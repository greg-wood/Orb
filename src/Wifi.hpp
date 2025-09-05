#include <ESPmDNS.h>
#include <Arduino.h>
#include <WiFi.h>

extern const char *ssid;
extern const char *password;
extern boolean wifi_connected;

void connectToWiFi();
void initmDNS();
void setupOTA();