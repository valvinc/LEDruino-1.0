#include "sensorLedManager.h"
#include "ultrasonicSensorModule.h"
#include "ledModule.h"
#include "microphoneModule.h"
#include "tempSensorModule.h"
#include "lightSensorModule.h"
#include "config.h"
#include <Arduino.h>
#include <FastLED.h>

void initSensorsAndLEDs() {
    initUltrasonicSensors();
    initMicrophone();
    initTempSensor();
    initLightSensor();
    initLEDs();
}

void updateSensorsAndLEDs(int currentMode) {
    switch (currentMode) {
        case MODE_ULTRASONIC:
            updateUltrasonicMode();
            break;
        case MODE_MULTIPLE_SENSORS:
            updateMultipleSensorsMode();
            break;
        case MODE_MICROPHONE:
            updateMicrophoneMode();
            break;
        case MODE_LIGHT_SENSOR:
            updateLightSensorMode();
            break;
        case MODE_TEMPERATURE_SENSOR:
            updateTempSensorMode();
            break;
        default:
            break;
    }
}

void updateMultipleSensorsMode() {
    long distance = readUltrasonicDistance(1);
    int tempValue = readTempSensor();
    int lightValue = readLightSensor();

    int totalValue = 0;
    int numValues = 0;

    if (distance != -1) {
        totalValue += map(distance, MIN_DISTANCE, MAX_DISTANCE, 0, 255);
        numValues++;
    }

    totalValue += map(tempValue, 0, 50, 0, 255);
    numValues++;

    totalValue += map(lightValue, 0, 1023, 0, 255);
    numValues++;

    int averageValue = totalValue / numValues;
    uint8_t hue = averageValue;

    updateLEDs(NUM_LEDS, hue);
    delay(500);
}

void updateUltrasonicMode() {
    long distance = readUltrasonicDistance(1);

    if (distance == -1) {
        Serial.println("Ultrasonic Sensor: No valid measurement");
        updateLEDs(0, 0);
    } else {
        Serial.print("Ultrasonic Sensor: ");
        Serial.print(distance);
        Serial.println(" cm");

        int numLedsOn = map(distance, MAX_DISTANCE, MIN_DISTANCE, 0, NUM_LEDS);
        numLedsOn = constrain(numLedsOn, 0, NUM_LEDS);

        uint8_t hue = map(distance, MAX_DISTANCE, MIN_DISTANCE, 0, 255);

        updateLEDs(numLedsOn, hue);
    }

    delay(500);
}

void updateMicrophoneMode() {
    int soundLevel = readMicrophone();
    int numLedsOn = map(soundLevel, 0, 1023, 0, NUM_LEDS);
    numLedsOn = constrain(numLedsOn, 0, NUM_LEDS);

    uint8_t hue = map(soundLevel, 0, 1023, 0, 255);

    updateLEDs(numLedsOn, hue);
    delay(50);
}

void updateLightSensorMode() {
    int lightValue = readLightSensor();
    int numLedsOn = map(lightValue, 0, 1023, 0, NUM_LEDS);
    numLedsOn = constrain(numLedsOn, 0, NUM_LEDS);

    uint8_t hue = map(lightValue, 0, 1023, 0, 255);

    updateLEDs(numLedsOn, hue);
    delay(50);
}

void updateTempSensorMode() {
    int tempValue = readTempSensor();
    int numLedsOn = map(tempValue, 0, 50, 0, NUM_LEDS);
    numLedsOn = constrain(numLedsOn, 0, NUM_LEDS);

    uint8_t hue = map(tempValue, 0, 50, 0, 255);

    updateLEDs(numLedsOn, hue);
    delay(500);
}
