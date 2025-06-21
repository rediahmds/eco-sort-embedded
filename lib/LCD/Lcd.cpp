#include "Lcd.h"

LCD::LCD(int address, int columns, int rows) : LCD_I2C(address, columns, rows), _cols(columns) {}

void LCD::initialize()
{
    begin();
    backlight();
}

void LCD::printMessageAt(int col, int row, String message)
{
    setCursor(col, row);
    print(message);
}

void LCD::clearRow(int row)
{
    setCursor(0, row);
    for (int r = 0; r < _cols; r++)
    {
        print(" ");
    }
}

void LCD::printCentered(int row, String message)
{
    int padding = (_cols - message.length()) / 2;
    if (padding == 0)
        padding = 0;

    setCursor(padding, row);
    print(message);
}

void LCD::printScrollLeft(int row, String message, int delayms)
{
    printMessageAt(0, row, message);
    for (int i = 0; i < message.length(); i++)
    {
        scrollDisplayLeft();
        delay(delayms);
    }
}