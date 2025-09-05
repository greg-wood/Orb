#include "Sleep.hpp"

void goToSleep()
{
    Serial.println("Going to sleep...");

    u8g2.clearDisplay();
    u8g2.sleepOn();
    delay(100);
    pinMode(TAP_GPIO, INPUT_PULLUP); // HIGH by default
    gpio_pullup_en((gpio_num_t)TAP_GPIO);
    gpio_hold_en((gpio_num_t)TAP_GPIO);   // Keep pull state during sleep
    gpio_pullup_en((gpio_num_t)TAP_GPIO); // Ensure the pin stays HIGH when idle

    esp_deep_sleep_enable_gpio_wakeup(TAP_PIN_MASK, ESP_GPIO_WAKEUP_GPIO_LOW);
    esp_deep_sleep_start();
}

boolean isWokenByTap()
{
    if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_GPIO)
    {
        Serial.println("Woken by tap!");
        return true;
    }
    return false;
}