#include <Wire.h>

void setupWire() {
Wire.begin(8);                // join i2c bus with address #8
Wire.onRequest(requestEvent); // register event
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire.write(temperature[0].b, 4); // respond with message of 4 bytes
  // as expected by master
}
