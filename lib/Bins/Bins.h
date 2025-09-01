#ifndef BINS_H
#define BINS_H

#include "NewPing.h"

const int SENSOR_TRIG_ANORGANIC_PIN = 32;
const int SENSOR_ECHO_ANORGANIC_PIN = 33;

const int SENSOR_TRIG_ORGANIC_PIN = 5;
const int SENSOR_ECHO_ORGANIC_PIN = 18;

const int MAX_DISTANCE = 20; // centimeters

class Bins : public NewPing
{
public:
	Bins(int triggerPin, int echoPin, int maxDistance = MAX_DISTANCE);

	int readFilledHeightCm();
	float calculatePercentage(int distance);

private:
	const int BIN_HEIGHT = MAX_DISTANCE; // in cm
};

#endif