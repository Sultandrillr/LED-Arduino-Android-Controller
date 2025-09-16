//Function definitions for controlling the wifi connnectivity
//I would have done this over bluetooth but my pc has no wifi to use and my android is broken. I just deeped it. Will i even be able to use wifi? My pc is on wired connection. We will see

#include <Arduino.h>
#include "WifiControl.h"
#include <SPI.h>
#include <EEPROM.h>
#include <WiFiS3.h>
#include "LedControl.h"
//#include <WifiNINNA.h>

#define SSID_ADDRESS 0
#define PASSWORD 32
#define MAX_CREDENTIAL_SIZE 31

char ssid[MAX_CREDENTIAL_SIZE + 1];
char password[MAX_CREDENTIAL_SIZE + 1];

WiFiServer server(80);//this is HTTP. Unsecure but OK for testing. Before deployment I will need more libraries and extra stuff to make it in HTTPS. It will be better to make it more secure at a later date using HTTPS after i am finished the rest of ts btw port is 443

String htmlPage;
bool isWifiConnected = false;
//String arduino_IP = "";

MyWifi::MyWifi(){
  //this is only here so that the program can recognise the code I am going to execute
}
void MyWifi::setup_wifi(){
  load_credentials();
  if (strlen(ssid) > 0){
    connect_to_wifi();
  }
  if (WiFi.status() != WL_CONNECTED) {
    isWifiConnected = false;
    start_ap();
    setup_server();
    
  }
}

void MyWifi::load_credentials(){
  //EEPROM.begin(64);   apparently I dont need this?
  EEPROM.get(SSID_ADDRESS, ssid);
  EEPROM.get(PASSWORD, password);
  EEPROM.end();
}

void MyWifi::save_credentials(const char* newSSID, const char* newPassword){

  //I forgot ts for ages. Better data integrity if i erase the previous data before I write new data. Less chance of breaking sum.
  for (int i = 0; i < MAX_CREDENTIAL_SIZE + 1; i++){
    EEPROM.write(SSID_ADDRESS + i, 0);
    EEPROM.write(PASSWORD + i, 0);
  }

  //EEPROM.begin(64);//sets the size    again allegedly I dont need this
  EEPROM.put(SSID_ADDRESS, newSSID);
  EEPROM.put(PASSWORD, newPassword);
  EEPROM.end();
}

void MyWifi::connect_to_wifi(){
  Serial.println("Attempting to connect to wifi");
  Serial.print("SSID:");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  unsigned long startAttemptTime = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 30000){
    Serial.print("|");
    delay(501);
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED){
    Serial.println("Wifi connection succesful...");
    isWifiConnected = true;
  } else {
      Serial.println("Connection failed");
  } 
}

void MyWifi::start_ap(){
  Serial.println("Starting access point mode...");
  WiFi.beginAP("Light_Setup");
  while (WiFi.status() != WL_AP_LISTENING){delay(100);}
  Serial.println("Access point mode active. SSID is Light_Setup");
}

void MyWifi::serve_wifi_setup(WiFiClient &client){
     htmlPage = HTMLPage();
     client.println("HTTP/1.1 200 OK");
     client.println("content-Type: text\html");
     client.println("Connection: close");
     client.println();
     client.println(htmlPage);
  }
void MyWifi::handle_wifi_credentials(WiFiClient &client, String &request){

    String ssidVal = extract_input(request, "SSID=");
    String passwordVal = extract_input(request, "Password=");

    if(ssidVal.length() > 0 && passwordVal.length() > 0){
      save_credentials(ssidVal.c_str(), passwordVal.c_str());
      client.println("HTTP/1.1 200 OK");
      client.println("content-Type: text\html");
      client.println("Connection: close");
      client.println();
      client.println("<h1>Saved...Please restart the Arduino");
      //my dumbass didnt know I could restart only the ESP32 so i was resetting the whole thing like an idiot. we fixed up.   nvm i cant do that i wasnt stupid. I was restarting it with them 2 pins. include instructions when asking to restart
      //delay(2000);
      //ESP.restart();
    }
  }

