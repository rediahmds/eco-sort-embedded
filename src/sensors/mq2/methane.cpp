#include "methane.h"
#include <esp32-hal-adc.h>
#include <HardwareSerial.h>

int readMethane()
{
    int methaneADC = analogRead(methaneSensorPin);
    return methaneADC;
}

void printMethane()
{
    Serial.print("Methane ADC: ");

    int methane = readMethane();
    Serial.println(methane);
}