#include <Arduino.h>
#include "esp_sleep.h"
#include "driver/gpio.h"
#include "Display.hpp"

#define TAP_GPIO 3 // GPIO connected to tap module
#define TAP_PIN_MASK (1ULL << TAP_GPIO)

boolean isWokenByTap();
void goToSleep();
