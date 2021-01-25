#include <OneWire.h>
//biblioteka ze strony:
//https://github.com/PaulStoffregen/OneWire
//Biblioteka DallasTemperaure (poniżej) jest dodatkowa, można obsłużyć czujnik bez niej

// Include the libraries we need
#include <DallasTemperature.h>
//biblioteka ze strony:
//https://github.com/milesburton/Arduino-Temperature-Control-Library

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

//********** Zmienne do przechowywania odczytów
union singleFloat {
float val;
byte b[4];
} temperature[1];


/*
 * The setup function. We only start the sensors here
 */
void oneWireSetup()
{
  //Serial.println("Dallas Temperature IC Control Library");
  // Start up the library
  sensors.begin();
}

/*
 * Main function, get and show the temperature
 */
void oneWireLoop(void)
{ 
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  //Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  //Serial.println("DONE");
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  //Serial.print("Temperature for the device 1 (index 0) is: ");
  temperature[0].val = sensors.getTempCByIndex(0);
  //Serial.println(temperature[0].b[3]);
}