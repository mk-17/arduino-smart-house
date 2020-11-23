#include <Wire.h>
/***************** CONFIG ETHERNET **********************/
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 2);
IPAddress server(192, 168, 1, 91);
EthernetClient ethClient;
PubSubClient mqttClient(ethClient);
/**************** CONFIG ETHERNET END ******************/


void setup()
{
  Serial.begin(57600);
  //oneWireSetup();
  pirSetup();
  //wireSetup();//komunikacja pomiedzy Arduino
  dhtSetup();
  //ethernetSetup();

  //stairsSetup();
  displaysSetup();
  //rfidSetup();
  lightSensorSetup();
  
}

void loop(){
  //oneWireLoop();
  dhtLoop();
  
  pirLoop();
  
  //wireLoop();
  //mqttLoop();

  //stairsLoop();
  displaysLoop();
  //rfidLoop();
  lightSensorLoop();
}

int attemptsCount = 5;

void mqttLoop(){
  if (!mqttClient.connected() && attemptsCount != 0) {
    attemptsCount--;
    mqttReconnect();
    Serial.print("attempt: "+attemptsCount);
    if(attemptsCount == 0){
      Serial.print("MQTT conection failed,stoped trying");
    }    
  }
  if(mqttClient.connected())
    mqttClient.loop();
}

void ethernetSetup(){

  mqttClient.setServer(server, 1883);
  mqttClient.setCallback(mqttCallback);

  Ethernet.begin(mac, ip);
  // Allow the hardware to sort itself out
  delay(1500);
  
}

void mqttCallback(char* topic, uint8_t* payload, uint32_t length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}



void mqttReconnect() {

  // Loop until we're reconnected
  //while 
  if (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (mqttClient.connect("arduinoClient")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      //Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      //delay(5000);
    }
  }
}

void mqttSetup(){
      // Once connected, publish an announcement...
      //mqttClient.publish("outTopic","hello world");
      // ... and resubscribe
      mqttClient.subscribe("inTopic");
      //mqttClient.subscribe("outTopic"); //outTopic zdefiniowane jako temat do którego wyzej wpisalem hello world a tutaj odbieram komunikaty
      //mqttClient.publish("outTopic","arduino wysyla do siebie");  
}

void mqqtSend(char* topic, char* message){
  mqttClient.publish(topic, message); 
}
