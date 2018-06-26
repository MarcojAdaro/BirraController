#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

int read_LCD_buttons();  // para leer los botones

int read_LCD_buttons()  
  { adc_key_in = analogRead(0);      // Leemos A0
    // Mis botones dan:  0, 145, 329,507,743
    // Y ahora los comparamos con un margen comodo
    if (adc_key_in > 900) return btnNONE;     // Ningun boton pulsado 
    if (adc_key_in < 50)   return btnRIGHT; 
    if (adc_key_in < 250)  return btnUP;
    if (adc_key_in < 350)  return btnDOWN;
    if (adc_key_in < 550)  return btnLEFT;
    if (adc_key_in < 850)  return btnSELECT; 

    return btnNONE;  // Por si todo falla
  }
  
void setup() {
   lcd.begin(16, 2);              // Inicializar el LCD
      lcd.setCursor(0,0);
      lcd.print("Prometec.net");     // print a simple message
  // put your setup code here, to run once:

}

void loop() {
   lcd.setCursor(9,1);              // Cursor a linea 2, posicion 9
      lcd.print(millis()/1000);        // Imprime segundos
      lcd.setCursor(13, 0);            // Cursor a linea 1, posicion 13
      lcd.print(lcd_key);                  // Imprime el valor leido en la puerta A0
      lcd.setCursor(0,1);              // Cursor a linea 2, posicion 1
 
      lcd_key = read_LCD_buttons();
      if( lcd_key == btnRIGHT)
              lcd.print("RIGHT ");
      else if ( lcd_key == btnLEFT )
              lcd.print("LEFT   ");
      else if ( lcd_key == btnUP)
              lcd.print("UP    ");
      else if ( lcd_key == btnDOWN)
              lcd.print("DOWN  ");
      else if ( lcd_key == btnSELECT)
              lcd.print("SELECT");
      else if ( lcd_key == btnNONE)
              lcd.print("NONE  ");
  // put your main code here, to run repeatedly:

}
