#include "tempSensorModule.h"
#include "config.h"
#include <Arduino.h>

void initTempSensor() {
    pinMode(TEMP_SENSOR_PIN, INPUT);  // Set the temperature sensor pin as input
}

int readTempSensor() {
    int sensorValue = analogRead(TEMP_SENSOR_PIN);  // Read analog value from the sensor
    float voltage = sensorValue * (5.0 / 1023.0);   // Convert the value to voltage
    int temperatureC = (voltage - 0.5) * 100;       // Convert voltage to temperature (°C) for TMP36 sensor
    return temperatureC;  // Return the temperature in Celsius
}
