//based on  Basic ESP8266 MQTT example
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
byte sleepTimeS = 5; // Deep sleep time in seconds


//For MPU650
#include<Wire.h>
const int MPU_addr = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ, hold;
// data
const char* color = "HYDRO-Pink";
const char* pub1 = "Hydro/Pink/TILT"  ;  //send angle
const char* pub2 =  "Hydro/Pink/TEMP" ;  //send temperature
const char* sub1 =  "Hydro/Pink/TARE" ;  //recieve tare switch position
const char* sub2 =  "Hydro/Pink/BATT" ;  //recieve battery Saver Value
String keeper;


// Update these with values suitable for your network.

const char* ssid = "YourSSID";
const char* password = "YourWIFIPassword";
const char* mqtt_server = "YourMQTTServerAddress";// no :1883

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50]; //tilt
char msg2[50]; //temp
//char Tilt[10];
int Tilt = 0;
int calibrateValue = 0;
byte SwitchPos;
float KeepTime = 0;
String SetTime;
String message;
void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = color;
    //clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...

      //Duplicate these as needed
      client.publish(pub1, "0"); //Set up Publising  for each value
      client.publish(pub2, "0");
      // ... and resubscribe
      client.subscribe(sub1);  //Set up Subscription for each value
      client.subscribe(sub2);



    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Wire.begin(2, 0); //nodeMCU D2,D1   8622-01 2,0
  Serial.begin(115200);
  Serial.println("Initializing I2C devices...");
  //pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();
  if (now - lastMsg > 2000 + KeepTime) { //2 seconds as a buffer
    lastMsg = now;
    getTemp();
    long now = millis();


    if (SwitchPos == 0) { // Implament Tare value
      Tilt =  Tilt - calibrateValue;
      //Serial.println("                    Switch 0 ");
      //Serial.println (Tilt);
    }

    snprintf (msg, 75, "%ld", Tilt);
    Serial.print("Tilt message: ");
    Serial.println(msg);
    client.publish(pub1, msg);     // Publish Tilt


    Serial.print("Temp message: ");
    snprintf (msg2, 75, "%ld", Tmp);
    client.publish(pub2, msg2);    // Publish Temp
    Serial.println(msg2);
    delay(300);
  }
}


void callback(String topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) { // Used to concatanate the message
    message += (char)payload[i];
  }
  keeper = message;    //Store the message
  message = "";        //Clear the buffer
  Serial.println(keeper); //debug chcek for data captured


  if (topic == sub1) {  //Tare Switch data
    // Switch on the LED if an 1 was received as first character
    if (keeper == "1") { //Tare Position
      digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
      // but actually the LED is on; this is because
      // it is acive low on the ESP-01)
      calibrateValue = Tilt; //Store data to find a zero point.
      if (calibrateValue < 0) {
        calibrateValue = 0;
      }
      SwitchPos = 1; //elimiate taring a tare value
      Serial.print("calabrating");
    }
    if (keeper == "0") { //Tare Position
      digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
      SwitchPos = 0;
      Serial.print("                         callValue        ");
      Serial.println(calibrateValue);
    }
  }


  if (topic == sub2) {  // Battery Saver data
    KeepTime = keeper.toInt();
    KeepTime = KeepTime * 3600000; // scale microseconds to hours
    Serial.print("                                               KeepTime  =  ");
    Serial.println(KeepTime);
  }
}

void getTemp() {
  //int Tmp=0;
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  //Tmp = Tmp / 340.00 + 33.6; //equation for temperature in degrees C from datasheet 340/36.53
  //Tmp = Tmp * 1.8 + 32;   //convert to F   Comment out for C
  Tilt = AcX / 100;
  Serial.print("AcX = "); Serial.print(AcX / 100);
  //Serial.print(" | AcY = "); Serial.print(AcY);
  //Serial.print(" | AcZ = "); Serial.print(AcZ);
  Serial.print(" | Tmp = "); Serial.println(Tmp);
  //  snprintf (msg, 75, "%ld", Tmp);
  //client.publish(pub2, msg);//
  delay(300);



}
