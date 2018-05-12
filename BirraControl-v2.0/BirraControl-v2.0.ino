// VERSION FUNCIONANDO EN TOSKA
#include <OneWire.h>                
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

#define cant 3

 
OneWire ourWire(3);                //Se establece el pin 3  como bus OneWire
DallasTemperature sensors(&ourWire); //Se declara una variable u objeto para nuestro sensor
//----------Seteo las direcciones de los sensores--------------------//
DeviceAddress address1 = {0x28, 0xFF, 0x6B, 0x10, 0x86, 0x16, 0x5, 0xDB};//dirección del sensor 1
DeviceAddress address2 = {0x28, 0xFF, 0xD3, 0xA0, 0x94, 0x16, 0x5, 0x3E};//dirección del sensor 2
DeviceAddress address3 = {0x28, 0xFF, 0x3C, 0xA3, 0x94, 0x16, 0x5, 0x3};//dirección del sensor 3
DeviceAddress address4 = {0x28, 0xFF, 0xE, 0x12, 0x1, 0x17, 0x4, 0x9D};  /// sensor de repuesto


//------------Seteo la LCD-----------------------------------------//
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int lcd_key     = 0;
int adc_key_in  = 0;
//-------------Configuro boton derecho------------------------------//
#define btnDERECHA 0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

//--------------------------Temp max and min de los fermentadores-----------------------//
//float f_max[cant],f_min[cant];
//float m_max[cant],m_min[cant];
//------------------------------------------------------------------------------------//


int derecha=0;

int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // Leer la entrada analógica
 if (adc_key_in < 50)   return btnDERECHA;  
 if (adc_key_in < 250)  return btnUP; 
 if (adc_key_in < 450)  return btnDOWN; 
 if (adc_key_in < 650)  return btnLEFT; 
 if (adc_key_in < 850)  return btnSELECT;  
}


//----------Configuro los pines para los interruptores------------//
int Interruptor1 = A3; 
int Interruptor2 = A4;
int Interruptor3= A5;
//----------Configuro los pines para los RELES--------//
int RelePin = A1;
int RelePin2 = 2;
int RelePin3 = 10;
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
  
delay(6000);
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


value1= digitalRead(Interruptor1);// paso a digital el interruptor
value2= digitalRead(Interruptor2);
value3= digitalRead(Interruptor3);

sensors.requestTemperatures();   //envía el comando para obtener las temperaturas

float temp1= sensors.getTempC(address1);//Se obtiene la temperatura en °C del sensor 1
float temp2= sensors.getTempC(address2);//Se obtiene la temperatura en °C del sensor 2
float temp3= sensors.getTempC(address3);//Se obtiene la temperatura en °C del sensor 3



lcd.setCursor(0,1);               // Lo demas escribe en el segundo renglon

  if (read_LCD_buttons()== btnDERECHA){
    derecha = derecha +1;
    if(derecha==3) derecha=0;
  } 
  
  switch(derecha){
    case 0:
    {
        lcd.print("F1- ");
        lcd.print(temp1);      // display seconds elapsed since power-up
        lcd.print("C ");
        if(value1==1){
          lcd.print(" Fer");
        }else {
          lcd.print(" Mad");        
        }
       break;
     }
     case 1:
     {
        lcd.print("F2- ");
        lcd.print(temp2);      // display seconds elapsed since power-up
        lcd.print("C ");
        if(value2==1){
          lcd.print(" Fer");
        }else {
          lcd.print(" Mad");        
        }
       break;
     }
     case 2:
     {
        lcd.print("F3- ");
        lcd.print(temp3);      // display seconds elapsed since power-up
        lcd.print("C ");
        if(value3==1){
          lcd.print(" Fer");
        }else {
          lcd.print(" Mad");        
        }
        break;
      }     
   }                  

//--------------------------------FERMENTADOR 1 -----------------------------------------------------------------------------//
fermentar(0,ReleMotor,RelePin, temp1,value1,20,18,6,4);
                                       //    |  |
                                      //Fer max min Mad Max Min
//--------------------------------FERMENTADOR 2 ---------------------------------------------------------------------------//
fermentar(1,ReleMotor,RelePin2, temp2,value2,20,18,6,4);
//--------------------------------FERMENTADOR 3-------------------------------------------------------------------------//
fermentar(2,ReleMotor,RelePin3, temp3,value3,19,17,6,4);


if(apagar[0] && apagar[1] && apagar[2]) digitalWrite(ReleMotor, LOW);
//------------------------------------------------------------------------//
//switch ()               // Imprime un texto según el valor de la tecla detectada

}

void fermentar(int n_ferm ,int Motor, int Pin, float temp,int value,float f_max,float f_min,float m_max,float m_min){

if(value==1){ // entro en modo fermentacion
  if (temp>=f_max){//------------------------------> camibiar temperatura minima modo fermentador 2
    digitalWrite(Motor, HIGH);
    digitalWrite(Pin, HIGH);   //  prendo rele 2
    apagar[n_ferm]=false;
  }else if (temp<f_min){
    digitalWrite(Pin, LOW);   //  apago rele 2
     apagar[n_ferm]=true; 
    }
}if(value==0) { //entro en modo maduracion
  if (temp>=m_max){//------------------------------> camibiar temperatura minima modo maduracion 2
    digitalWrite(Motor, HIGH);
    digitalWrite(Pin, HIGH);   // Enciende el pin 9, prendo rele 2
    apagar[n_ferm]=false;
  }else if (temp<m_min){
    digitalWrite(Pin, LOW);    //apago el rele 2
    apagar[n_ferm]=true;
   }
}

}


//void set_temp(){
//}



