#include "methane.h"

#include <esp32-hal-adc.h>
#include <HardwareSerial.h>
#include <outputs/lcd/lcd.h>

int readMethane()
{
    int methaneADC = analogRead(SENSOR_METHANE);
    return methaneADC;
}

void printMethane(int methane)
{
    Serial.print("CH4: ");
    Serial.println(methane);

    lcdPrint({
        .row = 1,
        .message = "CH4: " + String(methane),
    });
}