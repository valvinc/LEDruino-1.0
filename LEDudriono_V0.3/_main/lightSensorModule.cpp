#include "lightSensorModule.h"
#include "config.h"
#include <Arduino.h>

void initLightSensor() {
    pinMode(LIGHT_SENSOR_PIN, INPUT);  // Set the light sensor pin as input
}

int readLightSensor() {
    int lightValue = analogRead(LIGHT_SENSOR_PIN);  // Read analog value from the light sensor
    return lightValue;  // Return the light level
}
