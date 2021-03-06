#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>

int  count;
char ferms[18];

//-------------------------------------------------------------------------------------------------//
#define cant 4 //Cantidad de Fermentadores
//-------------------------------------------------------------------------------------------------//
OneWire ourWire(D5);                
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
int RelePin[cant]= {D1,D2,D3,D4};
//int RelePin1= DG2;
//int RelePin2= DG3;
int ReleMotor = D6;
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
  for(i=0;i<cant;i++){
    pinMode(RelePin[i], OUTPUT);
  }
  pinMode(ReleMotor, OUTPUT);
  count=0;
  Nferm=0;

  for(i=0;i<cant;i++){
    MaxFerm[i]=22;
    MinFerm[i]=18;
    MaxMad[i]=22;
    MinMad[i]=22;
    value[i]=0;      
    OnOff[i]=0;
  }
  
}

void loop() {
  
  sensors.requestTemperatures();   //envía el comando para obtener las temperaturas
  temp[0]= sensors.getTempC(address1);//Se obtiene la temperatura en °C del sensor 1
  temp[1]= sensors.getTempC(address2);//Se obtiene la temperatura en °C del sensor 2
  temp[2]= sensors.getTempC(address3);//Se obtiene la temperatura en °C del sensor 3
  temp[3]= sensors.getTempC(address4);//Se obtiene la temperatura en °C del sensor 3
  
  //--------------------------------FERMENTADOR 1 --------------------------------------------//

  for(int i=0 ; i<cant; i++){

    if(OnOff[i]==1){
  
      fermentar(0,ReleMotor,RelePin[i], temp[i],value[i],MaxFerm[i],MinFerm[i],MaxMad[i],MinMad[i]);
      Serial.print(i);
      Serial.print(temp[i]);
      }
    else{
      digitalWrite(RelePin[i], LOW);
    }
    delay(300); 
  }                                      
    
  if(!OnOff[0] && !OnOff[1] && !OnOff[2] && !OnOff[3]) digitalWrite(ReleMotor, LOW);
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
      Serial.println("PRENDO EL RELE");
      //apagar[n_ferm]=false;
    }else if (temp<(((f_max-f_min)/2)+f_min)){
      digitalWrite(Pin, LOW);   //  apago rele 
      Serial.println("APAGO EL RELE");
      //apagar[n_ferm]=true;
      }
  }if(value==0) { //entro en modo maduracion
    if (temp>=m_max){//------------------------------> camibiar temperatura minima modo maduracion 
      digitalWrite(Motor, HIGH);
      digitalWrite(Pin, HIGH);   // prendo rele 
      //apagar[n_ferm]=false;
    }else if (temp<(((m_max-m_min)/2)+m_min)){
      digitalWrite(Pin, LOW);    //apago el rele 
      //apagar[n_ferm]=true;
    }
  }
}

