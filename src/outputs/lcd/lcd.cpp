#include "lcd.h"

LCD_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

void lcdInit()
{
    lcd.begin();
    lcd.backlight();

    lcd.setCursor(0, 0);
    lcd.print("  EcoSort Embedded  ");

    delay(4000);
    lcd.clear();
}

void lcdPrint(const LcdPrintParams &params)
{
    lcd.setCursor(params.column, params.row);
    lcd.print(params.message);
    delay(params.delay);
}