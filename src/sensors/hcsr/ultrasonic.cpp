#include "ultrasonic.h"
#include "outputs/lcd/lcd.h"

NewPing sonarNonOrganic(
    SENSOR_TRIG_NONORGANIC_PIN,
    SENSOR_ECHO_NONORGANIC_PIN,
    MAX_DISTANCE);

NewPing sonarOrganic();

int readLevelBinNonOrganic()
{
    int distance = sonarNonOrganic.ping_cm();
    return distance;
}

void printLevels(const BinsLevel &params)
{
    lcdPrint({
        .row = 2,
        .column = 0,
        .message = "Org: " + String(params.binsNonOrganic) + " cm",
    });
}