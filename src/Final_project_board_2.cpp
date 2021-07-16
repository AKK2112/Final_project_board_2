/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "d:/Labs/Final_project_board_2/src/Final_project_board_2.ino"
#include <MQTT.h>
#include "blynk.h"
#include "SparkFun_VCNL4040_Arduino_Library.h" 
#include "wire.h"


void setup();
void loop();
#line 7 "d:/Labs/Final_project_board_2/src/Final_project_board_2.ino"
SYSTEM_THREAD(ENABLED);
VCNL4040 sensor;


void callback(char* topic, byte* payload, unsigned int length);

MQTT client("lab.thewcl.com", 1883, callback);//which connection it should connect to


// recieve message
void callback(char* topic, byte* payload, unsigned int length) 
{
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  //Serial.printlnf("%s",p);
  
  
}
//allows the blynk text input to be displayed on the MQTT thread
BLYNK_WRITE(V1) {
  String inputText = param.asStr();
  client.publish("paris", inputText);//paris is the thread we made and it is our initials. Yes, I know, so origional :)
}
void setup() {
  Serial.begin(9600);

  pinMode(D7, OUTPUT); // blue light
  Blynk.begin("DISy_9aRsQHnyt8mtvZXh09rT-tdy72R", IPAddress(167, 172, 234, 162), 9090);
  
  sensor.begin(); //turns on the proximity sensor
  Wire.begin(); //Join i2c bus
  sensor.powerOnProximity();
  sensor.powerOnAmbient();
}

void loop() {
  Blynk.run();
  
  unsigned int proxValue = sensor.getProximity(); 
  String z = (String)proxValue;
  Serial.println(z);
  client.publish("tjProximity", z);
  client.subscribe("paris");
  unsigned int ambientValue = sensor.getAmbient();
  String x = (String)ambientValue;
  Serial.println(x);
  client.publish("tjAmbient", x);
  client.subscribe("paris");
  

  if (client.isConnected()) {
    
    client.subscribe("paris");//subscribes to the thread so it can recieve messages. 
    client.loop();
  } else {
    client.connect(System.deviceID());
  }
  delay(1000);


}