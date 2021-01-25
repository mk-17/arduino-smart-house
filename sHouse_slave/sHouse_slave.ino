const unsigned int sensorInterval = 6000; //co jaki czas ma byc odczyt z czujników [ms]

unsigned long oldTimer; //przechowuje stan licznika


void setup() {
  //Serial.begin(57600);
  //oneWireSetup();
  setupWire();
}

void loop() {

/*
  unsigned long currentTimer;
  currentTimer = millis();
  
  if(oldTimer == 0)
    oldTimer = currentTimer;
  
  if(currentTimer - oldTimer > sensorInterval){ //minął interwał co ile mamy wykonywać pomiar
    oldTimer = currentTimer; //resetujemy timer
    oneWireLoop(); //pobieramy wartości z czujników
  }else if (currentTimer - oldTimer < 0){ //przypadek kiedy licznik sie przekrecil
   oldTimer = currentTimer;
  }
*/

}
