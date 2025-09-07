#include <Arduino.h>
#include "esp_sleep.h"
#include "driver/gpio.h"
#include "Display.hpp"
#include "esp32-hal-gpio.h"

#define TAP_GPIO 3 // GPIO connected to tap module
#define TAP_PIN_MASK (1ULL << TAP_GPIO)

boolean isWokenByTap();
void goToSleep();
void checkSleep();
void updateActivity();