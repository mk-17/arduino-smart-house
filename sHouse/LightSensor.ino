 /*
  This is a simple code to test BH1750FVI Light senosr
  communicate using I2C Protocol 
  this library enable 2 slave device address
  Main address  0x23 
  secondary address 0x5C 
  connect this sensor as following :
  VCC >>> 3.3V
  SDA >>> A4 
  SCL >>> A5
  addr >> A3
  Gnd >>>Gnd

  Written By : Mohannad Rawashdeh
  
 */

 //*************************
 //Biblioteka uzywa Wire.h, musialem zmienic standardowe nazwy z reset na resetLS w bibliotece - byl konflikt z inna
 //strona biblioteki: http://www.instructables.com/id/BH1750-Digital-Light-Sensor/step4/Arduino-Code/

  // First define the library :
#include <BH1750FVI.h> // Sensor Library

uint16_t Light_Intensity=0;

BH1750FVI LightSensor;

void lightSensorSetup(){
   //  call begin Function so turn the sensor On .
  LightSensor.begin();
  //LightSensor.SetAddress(Device_Address_H); //Address 0x5C // kiedy ADDR  podlaczony do 3,3V
  LightSensor.SetAddress(Device_Address_L); //Address 0x23  // kiedy ADDR podlaczony do GND
  LightSensor.SetMode(Continuous_H_resolution_Mode);  
}

void lightSensorLoop(){
     lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print(" Intensity = ");
      lcd.setCursor(5, 1);
   Light_Intensity = LightSensor.GetLightIntensity();
   lcd.print(Light_Intensity);
   lcd.print(" Lux");
   delay(2000);
}

