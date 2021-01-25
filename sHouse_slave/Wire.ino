#include <Wire.h>

void setupWire() {
Wire.begin(8);                // join i2c bus with address #8
Wire.onRequest(requestEvent); // register event

Wire.onReceive(receiveEvent);

}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  //Wire.write(temperature[0].b, 4); // respond with message of 4 bytes
 float liczba = 1234;
  temperature[0].val = liczba;
  Wire.write(temperature[0].b, 4);
  // as expected by master
  //Wire.write("hello ");
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{

   Serial.println(howMany);
  while(Wire.available()) // loop through all
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }

}
