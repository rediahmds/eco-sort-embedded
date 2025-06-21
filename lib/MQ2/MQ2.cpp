#include "MQ2.h"
#include "HardwareSerial.h"

MQ2::MQ2(int pin) : _pin(pin) {}

int MQ2::readCH4()
{
    const int ch4 = analogRead(_pin);
    return ch4;
}