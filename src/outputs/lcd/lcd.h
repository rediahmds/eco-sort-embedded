// 0x27
// col, rows
#ifndef LCD_H
#define LCD_H

#include <LCD_I2C.h>

const int LCD_COLUMNS = 20;
const int LCD_ROWS = 4;
const int LCD_ADDRESS = 0x27;

extern LCD_I2C lcd;

void lcdInit();

struct LcdPrintParams
{
    int row;
    int column;
    String message;
    int delay = 0;
};
void lcdPrint(const LcdPrintParams &params);

#endif