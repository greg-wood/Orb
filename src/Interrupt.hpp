#pragma once
#include <Arduino.h>

extern volatile bool shocked;

// Example ISR for a button press
void IRAM_ATTR handleButtonInterrupt();

// Attach interrupt to a pin
void setupButtonInterrupt(uint8_t pin);
