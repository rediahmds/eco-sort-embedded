#include "Bins.h"

Bins::Bins(int triggerPin, int echoPin, int maxDistance) : NewPing(triggerPin, echoPin, maxDistance)
{
}

float Bins::calculatePercentage(int distance) {
    const float filledHeight = BIN_HEIGHT - distance;
    const float percentage = (filledHeight / BIN_HEIGHT) * 100.0f;
    return percentage;
}

float Bins::readLevelPercentage() {
    const int distance = ping_cm();
    const float percentage = calculatePercentage(distance);
    return percentage;
}
