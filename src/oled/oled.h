#ifndef OLED_H
#define OLED_H

#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"
#include "SPI.h"
#include "Wire.h"

const int OLED_WIDTH = 128;
const int OLED_HEIGHT = 64;
const int OLED_RESET = -1;
const int OLED_ADDRESS = 0x3D;

extern Adafruit_SSD1306 oled;

bool oledBegin();

#endif