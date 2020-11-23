#include "DHT.h"

#define DHTTYPE DHT22   // DHT 22  (AM2302)

#define DHTPIN_1 11     // what pin we're connected to

// Connect pin 1 (on the left) of the sensor to +5V - PATRZAC OD PRZODU NA "KRATKE"
// Connect pin 22 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

DHT dht1(DHTPIN_1, DHTTYPE);

void dhtSetup(){
  Serial.println("DHTxx test!");
  dht1.begin();
}

void dhtLoop(){
    // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht1.readHumidity();
  float t = dht1.readTemperature();

  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  } else {
    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.println(" *C");
    char temp[6];
    dtostrf(t, 4, 2, temp);
    mqqtSend("outTopic", temp);
  }
}

