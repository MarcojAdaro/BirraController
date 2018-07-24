/* Demonstration software for 1602 LCD Keypad via serial backpack
 *  Written by Keith Hungerford 14 May 2016
*/

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C  lcd(0x27,16,2);//2,1,0,4,5,6,7); // 0x27 is the I2C bus address for an unmodified backpack


int readkey;
long int lastmillis;
long int hours;
long int minutes;
long int seconds;
char l2c1; 
char l2c2;
char l2c3;


void setup() {
  lastmillis = millis();
  lcd.begin(16, 2);
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(0);
  lcd.clear();
  lcd.home() ;
  lcd.print("LCD & serial backpack");
  l2c1=' ';
  l2c2=' ';
  l2c3=' ';
}


void loop() {
 if (millis() - lastmillis > 15000) {
   lcd.setBacklight(HIGH);      // Backlight OFF
 }

  seconds = millis() / 1000 ;
  minutes = seconds / 60 ;
  hours = minutes / 60 ;
  seconds = seconds - (minutes * 60) ;
  minutes = minutes - hours *60 ;
  lcd.setCursor(8, 1); // go to char 8 in line 2
  lcd.print  (hours);
  lcd.print (":");
  lcd.print (minutes) ;
  lcd.print (":");
  lcd.print (seconds) ;
  lcd.print ("  ") ;
  
  readkey=analogRead(0);
  updateLCDline2();
  lastmillis = millis();
  /*if (readkey<50) {
    l2c1='R';
    updateLCDline2();
    lastmillis = millis();
  
  }
  else if(readkey<190) {
    l2c1='U';
    l2c2='p';
    updateLCDline2();
    lastmillis = millis();
 
  }
  else if(readkey<480) {
    l2c1='D';
    l2c2='n';
    updateLCDline2();
    lastmillis = millis();
 }
  else if(readkey<690) {
    l2c1='L';
    updateLCDline2();
    lastmillis = millis();
    
 }
  else if(readkey<750) {
    l2c1='S';
    l2c2='e';
    l2c3='l';
    updateLCDline2();
    lastmillis = millis();
 
  }
else if(readkey<950) {
    l2c1='R';
    l2c2='S';
    l2c3='T';
    updateLCDline2();
    lastmillis = millis();
 
  }*/

} 

void updateLCDline2(){
    lcd.setCursor(0, 1); // go to 1st char of line 2
    lcd.print(l2c1);
    lcd.print(l2c2);
    lcd.print(l2c3);
    l2c1=' ';
    l2c2=' ';
    l2c3=' ';
    lcd.setCursor(4, 1); // go to 4th char of line 2
    lcd.print("   ");
    lcd.setCursor(4, 1); // go to 4th char of line 2
    lcd.print  (readkey);
    lcd.setBacklight(LOW);      // Backlight ON

}

