#include "lightSensorModule.h"
#include "config.h"
#include <Arduino.h>

void initLightSensor() {
    pinMode(LIGHT_SENSOR_PIN, INPUT);  // Set the light sensor pin as input
}

int readLightSensor() {
  // Analogen Wert vom Lichtsensor auslesen
  int lightValue = analogRead(LIGHT_SENSOR_PIN);
  
  return lightValue;  // Return the sound level

}
