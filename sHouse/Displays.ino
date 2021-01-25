#include <LiquidCrystal_I2C.h>
//#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

void displaysSetup()
{
  Serial.println("LCD begin");
  lcd.begin(16,2);                      //Inicjalizacja wyświetlacza, podanie ilosci znakow i wierszy

  lcd.backlight();

  //Napisanie tekstu na ekranie
lcd.setCursor(0,0);  
  lcd.print("LCD na I2C!!    ");  
   delay(1000);
  //lcd.noBacklight();   
  lcd.setCursor(0,1);  
  lcd.print("Drugi wiersz    "); 
}

void displaysLoop(){
  
}

