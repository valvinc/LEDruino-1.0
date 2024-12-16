#include "ultrasonicSensorModule.h"
#include "config.h"
#include <Arduino.h>

// Constants for smoothing
#define SMOOTHING_WINDOW 5 // Number of samples to average

// Circular buffers for smoothing and indices
static long ultrasonicBuffers[3][SMOOTHING_WINDOW] = {0}; // Buffers for each sensor
static int ultrasonicIndices[3] = {0};                   // Current indices for each sensor

// Initialize ultrasonic sensors
void initUltrasonicSensors() {
    pinMode(TRIGGER_PIN_1, OUTPUT);
    pinMode(ECHO_PIN_1, INPUT);

    pinMode(TRIGGER_PIN_2, OUTPUT);
    pinMode(ECHO_PIN_2, INPUT);

    pinMode(TRIGGER_PIN_3, OUTPUT);
    pinMode(ECHO_PIN_3, INPUT);
}

// Smooth the ultrasonic sensor value using a moving average
long smoothUltrasonicValue(int sensorIndex, long newValue) {
    // Add the new value to the circular buffer
    ultrasonicBuffers[sensorIndex][ultrasonicIndices[sensorIndex]] = newValue;
    ultrasonicIndices[sensorIndex] = (ultrasonicIndices[sensorIndex] + 1) % SMOOTHING_WINDOW;

    // Calculate the average of the buffer
    long sum = 0;
    for (int i = 0; i < SMOOTHING_WINDOW; i++) {
        sum += ultrasonicBuffers[sensorIndex][i];
    }
    return sum / SMOOTHING_WINDOW; // Return smoothed value
}

// Read distance from an ultrasonic sensor
long readUltrasonicDistance(int sensorIndex) {
    int triggerPin, echoPin;

    // Select the trigger and echo pins based on the sensor index
    switch (sensorIndex) {
        case 1:
            triggerPin = TRIGGER_PIN_1;
            echoPin = ECHO_PIN_1;
            break;
        case 2:
            triggerPin = TRIGGER_PIN_2;
            echoPin = ECHO_PIN_2;
            break;
        case 3:
            triggerPin = TRIGGER_PIN_3;
            echoPin = ECHO_PIN_3;
            break;
        default:
            return -1; // Invalid sensor index
    }

    // Trigger a measurement
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(5);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    // Wait for the echo pin to go HIGH (start of echo pulse)
    unsigned long startTime = micros();
    while (digitalRead(echoPin) == LOW) {
        if (micros() - startTime > 26000) {
            return -1; // Timeout waiting for echo
        }
    }

    // Measure the duration of the echo pulse
    unsigned long echoStart = micros();
    while (digitalRead(echoPin) == HIGH) {
        if (micros() - echoStart > 26000) {
            return -1; // Timeout measuring echo pulse
        }
    }

    unsigned long duration = micros() - echoStart;

    // Calculate distance in centimeters
    long distance = (duration / 2) * 0.03432;

    // Smooth the value and return the result
    return smoothUltrasonicValue(sensorIndex - 1, distance);
}
