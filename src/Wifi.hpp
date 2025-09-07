#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>

extern const char *ssid;
extern const char *password;
extern boolean wifi_connected;

void connectToWiFi();
void setupOTA();