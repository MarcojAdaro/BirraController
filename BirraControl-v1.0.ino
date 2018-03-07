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
//asdasd
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
if(value1==1){ // ----------------------------------------------------------entro en modo fermentacion-----------------------//
prueba1=1; // pongo en 1 prueba1 para avisar al LCD que esta en modo FER
  if (temp1>=20){//------------------------------> cambiar temperatura minima modo fermentador 1<------ACA CAMBIO TEMPERATURA
    digitalWrite(ReleMotor, HIGH);  //Enciendo el rele del motor 
    digitalWrite(RelePin, HIGH);   // Enciendo rele de la electrovalvula 1
    bandera++;
  }else if (temp1<18){
     digitalWrite(RelePin, LOW);   //  Apago Electrovalvula
     bandera--;
      if(bandera==0){
         digitalWrite(ReleMotor, LOW);  // Apago Motor
      }
  }
}if(value1==0) {  // -----------------------------------------------------entro en modo maduracion--------------------------//
prueba1=0; // pongo en 0 prueba1 para avisar al LCD que esta en modo MAD
  if (temp1>=4){//------------------------------> camibiar temperatura minima modo maduracion 1<------ ACA CAMBIO TEMPERATURA
    digitalWrite(ReleMotor, HIGH);
    digitalWrite(RelePin, HIGH);   // Enciende el pin 6// prendo rele 1
    bandera++;
  }else if (temp1<3) {
      digitalWrite(RelePin, LOW);   // Enciende el pin 6//apago el rele 1
      bandera--;
      if(bandera==0){
        digitalWrite(ReleMotor, LOW);  // Apago Motor
            }
  }
}
//--------------------------------FERMENTADOR 2 ---------------------------------------------------------------------------//
if(value2==1){ // entro en modo fermentacion
prueba2=1;
  if (temp2>=20){//------------------------------> camibiar temperatura minima modo fermentador 2
    digitalWrite(ReleMotor, HIGH);
    digitalWrite(RelePin2, HIGH);   //  prendo rele 2
    bandera++;
  }else if (temp2<18){
    digitalWrite(RelePin2, LOW);   //  apago rele 2
    bandera--;
    if(bandera==0){
      digitalWrite(ReleMotor, LOW);  // Apago Motor
      }
    }
}if(value2==0) { //entro en modo maduracion
prueba2=0;
  if (temp2>=4){//------------------------------> camibiar temperatura minima modo maduracion 2
    digitalWrite(ReleMotor, HIGH);
    digitalWrite(RelePin2, HIGH);   // Enciende el pin 9, prendo rele 2
    bandera++;
  }else if (temp2<3){
    digitalWrite(RelePin2, LOW);    //apago el rele 2
    bandera--;
    if(bandera==0){
      digitalWrite(ReleMotor, LOW);  // Apago Motor
    }
   }
}
//--------------------------------FERMENTADOR 3-------------------------------------------------------------------------//
if(value3==1){ // entro en modo fermentacion
 Serial.println(temp3);
prueba3=1;
  if (temp3>=20){//------------------------------> camibiar temperatura minima modo fermentador 3
    digitalWrite(ReleMotor, HIGH);
    digitalWrite(RelePin3, HIGH);   // Enciende el pin 9, prendo rele 3
    Serial.println("motor prendido");
    bandera=1;
  }else if (temp3<18){
    digitalWrite(RelePin3, LOW);    //apago el rele 3
    bandera=0;
    Serial.println(bandera);
    if(bandera==0){
      digitalWrite(ReleMotor, LOW);  // Apago Motor
      Serial.println("motor apagado");
      }
    }
}if(value3==0) {  // entro en modo maduracion
prueba3=0; 
  if (temp3>=4){//------------------------------> camibiar temperatura minima modo maduracion 3
    digitalWrite(ReleMotor, HIGH);
    digitalWrite(RelePin3, HIGH);   // Enciende el pin 9, prendo rele 3 
    bandera++;
}else if (temp3<3) {
    digitalWrite(RelePin3, LOW);    //apago el rele 3
    bandera--;
    if(bandera==0){
      digitalWrite(ReleMotor, LOW);  // Apago Motor
      }
    } 
}
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


