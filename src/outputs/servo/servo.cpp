#include "servo.h"

Servo servo;

void servoTiltR()
{
    servo.attach(SERVO_PIN);
    servo.write(45);
    delay(1000);
    servoStop();
}

void servoStop()
{
    servo.write(90);
    delay(1000);
    servo.detach();
}
