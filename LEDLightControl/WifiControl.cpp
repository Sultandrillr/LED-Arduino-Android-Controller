//Function definitions for controlling the wifi connnectivity

#include <Arduino.h>
#include "WifiControl.h"
//#include 

#include <EEPROM.h>
#include <WiFiS3.h>
//#include <WifiNINNA.h>

#define SSID_ADDRESS 0
#define PASSWORD 32
#define MAX_CREDENTIAL_SIZE 31

char ssid[MAX_CREDENTIAL_SIZE + 1];
char password[MAX_CREDENTIAL_SIZE + 1];

String htmlPage;

MyWifi::MyWifi(){
  //this is only here so that the program can recognise the code I am going to execute
}
void MyWifi::setup_wifi(){
  load_credentials();
  if (strlen(ssid) > 0){
    connect_to_wifi();
  }
  if (WiFi.status() != WL_CONNECTED) {
    start_ap();
    setup_server();
  }
}

void MyWifi::load_credentials(){
  EEPROM.begin(/*64*/);
  EEPROM.get(SSID_ADDRESS, ssid);
  EEPROM.get(PASSWORD, password);
  EEPROM.end();
}

void MyWifi::save_credentials(const char* newSSID, const char* newPassword){
  EEPROM.begin(/*64*/);
  EEPROM.put(SSID_ADDRESS, newSSID);
  EEPROM.put(PASSWORD, newPassword);
  EEPROM.end();
}

void MyWifi::connect_to_wifi(){
  Serial.println("Attempting to connect to wifi");
  WiFi.begin(ssid, password);
  unsigned long startAttemptTime = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 30000){
    Serial.println("|");
    delay(501);
  }

  if (WiFi.status() == WL_CONNECTED){
    Serial.println("Wifi connection succesful...");
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

void MyWifi::handle_client(WiFiClient &client){
  String request = client.readStringUntil('\r');
  client.flush();

  if(request.indexOf("GET /") >= 0){
     htmlPage = HTMLPage();
     client.println("HTTP/1.1 200 OK");
     client.println("content-Type: text\html");
     client.println("Connection: close");
     client.println();
     client.println(htmlPage);
  }

  if(request.indexOf("POST /") >= 0){
    String ssidVal = extract_input(request, "SSID=");
    String passwordVal = extract_input(request, "Password=");

    if(ssidVal.length() > 0 && passwordVal.length() > 0){
      save_credentials(ssidVal.c_str(), passwordVal.c_str());
      client.println("HTTP/1.1 200 OK");
      client.println("content-Type: text\html");
      client.println("Connection: close");
      client.println();
      client.println("<h1>Saved...Please restart the Arduino");
    }
  }
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

/*void MyWifi::setup_server(){
  server.begin();
  Serial.println("Web server is active");
}*/



