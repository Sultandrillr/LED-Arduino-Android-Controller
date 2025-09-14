#include <IRremote.hpp>
#include <SPI.h>
#include "WifiControl.h"//no longer needed, found a library...... bun the library I am better
//#include <r4-wifi-manager/constants.hpp>
//#include <r4-wifi-manager/r4-wifi-manager.hpp>
#include "LedControl.h"

//String createHtmlPage;

IRrecv IR(11);
const int redPin = 6;
const int greenPin = 10;
const int bluePin = 5;

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
    analogWrite(redPin,LedControl::redBright);
    analogWrite(greenPin,LedControl::greenBright);
    analogWrite(bluePin,LedControl::blueBright);
  }

void lights_off(){
  LedControl::redBright = 0;
  LedControl::greenBright = 0;
  LedControl::blueBright = 0;
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
  for (LedControl::redBright; LedControl::redBright < 255; LedControl::redBright++){
    if (irCode == -200544512){
      check_LED();
      //delay(fadeDelay/2);
      update_LED();
      //delay(fadeDelay/2);
    }
  }

  //red to yellow
  for (LedControl::greenBright; LedControl::greenBright < 255; LedControl::greenBright++){
    if (irCode == -200544512){
      check_LED();
      delay(fadeDelay/2);
      update_LED();
      delay(fadeDelay/2);
    }
  }

  //yellow to green
  for (LedControl::redBright; LedControl::redBright > 0; LedControl::redBright--){
    if (irCode == -200544512){
      check_LED();
      delay(fadeDelay/2);
      update_LED();
      delay(fadeDelay/2);
    }
  }

  //green to teal
  for (LedControl::blueBright; LedControl::blueBright < 255; LedControl::blueBright++){
    if (irCode == -200544512){
      check_LED();
      delay(fadeDelay/2);
      update_LED();
      delay(fadeDelay/2);
    }
  }
  //teal to blue
  for (LedControl::greenBright; LedControl::greenBright > 0; LedControl::greenBright--){
    if (irCode == -200544512){
      check_LED();
      delay(fadeDelay/2);
      update_LED();
      delay(fadeDelay/2);
    }
  }

  //blue to purple
  for (LedControl::redBright; LedControl::redBright < 255; LedControl::redBright++){
    if (irCode == -200544512){
      check_LED();
      delay(fadeDelay/2);
      update_LED();
      delay(fadeDelay/2);
    }
  }

  //purple to red
  for (LedControl::blueBright; LedControl::blueBright > 0; LedControl::blueBright--){
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
    LedControl::redBright = 255;
    LedControl::greenBright = 0;
    LedControl::blueBright = 0;
    update_LED();
    irCode = 0;
    break;
  case -100274432:
    //GREEN
    LedControl::redBright = 0;
    LedControl::greenBright = 255;
    LedControl::blueBright = 0;
    update_LED();
    irCode = 0;
    break;
  
  case -116986112:
    //BLUE
    LedControl::redBright = 0;
    LedControl::greenBright = 0;
    LedControl::blueBright = 255;
    update_LED();
    irCode = 0;
    break;
  
  case -150409472:
    //red up 20
    LedControl::redBright += 20;
    update_LED();
    irCode = 0;
    break;

  case -217256192:
    //red down 20
    LedControl::redBright -= 20;
    update_LED();
    irCode = 0;
    break;

  case -167121152:
    //green up 20
    LedControl::greenBright += 20;
    update_LED();
    irCode = 0;
    break;

  case -233967872:
    //green down 20
    LedControl::greenBright -= 20;
    update_LED();
    irCode = 0;
    break;

  case -183832832:
    //blue up 20
    LedControl::blueBright += 20;
    update_LED();
    irCode = 0;
    break;
  case -250679552:
    //blue down 20
    LedControl::blueBright -= 20;
    update_LED();
    irCode = 0;
    break;
  
  case -50139392:
    //Lights Off
    LedControl::redBright = 0;
    LedControl::greenBright = 0;
    LedControl::blueBright = 0;
    update_LED();
    irCode = 0;
    break;

  case -33427712:
    //All Down
    LedControl::redBright -= 20;
    LedControl::greenBright -= 20;
    LedControl::blueBright -= 20;
    update_LED();
    irCode = 0;
    break;

  case -16716032:
    //All Up
    LedControl::redBright += 20;
    LedControl::greenBright += 20;
    LedControl::blueBright += 20;
    update_LED();
    irCode = 0;
    break;

  case -133697792:
    //White.........
    LedControl::redBright = 255;
    LedControl::greenBright = 255;
    LedControl::blueBright = 255;
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
    LedControl::blueBright -= 10;
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
