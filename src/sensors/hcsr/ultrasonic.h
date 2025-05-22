#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "NewPing.h"

struct BinsLevel
{
    int binsNonOrganic;
    int binsOrganic;
};

const int SENSOR_TRIG_NONORGANIC_PIN = 32;
const int SENSOR_ECHO_NONORGANIC_PIN = 33;
const int MAX_DISTANCE = 100; // centimeters

extern NewPing sonarNonOrganic;

int readLevelBinNonOrganic();
void printLevels(const BinsLevel &params);

#endif