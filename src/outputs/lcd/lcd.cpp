#include "lcd.h"

LCD_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

void lcdInit()
{
    lcd.begin();
    lcd.backlight();
}

void lcdPrint(const LcdPrintParams &params)
{
    if (params.clear)
    {
        lcdClear();
    }

    lcd.setCursor(params.column, params.row);
    lcd.print(params.message);
    delay(params.delay);

    if (params.clear)
    {
        lcd.clear();
    }
}

void lcdClear()
{
    lcd.clear();
}