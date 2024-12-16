#include "sensorLedManager.h"
#include "ultrasonicSensorModule.h"
#include "microphoneModule.h"
#include "tempSensorModule.h"
#include "lightSensorModule.h"
#include "ledModule.h"
#include "config.h"
#include <Arduino.h>

// Global variables to store sensor data
long ultrasonicDistances[NUM_SENSORS] = {0}; // Array to store distances
int microphoneLevel = 0;                     // Microphone sound level
int temperatureValue = 0;                    // Temperature value
int lightValue = 0;                          // Light sensor value

void initSensorsAndLEDs() {
    initUltrasonicSensors();  // Initialize ultrasonic sensors
    initMicrophone();         // Initialize microphone
    initTempSensor();         // Initialize temperature sensor
    initLightSensor();        // Initialize light sensor
    initLEDs();               // Initialize LEDs
}

void readAllSensors() {
    // Read distances from all ultrasonic sensors
    for (int i = 0; i < NUM_SENSORS; i++) {
        ultrasonicDistances[i] = readUltrasonicDistance(i + 1);
        Serial.print("Ultrasonic Sensor ");
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(ultrasonicDistances[i]);
        Serial.println(" cm");
    }

    // Read microphone sound level
    microphoneLevel = readMicrophone();
    Serial.print("Microphone Level: ");
    Serial.println(microphoneLevel);

    // Read temperature value
    temperatureValue = readTempSensor();
    Serial.print("Temperature: ");
    Serial.print(temperatureValue);
    Serial.println(" °C");

    // Read light sensor value
    lightValue = readLightSensor();
    Serial.print("Light Level: ");
    Serial.println(lightValue);
}

void updateLEDsBasedOnMode(int currentMode) {
    switch (currentMode) {
        case MODE_ULTRASONIC:
            updateUltrasonicMode();
            break;
        case MODE_MICROPHONE:
            updateMicrophoneMode();
            break;
        case MODE_TEMPERATURE_SENSOR:
            updateTempSensorMode();
            break;
        case MODE_LIGHT_SENSOR:
            updateLightSensorMode();
            break;
        case MODE_MULTIPLE_SENSORS:
            updateMultipleSensorsMode();
            break;
        case MODE_RAINBOW:
            updateRainbowMode();
            break;
        default:
            break;
    }
}

void updateUltrasonicMode() {
    // Use the average distance from all ultrasonic sensors
    int totalDistance = 0;
    int validReadings = 0;
    for (int i = 0; i < NUM_SENSORS; i++) {
        if (ultrasonicDistances[i] != -1) {
            totalDistance += ultrasonicDistances[i];
            validReadings++;
        }
    }
    if (validReadings > 0) {
        int averageDistance = totalDistance / validReadings;
        int numLedsOn = map(averageDistance, MAX_DISTANCE, MIN_DISTANCE, 0, NUM_LEDS);
        numLedsOn = constrain(numLedsOn, 0, NUM_LEDS);
        uint8_t hue = map(averageDistance, MAX_DISTANCE, MIN_DISTANCE, 0, 255);
        updateLEDs(numLedsOn, hue);
    } else {
        updateLEDs(0, 0); // No valid readings, turn off LEDs
    }
}

void updateMicrophoneMode() {
    // Visualize sound levels on the LED matrix
    int numLedsOn = map(microphoneLevel, 0, 1023, 0, NUM_LEDS);
    numLedsOn = constrain(numLedsOn, 0, NUM_LEDS);
    uint8_t hue = map(microphoneLevel, 0, 1023, 0, 255);
    updateLEDs(numLedsOn, hue);
}

void updateTempSensorMode() {
    // Visualize temperature on the LED matrix
    int numLedsOn = map(temperatureValue, 0, 50, 0, NUM_LEDS);
    numLedsOn = constrain(numLedsOn, 0, NUM_LEDS);
    uint8_t hue = map(temperatureValue, 0, 50, 160, 0); // From blue (cold) to red (hot)
    updateLEDs(numLedsOn, hue);
}

void updateLightSensorMode() {
    // Visualize light levels on the LED matrix
    int numLedsOn = map(lightValue, 0, 1023, 0, NUM_LEDS);
    numLedsOn = constrain(numLedsOn, 0, NUM_LEDS);
    uint8_t hue = map(lightValue, 0, 1023, 0, 255);
    updateLEDs(numLedsOn, hue);
}

void updateMultipleSensorsMode() {
    // Combine readings from multiple sensors to update LEDs
    int totalValue = 0;
    int numValues = 0;

    // Include ultrasonic sensors
    for (int i = 0; i < NUM_SENSORS; i++) {
        if (ultrasonicDistances[i] != -1) {
            totalValue += map(ultrasonicDistances[i], MIN_DISTANCE, MAX_DISTANCE, 255, 0);
            numValues++;
        }
    }

    // Include temperature
    totalValue += map(temperatureValue, 0, 50, 0, 255);
    numValues++;

    // Include light sensor
    totalValue += map(lightValue, 0, 1023, 0, 255);
    numValues++;

    // Include microphone
    totalValue += map(microphoneLevel, 0, 1023, 0, 255);
    numValues++;

    int averageValue = totalValue / numValues;
    uint8_t hue = averageValue;

    updateLEDs(NUM_LEDS, hue);  // Update all LEDs with the calculated hue
}

void updateRainbowMode() {
    // Display a moving rainbow pattern across the LED matrix
    static uint8_t hue = 0; // Static variable to keep track of the hue
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(hue + (i * 10), 255, 255); // Assign color based on position
    }
    FastLED.show();
    hue++; // Increment hue for the next frame
}
