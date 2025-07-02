#include "ServoPositioner.h"

ServoPositioner::ServoPositioner(int pin) {}

void ServoPositioner::toInitialPosition()
{
    // const bool isAttached = attached();
    // if (!isAttached)
    // {
    //     attach(_pin);
    // }
    write(INITIAL_POSITION);
}

void ServoPositioner::tiltToOrganincBin()
{
    // const bool isAttached = attached();
    // if (!isAttached)
    // {
    //     attach(_pin);
    // }
    write(DEFAULT_DEGREE_ORGANIC);
}

void ServoPositioner::tiltToAnorganicBin()
{
    // const bool isAttached = attached();
    // if (!isAttached)
    // {
    //     attach(_pin);
    // }
    write(DEFAULT_DEGREE_ANORGANIC);
}

ServoPositioner::~ServoPositioner() {}
