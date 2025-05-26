#include "ultrasonic.h"
#include "outputs/lcd/lcd.h"

NewPing sonarNonOrganic(
    SENSOR_TRIG_NONORGANIC_PIN,
    SENSOR_ECHO_NONORGANIC_PIN,
    MAX_DISTANCE);

NewPing sonarOrganic(
    SENSOR_TRIG_ORGANIC_PIN,
    SENSOR_ECHO_ORGANIC_PIN,
    MAX_DISTANCE);

int readLevelBinNonOrganic()
{
    int distance = sonarNonOrganic.ping_cm();
    return distance;
}

int readLevelBinOrganic()
{
    int distance = sonarOrganic.ping_cm();
    return distance;
}

void printLevels(const BinsLevel &params)
{
    lcdPrint({
        .row = 2,
        .column = 0,
        .message = "O: " + String(params.binsNonOrganic) + " cm | N: " + String(params.binsOrganic) + " cm",
    });
}