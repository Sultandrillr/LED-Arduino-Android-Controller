#include <IRremote.hpp>
#include <SPI.h>
#include "WifiControl.h"//no longer needed, found a library
#include <r4-wifi-manager/constants.hpp>
#include <r4-wifi-manager/r4-wifi-manager.hpp>

//String createHtmlPage;

IRrecv IR(11);
const int redPin = 6;
const int greenPin = 10;
const int bluePin = 5;

int redBright = 225;
int greenBright = 225;
int blueBright = 225;

int fadeDelay = 10;

long int irCode = 20000;

void(* resetFunc) (void) = 0;

void setup() {
  //pinMode(redPin,OUTPUT);
  //pinMode(greenPin,OUTPUT);
  //pinMode(bluePin,OUTPUT);
  ////WiFiManager WiFiManager;
  Serial.begin(115200);

//  loadCredentials();
//  if (strlen(ssid) > 0){
//    connectToWifi();
//  }

//  if (WiFi.status() != WL_CONNECTED) {
//    startAP();
//    setupWebServer();
//  }
  IR.begin(11, true);
  Serial.println("Setup complete");
}

void update_LED()
  {
    analogWrite(redPin,redBright);
    analogWrite(greenPin,greenBright);
    analogWrite(bluePin,blueBright);
  }

void lights_off(){
  int redBright = 0;
  int greenBright = 0;
  int blueBright = 0;
}
void check_LED(){
  if (IR.decode() && IR.decodedIRData.decodedRawData, HEX != 0){
    Serial.println(IR.decodedIRData.decodedRawData, HEX);
    irCode = (IR.decodedIRData.decodedRawData);
    IR.resume();
  }
}

void fade_LED(){
  //dark to red
  for (redBright; redBright < 255; redBright++){
    if (irCode == -200544512){
      check_LED();
      //delay(fadeDelay/2);
      update_LED();
      //delay(fadeDelay/2);
    }
  }

  //red to yellow
  for (greenBright; greenBright < 255; greenBright++){
    if (irCode == -200544512){
      check_LED();
      delay(fadeDelay/2);
      update_LED();
      delay(fadeDelay/2);
    }
  }

  //yellow to green
  for (redBright; redBright > 0; redBright--){
    if (irCode == -200544512){
      check_LED();
      delay(fadeDelay/2);
      update_LED();
      delay(fadeDelay/2);
    }
  }

  //green to teal
  for (blueBright; blueBright < 255; blueBright++){
    if (irCode == -200544512){
      check_LED();
      delay(fadeDelay/2);
      update_LED();
      delay(fadeDelay/2);
    }
  }
  //teal to blue
  for (greenBright; greenBright > 0; greenBright--){
    if (irCode == -200544512){
      check_LED();
      delay(fadeDelay/2);
      update_LED();
      delay(fadeDelay/2);
    }
  }

  //blue to purple
  for (redBright; redBright < 255; redBright++){
    if (irCode == -200544512){
      check_LED();
      delay(fadeDelay/2);
      update_LED();
      delay(fadeDelay/2);
    }
  }

  //purple to red
  for (blueBright; blueBright > 0; blueBright--){
    if (irCode == -200544512){
      check_LED();
      delay(fadeDelay/2);
      update_LED();
      delay(fadeDelay/2);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
if (IR.decode()){
  Serial.println(IR.decode());
  Serial.println(IR.decodedIRData.decodedRawData, HEX);
  irCode = (IR.decodedIRData.decodedRawData);
  Serial.println(irCode);
  
  switch (irCode) {
  //RED
  case -83562752:
    redBright = 255;
    greenBright = 0;
    blueBright = 0;
    update_LED();
    irCode = 0;
    break;
  case -100274432:
    //GREEN
    redBright = 0;
    greenBright = 255;
    blueBright = 0;
    update_LED();
    irCode = 0;
    break;
  
  case -116986112:
    //BLUE
    redBright = 0;
    greenBright = 0;
    blueBright = 255;
    update_LED();
    irCode = 0;
    break;
  
  case -150409472:
    //red up 20
    redBright += 20;
    update_LED();
    irCode = 0;
    break;

  case -217256192:
    //red down 20
    redBright -= 20;
    update_LED();
    irCode = 0;
    break;

  case -167121152:
    //green up 20
    greenBright += 20;
    update_LED();
    irCode = 0;
    break;

  case -233967872:
    //green down 20
    greenBright -= 20;
    update_LED();
    irCode = 0;
    break;

  case -183832832:
    //blue up 20
    blueBright += 20;
    update_LED();
    irCode = 0;
    break;
  case -250679552:
    //blue down 20
    blueBright -= 20;
    update_LED();
    irCode = 0;
    break;
  
  case -50139392:
    //Lights Off
    redBright = 0;
    greenBright = 0;
    blueBright = 0;
    update_LED();
    irCode = 0;
    break;

  case -33427712:
    //All Down
    redBright -= 20;
    greenBright -= 20;
    blueBright -= 20;
    update_LED();
    irCode = 0;
    break;

  case -16716032:
    //All Up
    redBright += 20;
    greenBright += 20;
    blueBright += 20;
    update_LED();
    irCode = 0;
    break;

  case -133697792:
    //White.........
    redBright = 255;
    greenBright = 255;
    blueBright = 255;
    update_LED();
    irCode = 0;
    break;

  case -200544512:
    //Rainbow.................................
    lights_off();
    IR.resume();
    while (irCode == -200544512){
      fade_LED();
      check_LED();
      
    }
    irCode = 0;
    break;

  case 6:
    //blue down 10
    blueBright -= 10;
    update_LED();
    irCode = 0;
    break;

  }

  //redBright = random(0,225);
  //greenBright = random(0,225);
  //blueBright = random(0,225);
  //update_LED();
  
  delay(400);
  IR.resume();

}
}
