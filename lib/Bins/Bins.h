#ifndef BINS_H
#define BINS_H

#include "NewPing.h"

class Bins : public NewPing
{
public:
    Bins(int triggerPin, int echoPin, int maxDistance = 100);

    float readLevelPercentage();

private:
    const int BIN_HEIGHT = 50; // in cm
    float calculatePercentage(int distance);
};

#endif