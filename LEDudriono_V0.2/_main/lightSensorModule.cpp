#include "lightSensorModule.h"
#include "config.h"
#include <Arduino.h>

void initLightSensor() {
    pinMode(LIGHT_SENSOR_PIN, INPUT);
}

int readLightSensor() {
    int lightValue = analogRead(LIGHT_SENSOR_PIN);
    Serial.print("Light Sensor Value: ");
    Serial.println(lightValue);
    return lightValue;
}
