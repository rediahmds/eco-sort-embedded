#ifndef LCD_H
#define LCD_H

#include "LCD_I2C.h"

const int LCD_COLUMNS = 20;
const int LCD_ROWS = 4;
const int LCD_ADDRESS = 0x27;

class LCD : public LCD_I2C
{
public:
    LCD(int address = LCD_ADDRESS, int columns = LCD_COLUMNS, int rows = LCD_ROWS);
    void initialize();
    void printMessageAt(int col, int row, String message);
    void clearRow(int row);
    void printCentered(int row, String message);

private:
    const int _cols;
};

#endif