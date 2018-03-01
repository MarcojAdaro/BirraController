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


#define BUTTON_ADC_PIN A0  // A0 is the button ADC input

#define LCD_BACKLIGHT_PIN 10  // D10 controls LCD backlight


#define RIGHT_10BIT_ADC           0  // right
#define UP_10BIT_ADC            120  // up
#define DOWN_10BIT_ADC          280  // down
#define LEFT_10BIT_ADC          480  // left
#define SELECT_10BIT_ADC        720  // right
#define BUTTONHYSTERESIS         30  // hysteresis for valid button sensing window


//-------------Configuro boton derecho------------------------------//
#define BUTTON_NONE               0  // 
#define BUTTON_RIGHT              1  // 
#define BUTTON_UP                 2  // 
#define BUTTON_DOWN               3  // 
#define BUTTON_LEFT               4  // 
#define BUTTON_SELECT             5  // 

//------------Seteo la LCD-----------------------------------------//
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int lcd_key     = 0;
int adc_key_in  = 0;


//--------------------------Temp max and min de los fermentadores-----------------------//
//float f_max[cant],f_min[cant];
//float m_max[cant],m_min[cant];
//------------------------------------------------------------------------------------//


int derecha=0;

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


//int value[cant];
int temp[cant];

int prueba1=0;
int prueba2=0;
int prueba3=0;
int bandera=0;

boolean apagar[3];

byte buttonJustPressed  = false;         //this will be true after a ReadButtons() call if triggered
byte buttonJustReleased = false;         //this will be true after a ReadButtons() call if triggered
byte buttonWas          = BUTTON_NONE;   //used by ReadButtons() for detection of button events


int SelectingMenu = true;               //This will be true until the select button is pressed in Menu()
int scroll = 0;                         //Used in Menu(). Stores numerical value of key pressed
int button = 0;                         //Sets scroll when a button is pressed. Acts on it when release
int menu = 4;                           //Stores the value of the menu. Used in Menu()
int FunctionChoice;                     //Stores the value of the selected function
float Answer;                           //where the answer is stored.

float A;                                //holds the values being computed
float B;




void setup() {
int i;
  
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

pinMode( BUTTON_ADC_PIN, INPUT );         //ensure A0 is an input
digitalWrite( BUTTON_ADC_PIN, LOW );      //ensure pullup is off on A0
  //lcd backlight control
digitalWrite( LCD_BACKLIGHT_PIN, HIGH );  //backlight control pin D3 is high (on)
pinMode( LCD_BACKLIGHT_PIN, OUTPUT );     //D3 is an output

lcd.begin(16, 2);                 //LCD de 16 columnas y 2 filas
lcd.clear();                      //Borrar la pantalla
lcd.setCursor(4, 0);              //Llevar el cursor al inicio
lcd.print(" TOSKA ");             // Escritura del primer renglon 
lcd.setCursor(0,1);               // Lo demas escribe en el segundo renglon


for(i=0;i<cant;i++)
  temp[i]=20;

}
 
