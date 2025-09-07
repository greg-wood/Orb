#pragma once

#include <Arduino.h>
#include <vector>
#include <Wire.h>

#include <U8g2lib.h>

extern U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2;

void setupDisplay();
void show8BallResponse();
void drawWrappedCenteredText(const char *text, int maxWidth, int lineHeight, int screenHeight);
void clearDisplay();