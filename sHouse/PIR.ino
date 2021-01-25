#define PIR1_PIN 12

void pirSetup(){
  pinMode(PIR1_PIN, INPUT);
}

void pirLoop(){
  int pir1State = digitalRead(PIR1_PIN);
  //If PIR state is HIGH
  if( pir1State > 0 ){
    alarm();
  }
}


void alarm(){
  //add alarm routines here
  //...
  Serial.println("ALARM!");
}

