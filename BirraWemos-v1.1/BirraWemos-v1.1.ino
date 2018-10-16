#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <pin_wemos.h>
/*      
      ------------
      |           |-d8 ->15
      |    W      |-d7 ->13
      |    E      |-d6 ->12
      |    M      |-d5 ->14
      |    O      |-d4 ->2
   A0-|    S      |-d3 ->0 
      |           |-d2 ->4
      |    D      |-d1 ->5
      |    1      |-d0 ->16
  SDA-|    R      |-rx
  SCL-|    2      |-tx
       ------------
*/

static const uint8_t DG0   = 16;
static const uint8_t DG1   = 5;
static const uint8_t DG2   = 4;
static const uint8_t DG3   = 0;
static const uint8_t DG4   = 2;
static const uint8_t DG5   = 14;
static const uint8_t DG6   = 12;
static const uint8_t DG7   = 13;
static const uint8_t DG8   = 15;
//-------------------------------------------------------------------------------------------------//
#define cant 3 //Cantidad de Fermentadores
//-------------------------------------------------------------------------------------------------//
OneWire ourWire(0);                //Se establece el pin 3  como bus OneWire
DallasTemperature sensors(&ourWire); //Se declara una variable u objeto para nuestro sensor
//----------Seteo las direcciones de los sensores--------------------------------------------------//
DeviceAddress address1 = {0x28, 0xFF, 0x6B, 0x10, 0x86, 0x16, 0x5, 0xDB};//dirección del sensor 1
DeviceAddress address2 = {0x28, 0xFF, 0xD3, 0xA0, 0x94, 0x16, 0x5, 0x3E};//dirección del sensor 2
DeviceAddress address3 = {0x28, 0xFF, 0x3C, 0xA3, 0x94, 0x16, 0x5, 0x3};//dirección del sensor 3
DeviceAddress address4 = {0x28, 0xFF, 0x8B, 0x4D, 0xC2, 0x16, 0x3, 0x36};  /// sensor de repuesto
//--------------------------Temp max and min de los fermentadores-----------------------//
float MaxFerm[cant],MinFerm[cant];
float MaxMad[cant],MinMad[cant];
//------------------------------------------------------------------------------------//
int derecha=0;
//----------Configuro los pines para los RELES----------------------------------------//
int RelePin = DG1;
int RelePin2 = DG2;
int RelePin3 = DG3;
int ReleMotor = DG4;
//----------seteo las variables------------------------------------------------------//
int value[cant];
int temp[cant];
boolean apagar[3];
//--------------------------------------------------------------------------------------------//
void setup() {

  int i;
  delay(2000);
  sensors.begin();               //Se inicia el sensor
  pinMode(RelePin, OUTPUT);
  pinMode(RelePin2, OUTPUT);
  pinMode(RelePin3, OUTPUT);
  pinMode(ReleMotor, OUTPUT);
}

void loop() {

  //value[0]= digitalRead(Interruptor1);// paso a digital el interruptor
  //value[1]= digitalRead(Interruptor2);
  //value[2]= digitalRead(Interruptor3);
  sensors.requestTemperatures();   //envía el comando para obtener las temperaturas
  float temp1= sensors.getTempC(address4);//Se obtiene la temperatura en °C del sensor 1
  float temp2= 10+(sensors.getTempC(address4));//Se obtiene la temperatura en °C del sensor 2
  float temp3= 20+(sensors.getTempC(address4));//Se obtiene la temperatura en °C del sensor 3
  //--------------------------------FERMENTADOR 1 --------------------------------------------//
  fermentar(0,ReleMotor,RelePin, temp1,value[0],MaxFerm[0],MinFerm[0],MaxMad[0],MinMad[0]);                                       
  //--------------------------------FERMENTADOR 2 --------------------------------------------//
  fermentar(1,ReleMotor,RelePin2, temp2,value[1],MaxFerm[1],MinFerm[1],MaxMad[1],MinMad[1]);
  //--------------------------------FERMENTADOR 3---------------------------------------------//
  fermentar(2,ReleMotor,RelePin3, temp3,value[2],MaxFerm[2],MinFerm[2],MaxMad[2],MinMad[2]);
  //-----------------------------------AND----------------------------------------------------//
  if(apagar[0] && apagar[1] && apagar[2]) digitalWrite(ReleMotor, LOW);
}
 
void fermentar(int n_ferm ,int Motor, int Pin, float temp,int value,float f_max,float f_min,float m_max,float m_min){

  if(value==1){ // entro en modo fermentacion
    if (temp>=f_max){//------------------------------> camibiar temperatura minima modo fermentador 
      digitalWrite(Motor, HIGH);
      digitalWrite(Pin, HIGH);   //  prendo rele 
      apagar[n_ferm]=false;
    }else if (temp<f_min){
      digitalWrite(Pin, LOW);   //  apago rele 
      apagar[n_ferm]=true;
      }
  }if(value==0) { //entro en modo maduracion
    if (temp>=m_max){//------------------------------> camibiar temperatura minima modo maduracion 
      digitalWrite(Motor, HIGH);
      digitalWrite(Pin, HIGH);   // prendo rele 
      apagar[n_ferm]=false;
    }else if (temp<m_min){
      digitalWrite(Pin, LOW);    //apago el rele 
      apagar[n_ferm]=true;
    }
  }
}

