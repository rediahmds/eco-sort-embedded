#ifndef LCD_H
#define LCD_H

#include <LCD_I2C.h>

const int LCD_COLUMNS = 20;
const int LCD_ROWS = 4;
const int LCD_ADDRESS = 0x27;

struct LcdPrintParams
{
    int row = 0;
    int column = 0;
    String message;
    int delay = 0;
    bool clear = false;
};

extern LCD_I2C lcd;

void lcdInit();
void lcdPrint(const LcdPrintParams &params);
void lcdClear();

#endif