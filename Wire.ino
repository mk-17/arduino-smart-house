#include <Wire.h> //generalna biblioteka do obslugi I2C/TWI (TWI-Two Wire Interface jako ze I2C jest zastrzezona nazwa)
//tylko do komunikacji do małych odległości lub na większe odległości z uzyciem Bus Extender: P82B715
//********** Zmienne do przechowywania odczytów
union singleFloat {
float val;
byte b[4];
} temperature[1];

void wireSetup() {
  Wire.begin();        // join i2c bus (address optional for master)
}

void wireLoop() {
  Serial.println("Rozpoczynam pobieranie");
  Wire.requestFrom(8, 4);    // request 4 bytes (a float) from slave device #8

  int i = 0;
  while (Wire.available()) { // slave may send less than requested
    temperature[0].b[i] = Wire.read(); // receive a byte as character
    i++;
  }
  Serial.print("Pobrana ze slave temp=");
  Serial.println(temperature[0].val);
}
