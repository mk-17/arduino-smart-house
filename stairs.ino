#define STAIR_5 8
#define STAIR_4 7
#define STAIR_3 6
#define STAIR_2 5
#define STAIR_1 4

#define CONTROL 40

const unsigned int stairInterval = 270; //co jaki czas ma byc wlaczany kolejny schodek
const unsigned int starIncrease = stairInterval/9; //ile czasu ma wzrastac moc schodow, 
                                                    //powyzsze musze podzielic przez ilosc leveli swiatla, tabela ponizej
int startLightValues [9] = {0, 10, 30, 60, 120, 150, 200, 225, 255};


unsigned long oldTimer; //przechowuje stan licznika
unsigned long oldTimerIncrease; //przechowuje stan licznika

int nextToLight = 0;
int nextLightValue = 0;

int stairs[5];

int lightStatus = 4;
                     //1 - oznacza ze trwa zapalanie
                     //2 - oznacza ze trwa gaszenie
                     //3 - oznacza ze zapalona calosc
                     //4 - oznaczze ze zgaszona calosc
#define STATUS_TURNING_ON 1
#define STATUS_TURNING_OFF 2
#define STATUS_TURNED_ON 3
#define STATUS_TURNED_OFF 4

void stairsSetup(){
  stairs[0] = STAIR_1;
  stairs[1] = STAIR_2;
  stairs[2] = STAIR_3;
  stairs[3] = STAIR_4;
  stairs[4] = STAIR_5;       

  for(int i=0; i<sizeof(stairs)/sizeof(int); i++){
    pinMode(stairs[i], OUTPUT); 
  }
  
  pinMode(CONTROL, INPUT_PULLUP);
}

void stairsLoop(){
  unsigned long currentTimer;
  currentTimer = millis();

  if(oldTimer == 0)
    oldTimer = currentTimer;  

  if(oldTimerIncrease == 0)
    oldTimerIncrease = currentTimer;

  if(digitalRead(CONTROL) && lightStatus != STATUS_TURNING_ON && lightStatus == STATUS_TURNED_OFF){//musi byc zgaszone zeby mozna bylo ponownie wlaczyc
    nextLightValue = 0;
    nextToLight = 0;
    lightStatus = STATUS_TURNING_ON;
    Serial.println("1.status="+String(lightStatus));
  }
  else if(!digitalRead(CONTROL) && lightStatus != STATUS_TURNING_OFF && lightStatus == STATUS_TURNED_ON){ //gasic moge rozpoczac tylko jak jest calosc zapalona i nie jest obecnie gaszone
    nextLightValue = sizeof(startLightValues)/sizeof(int)-1;
    nextToLight = sizeof(stairs)/sizeof(int)-1;
    lightStatus = STATUS_TURNING_OFF;
    Serial.println("2.status="+String(lightStatus));    
  }

//na razie zapalane jest wszystko od dołu...
//trzeba przerobic zeby zapalane i gaszenie bylo mozliwe zarowno od dolu i od gory
  //delay(100);
  //Serial.println(String(turnOn)+";"+String(isLighted));
  if(lightStatus == STATUS_TURNING_ON){ //jesli wcisniety przycisk lub inne wywolanie zapalenia i jeszcze sie wszystko nie zapalilo
    if(currentTimer - oldTimerIncrease > starIncrease){ //minął interwał co ile mam zwiekszyc jasnosc jednego schowka 
      oldTimerIncrease = currentTimer;
      changeStairLight(nextToLight, nextLightValue);
      nextLightValue++;
      if(nextLightValue >= sizeof(startLightValues)/sizeof(int))
        nextLightValue = 0;
      if(nextLightValue == 0){ //minął interwał co ile mamy wlaczac kolejny schodek{
        //oldTimer = currentTimer; //resetuje czas na kolejny schodek        
        nextToLight++;
        Serial.println("nextToLight="+String(nextToLight)+"; size="+String(sizeof(stairs)/sizeof(int)));
        if(nextToLight >= sizeof(stairs)/sizeof(int)) //wykrycie ostatniego schodka
          lightStatus = STATUS_TURNED_ON; //oznacza ze wszystko zapalone
      }
    }
  }else if(lightStatus == STATUS_TURNING_OFF){
    if(currentTimer - oldTimerIncrease > starIncrease){ //minął interwał co ile mam zmniejszyc jasnosc jednego schowka 
        oldTimerIncrease = currentTimer;
        changeStairLight(nextToLight, nextLightValue);
        nextLightValue--;
        if(nextLightValue < 0){ //minął interwał co ile mamy wylaczac kolejny schodek{
          nextLightValue = sizeof(startLightValues)/sizeof(int)-1;
          oldTimer = currentTimer; //resetuje czas na kolejny schodek
          nextToLight--;
          Serial.println("nextToLight="+String(nextToLight)+"; size="+String(sizeof(stairs)/sizeof(int)));
          if(nextToLight < 0) //wykrycie ostatniego schodka
            lightStatus = STATUS_TURNED_OFF; //oznacza ze wszystko zgaszone
      }  
    }
  }
}

void changeStairLight(int stairNb, int lightValue){
  Serial.println("LightValue="+String(lightValue));
  analogWrite(stairs[stairNb], startLightValues[lightValue]);
}


