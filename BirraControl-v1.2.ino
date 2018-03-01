#include <OneWire.h>                
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
 
OneWire ourWire(3);                //Se establece el pin 3  como bus OneWire
DallasTemperature sensors(&ourWire); //Se declara una variable u objeto para nuestro sensor
//----------Seteo las direcciones de los sensores--------------------//
DeviceAddress address1 = {0x28, 0xFF, 0x6B, 0x10, 0x86, 0x16, 0x5, 0xDB};//dirección del sensor 1
DeviceAddress address2 = {0x28, 0xFF, 0xD3, 0xA0, 0x94, 0x16, 0x5, 0x3E};//dirección del sensor 2
DeviceAddress address3 = {0x28, 0xFF, 0x3C, 0xA3, 0x94, 0x16, 0x5, 0x3};//dirección del sensor 3
DeviceAddress address4 = {0x28, 0xE5, 0x6E, 0x1,  0x0,  0x0,  0x80, 0x6C};  /// sensor de repuesto


//------------Seteo la LCD-----------------------------------------//
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int lcd_key     = 0;
int adc_key_in  = 0;
//-------------Configuro boton derecho------------------------------//
#define btnDERECHA      0
int derecha=0;
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // Leer la entrada analógica
 if (adc_key_in < 50)   return btnDERECHA;  
}
//----------Configuro los pines para los interruptores------------//
int Interruptor1 = A3; 
int Interruptor2 = A4;
int Interruptor3= A5;
//----------Configuro los pines para los RELES--------//
int RelePin = A1;
int RelePin2 = 2;
int RelePin3 = 1;
int ReleMotor = A2;
//----------seteo las variables------------//
int value1=0;
int value2=0;
int value3=0;
int prueba1=0;
int prueba2=0;
int prueba3=0;
int bandera=0;

boolean apagar[3];

void setup() {
  
delay(1000);
Serial.begin(9600);
sensors.begin();               //Se inicia el sensor
pinMode(Interruptor1, INPUT);  
pinMode(Interruptor2, INPUT);
pinMode(Interruptor3, INPUT);
pinMode(RelePin, OUTPUT);
pinMode(RelePin2, OUTPUT);
pinMode(RelePin3, OUTPUT);
pinMode(ReleMotor, OUTPUT);
lcd.begin(16, 2);                 //LCD de 16 columnas y 2 filas
lcd.clear();                      //Borrar la pantalla
lcd.setCursor(4, 0);              //Llevar el cursor al inicio
lcd.print(" TOSKA ");             // Escritura del primer renglon 
lcd.setCursor(0,1);               // Lo demas escribe en el segundo renglon
}
 
void loop() {

lcd.setCursor(0,1);            // Lleva el cursor al inicio de la segunda linea
lcd_key = read_LCD_buttons();  // Lee las teclas 
value1= digitalRead(Interruptor1);// paso a digital el interruptor
value2= digitalRead(Interruptor2);
value3= digitalRead(Interruptor3);
sensors.requestTemperatures();   //envía el comando para obtener las temperaturas
float temp1= sensors.getTempC(address1);//Se obtiene la temperatura en °C del sensor 1
float temp2= sensors.getTempC(address2);//Se obtiene la temperatura en °C del sensor 2
float temp3= sensors.getTempC(address4);//Se obtiene la temperatura en °C del sensor 3

//--------------------------------FERMENTADOR 1 -----------------------------------------------------------------------------//
fermentar(1,ReleMotor,RelePin, temp1, value1,20,18,4,3);
//--------------------------------FERMENTADOR 2 ---------------------------------------------------------------------------//
fermentar(2,ReleMotor,RelePin2, temp2, value2,20,18,4,3);
//--------------------------------FERMENTADOR 3-------------------------------------------------------------------------//
fermentar(3,ReleMotor,RelePin3, temp3,value3,20,18,4,3);


if(apagado[0] && apagado[1] && apagado[2]) digitalWrite(Motor, LOW);
//------------------------------------------------------------------------//
switch (lcd_key){               // Imprime un texto según el valor de la tecla detectada
  case btnDERECHA:
  {
    delay (500);
    derecha = derecha +1;
    if (derecha==1){
      lcd.print("F1- ");
      lcd.print(temp1);      // display seconds elapsed since power-up
      lcd.print("C ");
      if(prueba1==1){
        lcd.print(" Fer");
      }else {
        lcd.print(" Mad");        
      }
    }
    if (derecha==2){
      lcd.print("F2- ");
      lcd.print(temp2);      // display seconds elapsed since power-up
      lcd.print("C ");
      if(prueba2==1){
        lcd.print(" Fer");
      }else {
        lcd.print(" Mad");        
      }
     }
    if (derecha==3){
      lcd.print("F3- ");
      lcd.print(temp3);      // display seconds elapsed since power-up
      lcd.print("C ");
      if(prueba3==1){
        lcd.print(" Fer");
      }else {
        lcd.print(" Mad");        
      }
      derecha = 0;
    }
    
    break;
     
  }
}
 
delay(100);                     
}

void fermentar(int n_ferm ,int Motor, int Pin, float temp,int value,float f_max,float f_min,float m_max,float m_min){

 
if(value==1){ // entro en modo fermentacion
prueba2=1;
  if (temp>=f_max){//------------------------------> camibiar temperatura minima modo fermentador 2
    digitalWrite(Motor, HIGH);
    digitalWrite(Pin, HIGH);   //  prendo rele 2
    apagar[n_ferm]=false;
  }else if (temp<f_min){
    digitalWrite(Pin, LOW);   //  apago rele 2
     apagar[n_ferm]=true; 
    }
}if(value2==0) { //entro en modo maduracion
prueba2=0;
  if (temp>=m_max){//------------------------------> camibiar temperatura minima modo maduracion 2
    digitalWrite(Motor, HIGH);
    digitalWrite(Pin, HIGH);   // Enciende el pin 9, prendo rele 2
    apagar[n_ferm]=false;
  }else if (temp<m_min){
    digitalWrite(Pin, LOW);    //apago el rele 2
    apagar[n_ferm]=true
   }
}

}
