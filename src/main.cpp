#include <Arduino.h>
#include <ArduinoOTA.h>
#include "Wifi.hpp"
#include "Display.hpp"
#include "Interrupt.hpp"
#include "Sleep.hpp"

// updateActivity(); // Call this whenever activity occurs
// checkSleep();     // Call

void setup()
{
  Serial.begin(115200);
  delay(500);
  Serial.println("Booting...");
  connectToWiFi();
  initmDNS();
  setupOTA();
  setupDisplay();
  setupButtonInterrupt(TAP_GPIO);
}

void loop()
{

  ArduinoOTA.handle();

  if (buttonPressed)
  {
    Serial.println("Button pressed!");
    buttonPressed = false;
    show8BallResponse();
  }
  Serial.println("In Loop");
}
