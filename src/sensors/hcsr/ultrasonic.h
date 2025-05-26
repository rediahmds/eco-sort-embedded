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

const int SENSOR_TRIG_ORGANIC_PIN = 25;
const int SENSOR_ECHO_ORGANIC_PIN = 26;

const int MAX_DISTANCE = 100; // centimeters

extern NewPing sonarNonOrganic;
extern NewPing sonarOrganic;

int readLevelBinNonOrganic();
int readLevelBinOrganic();
void printLevels(const BinsLevel &params);

#endif