void MyWifi::handle_LED_control(WiFiClient &client, String &request){
  if(request.indexOf("r=")){
    LedControl::redBright = extractInt(request, "r=");
  }
  if(request.indexOf("g=")){
    LedControl::greenBright = extractInt(request, "g=");
  }
  if(request.indexOf("b=")){
    LedControl::blueBright = extractInt(request, "b=");
  }
}

void MyWifi::send_all_device_status(WiFiClient &client){
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: application/json");
  client.println("Access-Control-Allow-Origin: *");
  client.println("Connection: close");
  client.println();
  byte mac[6];
  WiFi.macAddress(mac);
  char macStr[18];
  sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[5], mac[4], mac[3], mac[2], mac[1], mac[0]);
  client.print("{\"device\":\"LED_Controller\",\"mac\":\"");
  client.print(macStr);
  client.print("\",\"ip\":\"");
  client.print(WiFi.localIP());
  client.print("\",\"connected\":");
  client.print(isWifiConnected ? "true" : "false");
  client.print(",\"red\":");
  client.print(LedControl::redBright);
  client.print(",\"green\":");
  client.print(LedControl::greenBright);
  client.print(",\"blue\":");
  client.print(LedControl::blueBright);
  client.println("}");
}

void MyWifi::send_rgb_actual_status(WiFiClient &client, String &request){
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: application/json");
  client.println("Access-Control-Allow-Origin: *");
  client.println("Connection: close");
  client.println();
  client.print(",\"red\":");
  client.print(LedControl::redBright);
  client.print(",\"green\":");
  client.print(LedControl::greenBright);
  client.print(",\"blue\":");
  client.print(LedControl::blueBright);
  client.println("}");//sends only the RGB values because sending more data than i would need to would just make ts slower and affect syncornisation. Ik its not sum huge but it matters lil bro
}

//stolen code, may need to be fixed/improved
String MyWifi::HTMLPage(){
  String page = "<!DOCTYPE html><html><body>"; // Start of HTML document
  page += "<h1>Wi-Fi Setup</h1>";             // Add a title
  page += "<form method='POST'>";             // Create a form for SSID and password input
  page += "SSID: <input type='text' name='ssid'><br>";  // Input field for SSID
  page += "Password: <input type='password' name='pass'><br>"; // Input field for password
  page += "<input type='submit' value='Connect'>";      // Submit button
  page += "</form>";                                    // End of form
  page += "</body></html>";                             // End of HTML document
  return page;                                          // Return the HTML as a string
}

String MyWifi::extract_input(String &request, const String &key){
  int start = request.indexOf(key) + key.length();
  int end = request.indexOf("&", start);
  if (end == -1){
    end = request.indexOf(" ", start);
  }
  return request.substring(start, end);
}

void MyWifi::setup_server(){
  server.begin();
  Serial.println("Web server is active");
}

void MyWifi::handle_web_requests(){
  WiFiClient client = server.available();
  String request = client.readStringUntil('\r');
  client.flush();

  if(request.indexOf("GET / ") >= 0 && request.indexOf("POST") == -1){ //when the client is asking for sum, give them this...    added 2nd condition to ensure it only executes if not POST request   I also added a space after GET / so that it will not call in the case of GET /led. Im too sharp bro
    serve_wifi_setup(client);
  }
  if(request.indexOf("POST /") >= 0){
    handle_wifi_credentials(client, request);
  }
  if(request.indexOf("GET /led") >= 0){
    handle_LED_control(client, request);
  }
  if(request.indexOf("GET /status") >= 0){
    handle_LED_control(client, request);
  }
  if(request.indexOf("GET /rgb") >= 0){
    handle_LED_control(client, request);
  }

}
int MyWifi::extractInt(String &request, const String &key){
  String value = extract_input(request, key);
  return value.toInt();
}
// Add UUID. I didnt even know ts was important. If i forget why, it just allows it to have a more consistent connection and some safety stuff to allow for



