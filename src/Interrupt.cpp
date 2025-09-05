#include "Interrupt.hpp"

// Example implementation (place in .cpp file):
volatile bool buttonPressed = true;

void IRAM_ATTR handleButtonInterrupt()
{
    buttonPressed = true;
}

void setupButtonInterrupt(uint8_t pin)
{
    pinMode(pin, INPUT_PULLDOWN);
    attachInterrupt(digitalPinToInterrupt(pin), handleButtonInterrupt, RISING);
};