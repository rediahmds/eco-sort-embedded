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

float readLevelBinNonOrganic()
{
    const int distance = sonarNonOrganic.ping_cm();
    const float percentage = calculatePercentage(distance);
    return distance;
}

float readLevelBinOrganic()
{
    const int distance = sonarOrganic.ping_cm();
    const float percentage = calculatePercentage(distance);
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

float calculatePercentage(int distance) {
    const float fillHeight = BIN_HEIGHT - distance;
    const float percentage = (fillHeight / BIN_HEIGHT) * 100.0f;
    return percentage;
}
