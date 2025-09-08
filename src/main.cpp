#include <Arduino.h>
#include <ArduinoOTA.h>
#include "Wifi.hpp"
#include "Display.hpp"
#include "Interrupt.hpp"
#include "Sleep.hpp"


void setup()
{
  Serial.begin(115200);
  delay(500);
  Serial.println("Booting...");
  connectToWiFi();
//  initmDNS();
  setupOTA();
  setupDisplay();
  setupButtonInterrupt(TAP_GPIO);
  updateActivity(); // Call this whenever activity occurs

}
  int Mins = 0;

void loop()
{
  currentTime = millis();
  ArduinoOTA.handle();

  if (shocked)
  {
    Serial.println("Shocked!");
    shocked = false;
    updateActivity(); // Call this whenever activity occurs
    show8BallResponse();
  }
  if ((currentTime % 60000) == 0 ) {
  Serial.print("In Loop ");
  Serial.print(currentTime);
  Serial.print(" ");
  Serial.println(++Mins);
  Serial.flush();
  }
  checkSleep(); 
}