void loop() {

lcd.setCursor(0,1);            // Lleva el cursor al inicio de la segunda linea
button = ReadButtons();  // Lee las teclas 
value1= digitalRead(Interruptor1);// paso a digital el interruptor
value2= digitalRead(Interruptor2);
value3= digitalRead(Interruptor3);
sensors.requestTemperatures();   //envía el comando para obtener las temperaturas
float temp1= sensors.getTempC(address1);//Se obtiene la temperatura en °C del sensor 1
temp[0]= sensors.getTempC(address1);
float temp2= sensors.getTempC(address2);//Se obtiene la temperatura en °C del sensor 2
float temp3= sensors.getTempC(address3);//Se obtiene la temperatura en °C del sensor 3

if(ReadButtons()==BUTTON_SELECT)
  Menu();

//--------------------------------FERMENTADOR 1 -----------------------------------------------------------------------------//
fermentar(0,ReleMotor,RelePin, temp1,value1,20,18,4,3);
                                       //    |  |
                                      //Fer max min Mad Max Min
//--------------------------------FERMENTADOR 2 ---------------------------------------------------------------------------//
fermentar(1,ReleMotor,RelePin2, temp2,value2,20,18,4,3);
//--------------------------------FERMENTADOR 3-------------------------------------------------------------------------//
fermentar(2,ReleMotor,RelePin3, temp3,value3,20,18,4,3);


if(apagar[0] && apagar[1] && apagar[2]) digitalWrite(ReleMotor, LOW);
//------------------------------------------------------------------------//
switch (button){               // Imprime un texto según el valor de la tecla detectada
  case BUTTON_RIGHT:
  {
    delay (500);
    derecha = derecha +1;
    if (derecha==1){
      lcd.print("F1- ");
      lcd.print(temp1);      // display seconds elapsed since power-up
      lcd.print("C ");
      if(value1==1){
        lcd.print(" Fer");
      }else {
        lcd.print(" Mad");        
      }
    }
    if (derecha==2){
      lcd.print("F2- ");
      lcd.print(temp2);      // display seconds elapsed since power-up
      lcd.print("C ");
      if(value2==1){
        lcd.print(" Fer");
      }else {
        lcd.print(" Mad");        
      }
     }
    if (derecha==3){
      lcd.print("F3- ");
      lcd.print(temp3);      // display seconds elapsed since power-up
      lcd.print("C ");
      if(value3==1){
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

void pantalla(){
  int i;
  for(i=0;i<3;i++){  
    if (derecha==1){
       lcd.print("F");
       lcd.print(i+1);
       lcd.print("- ");
       lcd.print(temp[i]);      // display seconds elapsed since power-up
       lcd.print("C ");
       if(value1==1){
          lcd.print(" Fer");
        }else {
          lcd.print(" Mad");        
      }
    }
  }
}

void Menu(){
  int fermentador;
  lcd.clear();                      //Borrar la pantalla
  lcd.setCursor(2, 0);              //Llevar el cursor al inicio
  lcd.print("Cambiar Temp");             // Escritura del primer renglon 
  
  while(ReadButtons()!= BUTTON_UP){}
  
  fermentador=choice_ferm();
  
  lcd.setCursor(0,1);               // Lo demas escribe en el segundo renglon

  
}

int Menu2 ()
{
  SelectingMenu = true;
  button = ReadButtons();
  if ( buttonJustPressed == true )  //If the button is pressed, store the value
  {
    scroll = button;
    Serial.print (button);   //Testing purposes
    buttonJustPressed = false;
  }

  if (buttonJustReleased == true)  //If the button is released, act on value
  {
    buttonJustReleased = false;

    switch (scroll)
    {
    case BUTTON_UP:
      { 
        menu = menu +1;
        break;
      }
    case BUTTON_DOWN:
      {
        menu = menu - 1;
        break;
      }
    case BUTTON_SELECT:
      {
        SelectingMenu = false;
      }
    default:
      {
        break;
      }
    }  //End switch
  }    //End if
  Serial.println(menu);
  return menu;
}  //End Function

/*
void set_temp(){

while(read_LCD_buttons()!= btnLEFT){ 
   switch (FunctionChoice)
    {
      case 0:{
       lcd.print("T MAX");
       lcd.print("- ");
       lcd.print(temp[i]);      // display seconds elapsed since power-up
       lcd.print("C ");
       if(value1==1){
          lcd.print(" Fer");
        }else {
          lcd.print(" Mad");  
      }
  case 1: 
    {
      lcd.print ("Add        (A+B)              ");
      Add();
      break;
    }
  case 2:
    {
      lcd.print ("Subtract   (A-B)         ");
      Subtract();
      break;
    }
  case 3: 
    {
      lcd.print ("Multiply   (A*B)        ");
      Multiply();
      break;
    }
  case 4:
    {
      lcd.print ("Divide     (A/B)            ");
      Divide();
      break;
    }
  case 5: 
    {
      FunctionChoice = 1;
    }      
  }  //End switch
 
 }  

}
*/

int choice_ferm(){
  int caso=0, caso_ant=0;
    
  lcd.clear();                      //Borrar la pantalla
  lcd.setCursor(0, 0);              //Llevar el cursor al inicio
  lcd.print("Fermentacion 1");
  
  while(button!= BUTTON_LEFT){
  
  button=Menu2();
  delay(150);
  if(button== BUTTON_UP)
    caso++;
    
  if(button== BUTTON_DOWN)
    caso--;
    
   delay(500);
   //if(caso>cant) caso=1;
   
   Serial.print("caso");
   Serial.println(caso);
  
  
  if(caso!=caso_ant){
     
      lcd.clear();                      //Borrar la pantalla
      lcd.setCursor(0, 0);              //Llevar el cursor al inicio
      Serial.print("pase");
      
      if((caso % 2)==0){lcd.print("Fermentacion ");lcd.print(caso);}
      else {lcd.print("Maduracion ");
        if(caso_ant==0) lcd.print("1");
        else  lcd.print(caso_ant);
        }
      caso_ant=caso;
  }
       
  }
  
  return caso;
}



byte ReadButtons()
{
  unsigned int buttonVoltage;
  byte button = BUTTON_NONE;   // return no button pressed if the below checks don't write to btn

  //read the button ADC pin voltage
  buttonVoltage = analogRead( BUTTON_ADC_PIN );
  //sense if the voltage falls within valid voltage windows
  if( buttonVoltage < ( RIGHT_10BIT_ADC + BUTTONHYSTERESIS ) )
  {
    button = BUTTON_RIGHT;
  }
  else if(   buttonVoltage >= ( UP_10BIT_ADC - BUTTONHYSTERESIS )
    && buttonVoltage <= ( UP_10BIT_ADC + BUTTONHYSTERESIS ) )
  {
    button = BUTTON_UP;
  }
  else if(   buttonVoltage >= ( DOWN_10BIT_ADC - BUTTONHYSTERESIS )
    && buttonVoltage <= ( DOWN_10BIT_ADC + BUTTONHYSTERESIS ) )
  {
    button = BUTTON_DOWN;
  }
  else if(   buttonVoltage >= ( LEFT_10BIT_ADC - BUTTONHYSTERESIS )
    && buttonVoltage <= ( LEFT_10BIT_ADC + BUTTONHYSTERESIS ) )
  {
    button = BUTTON_LEFT;
  }
  else if(   buttonVoltage >= ( SELECT_10BIT_ADC - BUTTONHYSTERESIS )
    && buttonVoltage <= ( SELECT_10BIT_ADC + BUTTONHYSTERESIS ) )
  {
    button = BUTTON_SELECT;
  }
  //handle button flags for just pressed and just released events
  if( ( buttonWas == BUTTON_NONE ) && ( button != BUTTON_NONE ) )
  {
    //the button was just pressed, set buttonJustPressed, this can optionally be used to trigger a once-off action for a button press event
    //it's the duty of the receiver to clear these flags if it wants to detect a new button change event
    buttonJustPressed  = true;
    buttonJustReleased = false;
  }
  if( ( buttonWas != BUTTON_NONE ) && ( button == BUTTON_NONE ) )
  {
    buttonJustPressed  = false;
    buttonJustReleased = true;
  }

  //save the latest button value, for change event detection next time round
  buttonWas = button;

  return( button );
}
