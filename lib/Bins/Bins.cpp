#include "Bins.h"

Bins::Bins(int triggerPin, int echoPin, int maxDistance) : NewPing(triggerPin, echoPin, maxDistance)
{
}

float Bins::calculatePercentage(int heightReading)
{
	return (heightReading * 100.0f) / BIN_HEIGHT;
}

int Bins::readFilledHeightCm()
{
	const int distance = ping_cm();
	const int filledheight = BIN_HEIGHT - distance;
	return filledheight;
}
