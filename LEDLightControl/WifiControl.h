
#ifndef WifiControl_H
#define WifiControl_H
#include <WiFiS3.h>//just for the errors

class MyWifi{
  public:
  MyWifi();
  int extractInt(String &request, const String &key);
  void setup_wifi();
  void load_credentials();
  void save_credentials(const char *, const char *);
  void connect_to_wifi();
  void start_ap();
  void serve_wifi_setup(WiFiClient &client);
  void handle_wifi_credentials(WiFiClient &client, String &request);
  void handle_LED_control(WiFiClient &client, String &request);
  void send_all_device_status(WiFiClient &client);
  void send_rgb_actual_status(WiFiClient &client, String &request);
  String HTMLPage();
  String extract_input(String &request, const String &key);
  void setup_server();
  void handle_web_requests();
};

#endif