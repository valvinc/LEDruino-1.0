// sensorLedManager.cpp - Sensor and LED Manager

#include "sensorLedManager.h"
#include "ultrasonicSensorModule.h"
#include "ledModule.h"
#include "config.h"
#include <Arduino.h>   // For Arduino functions and types
#include <FastLED.h>   // For FastLED.show()

// Declare global variables
bool sensorConnected[NUM_SENSORS] = {true, false, false}; // Update as needed

void initSensorsAndLEDs() {
    initUltrasonicSensors();
    initLEDs();
}
void updateSensorsAndLEDs() {
    // Choose which sensor to use
    const int sensorIndex = 0; // Use the first sensor (index 0)

    long distance;

    // Check if the chosen sensor is connected
    if (sensorConnected[sensorIndex]) {
        distance = readUltrasonicDistance(sensorIndex + 1);
    } else {
        distance = -1; // Indicate sensor is not connected
    }

    // Process the distance reading
    if (distance == -1) {
        Serial.print("Ultrasonic Sensor ");
        Serial.print(sensorIndex + 1);
        Serial.println(": No valid measurement");

        // Turn off all LEDs since there's no valid measurement
        updateLEDs(0, 0);
    } else {
        Serial.print("Ultrasonic Sensor ");
        Serial.print(sensorIndex + 1);
        Serial.print(": ");
        Serial.print(distance);
        Serial.println(" cm");

        // Calculate the number of LEDs to light up
        int numLedsOn = map(distance, MAX_DISTANCE, MIN_DISTANCE, 0, NUM_LEDS);
        numLedsOn = constrain(numLedsOn, 0, NUM_LEDS);

        // Calculate hue based on distance
        uint8_t hue = map(distance, MAX_DISTANCE, MIN_DISTANCE, 0, 255);

        // Debugging output
        Serial.print("numLedsOn: ");
        Serial.println(numLedsOn);
        Serial.print("hue: ");
        Serial.println(hue);

        // Update the LEDs
        updateLEDs(numLedsOn, hue);
    }

    // Show the updated LED states
    FastLED.show();

    // Add a delay to avoid rapid updates
    delay(500);
}
