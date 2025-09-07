#include "Sleep.hpp"

unsigned long lastActivityTime = 0;
const unsigned long inactivityTimeout = 300000; // 60 seconds

void updateActivity()
{
    lastActivityTime = millis();
}

void checkSleep()
{
    if (millis() - lastActivityTime > inactivityTimeout)
    {
        Serial.println("No activity detected. Going to sleep...");
        // esp_sleep_enable_timer_wakeup(10 * 1000000); // Wake up after 10 seconds
        Serial.flush();
        esp_deep_sleep_start();
    }
}
