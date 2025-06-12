#ifndef MQ2_H
#define MQ2_H

const int SENSOR_MQ2_PIN = 34;

class MQ2
{
public:
    MQ2(int pin = SENSOR_MQ2_PIN);
    int readCH4();

private:
    const int _pin;
};

#endif