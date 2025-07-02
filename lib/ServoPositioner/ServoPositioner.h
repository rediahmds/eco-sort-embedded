#include "ESP32Servo.h"

#define SERVO_PIN 13
#define INITIAL_POSITION 90
#define DEFAULT_DEGREE_ORGANIC 45
#define DEFAULT_DEGREE_ANORGANIC 135

class ServoPositioner : public Servo
{
public:
    ServoPositioner(int pin = SERVO_PIN);
    void toInitialPosition();
    void tiltToOrganincBin();
    void tiltToAnorganicBin();

    ~ServoPositioner();

private:
};
