#ifndef OLED_H
#define OLED_H

#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"
#include "SPI.h"
#include "Wire.h"

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

extern Adafruit_SSD1306 oled;

bool oledBegin();

#endif