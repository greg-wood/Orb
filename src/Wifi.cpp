#include <Arduino.h>
#include "Wifi.hpp"

boolean wifi_connected = false;
const char *ssid = "WoodPrivate";
const char *password = "woodgreg";

// Prints a human-readable WiFi error message based on status code
void printWiFiErrorMessage(int status)
{
    switch (status)
    {
    case WL_IDLE_STATUS:
        Serial.println("WiFi Status: Idle");
        break;
    case WL_NO_SSID_AVAIL:
        Serial.println("WiFi Error: No SSID Available");
        break;
    case WL_SCAN_COMPLETED:
        Serial.println("WiFi Status: Scan Completed");
        break;
    case WL_CONNECTED:
        Serial.println("WiFi Status: Connected");
        break;
    case WL_CONNECT_FAILED:
        Serial.println("WiFi Error: Connection Failed");
        break;
    case WL_CONNECTION_LOST:
        Serial.println("WiFi Error: Connection Lost");
        break;
    case WL_DISCONNECTED:
        Serial.println("WiFi Status: Disconnected");
        break;
    default:
        Serial.print("WiFi Status: Unknown code ");
        Serial.println(status);
        break;
    }
}

// Connects to WiFi and prints status/errors to Serial
void connectToWiFi()
{
    Serial.println("Connecting to WiFi...");
    WiFi.mode(WIFI_STA);
    WiFi.setHostname("Orb"); // Set the hostname before connecting
    WiFi.begin(ssid, password);

    int maxAttempts = 20;
    int attempt = 0;
    wifi_connected = false;
    while (WiFi.status() != WL_CONNECTED && attempt < maxAttempts)
    {
        delay(500);
        Serial.print(".");
        attempt++;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("\nWiFi connected!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
        wifi_connected = true;
    }
    else
    {
        Serial.println("\nFailed to connect to WiFi.");
        Serial.print("Status code: ");
        Serial.println(WiFi.status());
        printWiFiErrorMessage(WiFi.status());
    }
}


// Initializes mDNS with hostname "Orb.local"
/*void initmDNS()
{
    if (!MDNS.begin("greg"))
    { // Hostname will be "Orb.local"
        Serial.println("Error setting up mDNS responder!");
        while (1)
        {
            delay(1000);
        }
    }
    else
    {
        Serial.println("mDNS responder started: Orb.local");
    }
}
    */


// Initializes OTA update functionality
void setupOTA()
{
    ArduinoOTA.onStart([]()
                       { Serial.println("OTA Update Start"); });
    ArduinoOTA.onEnd([]()
                     { Serial.println("OTA Update End"); });
    ArduinoOTA.onError([](ota_error_t error)
                       {
        Serial.printf("OTA Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed"); });
        ArduinoOTA.setHostname("Orb"); // Set OTA hostname
    ArduinoOTA.begin(); // false to disable MDNS
    Serial.println("OTA Ready");
}
