#ifndef BINS_H
#define BINS_H

#include "NewPing.h"

const int SENSOR_TRIG_ANORGANIC_PIN = 32;
const int SENSOR_ECHO_ANORGANIC_PIN = 33;

const int SENSOR_TRIG_ORGANIC_PIN = 25;
const int SENSOR_ECHO_ORGANIC_PIN = 26;

const int MAX_DISTANCE = 100; // centimeters
const int BIN_HEIGHT = 20;    // centimeters

class Bins : public NewPing
{
public:
    Bins(int triggerPin, int echoPin, int maxDistance = MAX_DISTANCE);

    float readLevelPercentage();

private:
    const int BIN_HEIGHT = 50; // in cm
    float calculatePercentage(int distance);
};

#endif