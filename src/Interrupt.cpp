#include "Interrupt.hpp"

// Example implementation (place in .cpp file):
volatile bool buttonPressed = false;

void IRAM_ATTR handleButtonInterrupt()
{
    buttonPressed = true;
}

void setupButtonInterrupt(uint8_t pin)
{
    pinMode(pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pin), handleButtonInterrupt, FALLING);
};