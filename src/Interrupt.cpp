#include "Interrupt.hpp"

// Example implementation (place in .cpp file):
volatile bool buttonPressed = true;
volatile unsigned long lastInterruptTime = 0;
const unsigned long MIN_INTERVAL_MS = 3000; // Minimum 100ms between interrupts

void IRAM_ATTR handleButtonInterrupt()
{
    if (millis() - lastInterruptTime >= MIN_INTERVAL_MS)
    {
        buttonPressed = true;
        lastInterruptTime = millis(); // Update the last valid interrupt time
    }
}

void setupButtonInterrupt(uint8_t pin)
{
    pinMode(pin, INPUT_PULLDOWN);
    attachInterrupt(digitalPinToInterrupt(pin), handleButtonInterrupt, RISING);
};