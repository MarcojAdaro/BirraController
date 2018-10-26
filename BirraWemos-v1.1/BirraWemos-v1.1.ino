#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>

int  count;
char ferms[18];

//-------------------------------------------------------------------------------------------------//
#define cant 3 //Cantidad de Fermentadores
//-------------------------------------------------------------------------------------------------//
OneWire ourWire(D5);                //Se establece el pin 3  como bus OneWire
DallasTemperature sensors(&ourWire); //Se declara una variable u objeto para nuestro sensor
//----------Seteo las direcciones de los sensores--------------------------------------------------//
DeviceAddress address1 = {0x28, 0xFF, 0x6B, 0x10, 0x86, 0x16, 0x5, 0xDB};//dirección del sensor 1
DeviceAddress address2 = {0x28, 0xFF, 0xD3, 0xA0, 0x94, 0x16, 0x5, 0x3E};//dirección del sensor 2
DeviceAddress address3 = {0x28, 0xFF, 0x3C, 0xA3, 0x94, 0x16, 0x5, 0x3};//dirección del sensor 3
DeviceAddress address4 = {0x28, 0xFF, 0x8B, 0x4D, 0xC2, 0x16, 0x3, 0x36};  /// sensor de repuesto

//--------------------------Temp max and min de los fermentadores-----------------------//
float MaxFerm[cant];
float MaxMad[cant];
float MinMad[cant];
float MinFerm[cant];
//------------------------------------------------------------------------------------//
int derecha=0;
//----------Configuro los pines para los RELES----------------------------------------//
int RelePin[3]= {D1,D2,D3};
//int RelePin1= DG2;
//int RelePin2= DG3;
int ReleMotor = D4;
int OnOff[cant];
int Nferm;
//----------seteo las variables------------------------------------------------------//
int value[cant];
float temp[cant];
//--------------------------------------------------------------------------------------------//
void setup() {

  int i;
  delay(2000);
  sensors.begin();               //Se inicia el sensor
  Serial.begin(9600);
  pinMode(RelePin[0], OUTPUT);
  pinMode(RelePin[1], OUTPUT);
  pinMode(RelePin[2], OUTPUT);
  pinMode(ReleMotor, OUTPUT);
  count=0;
  Nferm=0;
}

void loop() {
  
  sensors.requestTemperatures();   //envía el comando para obtener las temperaturas
  temp[0]= sensors.getTempC(address4);//Se obtiene la temperatura en °C del sensor 1
  temp[1]= 10+(sensors.getTempC(address4));//Se obtiene la temperatura en °C del sensor 2
  temp[2]= 20+(sensors.getTempC(address4));//Se obtiene la temperatura en °C del sensor 3
  
  //--------------------------------FERMENTADOR 1 --------------------------------------------//
  for(int i=0 ; i<3; i++){
    //Serial.println("Entre al for");
    //Serial.write("i = "+(char)i);
    //Serial.println(OnOff[i]);
    if(OnOff[i]==1){
  
      fermentar(0,ReleMotor,RelePin[i], temp[i],value[i],MaxFerm[i],MinFerm[i],MaxMad[i],MinMad[i]);
      Serial.print(i);
      Serial.print(temp[i]); 
      }
    else{
      digitalWrite(RelePin[i], LOW);
    
    }
  }                                      
  
  if(!OnOff[0] && !OnOff[1] && !OnOff[2]) digitalWrite(ReleMotor, LOW);
  count=0;
 
  if(Serial.available()>16){
     
     while(count<18){
      ferms[count]=Serial.read()-48;
      count++;
      delay(100);
     }

      
     Nferm =ferms[0]-1;
     
     if(Nferm>=0 && Nferm<3){
         OnOff[Nferm] = ferms[14];
         MaxFerm[Nferm]= (ferms[2]*10)+ferms[3];
         MaxMad [Nferm]= (ferms[8]*10)+ferms[9];
         MinMad [Nferm]= (ferms[11]*10)+ferms[12];
         value  [Nferm]= ferms[16];
         MinFerm[Nferm]= (ferms[5]*10)+ferms[6];
     }
     
  }  
  
  delay(1000);
}
 
void fermentar(int n_ferm ,int Motor, int Pin, float temp,int value,float f_max,float f_min,float m_max,float m_min){

  if(value==1){ // entro en modo fermentacion
    if (temp>=f_max){//------------------------------> camibiar temperatura minima modo fermentador 
      digitalWrite(Motor, HIGH);
      digitalWrite(Pin, HIGH);   //  prendo rele 
      //apagar[n_ferm]=false;
    }else if (temp<f_min){
      digitalWrite(Pin, LOW);   //  apago rele 
      //apagar[n_ferm]=true;
      }
  }if(value==0) { //entro en modo maduracion
    if (temp>=m_max){//------------------------------> camibiar temperatura minima modo maduracion 
      digitalWrite(Motor, HIGH);
      digitalWrite(Pin, HIGH);   // prendo rele 
      //apagar[n_ferm]=false;
    }else if (temp<m_min){
      digitalWrite(Pin, LOW);    //apago el rele 
      //apagar[n_ferm]=true;
    }
  }
}

