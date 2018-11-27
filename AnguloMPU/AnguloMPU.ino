#include <MPU6050.h>
#include "I2Cdev.h"
#include "Wire.h"
#include <ESP8266WiFi.h> 
#include "Adafruit_MQTT.h" 
#include "Adafruit_MQTT_Client.h" 
/************************* WiFi Access Point *********************************/ 
#define WLAN_SSID       "Cavegol" 
#define WLAN_PASS       "1q2w3e4r5t6y" 
#define MQTT_SERVER      "192.168.2.137"  // give static address
#define MQTT_PORT         1883                    
#define MQTT_USERNAME    "" 
#define MQTT_PASSWORD         "" 
// Create an ESP8266 WiFiClient class to connect to the MQTT server. 
WiFiClient client; 
// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details. 
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD); 
/****************************** Feeds ***************************************/ 
// Setup a feed called 'pi_led' for publishing. 
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname> 
Adafruit_MQTT_Publish pi_led = Adafruit_MQTT_Publish(&mqtt, MQTT_USERNAME "/leds/pi"); 
// Setup a feed called 'esp8266_led' for subscribing to changes. 
Adafruit_MQTT_Subscribe esp8266_led = Adafruit_MQTT_Subscribe(&mqtt, MQTT_USERNAME "/leds/esp8266"); 
/*************************** Sketch Code ************************************/ 
void MQTT_connect(); 
// La dirección del MPU6050 puede ser 0x68 o 0x69, dependiendo 
// del estado de AD0. Si no se especifica, 0x68 estará implicito
MPU6050 sensor;

// Valores RAW (sin procesar) del acelerometro  en los ejes x,y,z
int16_t ax, ay, az;
int16_t gx, gy, gz;

long tiempo_prev, dt;
float girosc_ang_x, girosc_ang_y;
float girosc_ang_x_prev, girosc_ang_y_prev;

float ang_x, ang_y;
float ang_x_prev, ang_y_prev;

void setup() {
  Serial.begin(115200);    //Iniciando puerto serial
  Wire.begin();           //Iniciando I2C  
  delay(10); 
  sensor.initialize();    //Iniciando el sensor
  WiFi.begin(WLAN_SSID, WLAN_PASS); 
  while (WiFi.status() != WL_CONNECTED) { 
   delay(500); 
   Serial.print("."); 
  } 
  Serial.println(); 
  Serial.println("WiFi connected"); 
  Serial.println("IP address: "); Serial.println(WiFi.localIP()); 
  // Setup MQTT subscription for esp8266_led feed. 
  mqtt.subscribe(&esp8266_led); 
  if (sensor.testConnection()) Serial.println("Sensor iniciado correctamente");
  else Serial.println("Error al iniciar el sensor");
}
uint32_t x=0; 
void loop() {
  // Leer las aceleraciones 
  MQTT_connect(); 
  sensor.getAcceleration(&ax, &ay, &az);
  //Calcular los angulos de inclinacion:
  float accel_ang_x=atan(ax/sqrt(pow(ay,2) + pow(az,2)))*(180.0/3.14);
  float accel_ang_y=atan(ay/sqrt(pow(ax,2) + pow(az,2)))*(180.0/3.14);
  float temp=sensor.getTemperature()/340.00+36.53;
  float accelZ = az * (9.81/16384.0);
  
  sensor.getRotation(&gx, &gy, &gz);
  //Calcular los angulos rotacion:
  dt = millis()-tiempo_prev;
  tiempo_prev=millis();
  girosc_ang_x = (gx/131)*dt/1000.0 + girosc_ang_x_prev;
  girosc_ang_y = (gy/131)*dt/1000.0 + girosc_ang_y_prev;
  girosc_ang_x_prev=girosc_ang_x;
  girosc_ang_y_prev=girosc_ang_y;


  dt = (millis()-tiempo_prev)/1000.0;
  tiempo_prev=millis();

  
  
  //Calcular angulo de rotación con giroscopio y filtro complemento  
  ang_x = 0.98*(ang_x_prev+(gx/131)*dt) + 0.02*accel_ang_x;
  ang_y = 0.98*(ang_y_prev+(gy/131)*dt) + 0.02*accel_ang_y;
  
  
  ang_x_prev=ang_x;
  ang_y_prev=ang_y;

 

  
  Adafruit_MQTT_Subscribe *subscription; 
  while ((subscription = mqtt.readSubscription())) { 
   if (subscription == &esp8266_led) { 
     Serial.print(F("Got: ")); 
     Serial.println((char *)esp8266_led.lastread); 
   }  
  
  pi_led.publish(accel_ang_x); 
  delay(10);
  pi_led.publish(accel_ang_y);
  delay(10);
  pi_led.publish(temp);
  delay(10);
  pi_led.publish(accelZ);
  delay(10);
  pi_led.publish(girosc_ang_x); 
  delay(10);
  pi_led.publish(girosc_ang_y);
  delay(10);
  pi_led.publish(ang_x); 
  delay(10);
  pi_led.publish(ang_y);
  pi_led.publish("-----------------");
 } 
  //Mostrar los angulos separadas por un [tab]
  /*
  Serial.print("Inclinacion en X: ");
  Serial.print(accel_ang_x); 
  Serial.print("tInclinacion en Y:");
  Serial.println(accel_ang_y);
  Serial.print("temp");
  Serial.println(temp);*/
  delay(2000);
}

void MQTT_connect() { 
 int8_t ret; 
 // Stop if already connected. 
 if (mqtt.connected()) { 
   return; 
 } 
 Serial.print("Connecting to MQTT... "); 
 uint8_t retries = 3; 
 while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected 
      Serial.println(mqtt.connectErrorString(ret)); 
      Serial.println("Retrying MQTT connection in 5 seconds..."); 
      mqtt.disconnect(); 
      delay(5000);  // wait 5 seconds 
      retries--; 
      if (retries == 0) { 
        // basically die and wait for WDT to reset me 
        while (1); 
      } 
 } 
 Serial.println("MQTT Connected!"); 
}  
