
#ifndef WifiControl_H
#define WifiControl_H
#include <WiFiS3.h>//just for the errors

class MyWifi{
  public:
  MyWifi();
  void setup_wifi();
  void load_credentials();
  void save_credentials(const char *, const char *);
  void connect_to_wifi();
  void start_ap();
  void handle_client(WiFiClient &client);
  String HTMLPage();
  String extract_input(String &request, const String &key);
  void setup_server();
};

#endif