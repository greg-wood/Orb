#include "Sleep.hpp"

unsigned long lastActivityTime = 0;
const unsigned long inactivityTimeout = 300000; 
unsigned long currentTime;

void updateActivity()
{
    lastActivityTime = millis();
}

void checkSleep()
{
    currentTime = millis();
    delay(100);
    if ((currentTime - lastActivityTime) > inactivityTimeout)
    {
        Serial.println("No activity detected. Going to sleep...");
        // esp_sleep_enable_timer_wakeup(10 * 000); // Wake up after 10 seconds
        Serial.flush();
        clearDisplay();    
        drawWrappedCenteredText("Going to sleep", 128, 12, 64); // screen width, line height, screen height  
        flushDisplay();
        delay(30000);
        clearDisplay();
        esp_deep_sleep_start();
    }
}
