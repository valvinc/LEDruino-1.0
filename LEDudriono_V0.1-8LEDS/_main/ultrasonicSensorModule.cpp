// ultrasonicSensorModule.cpp - Ultrasonic Sensor Handling

#include "ultrasonicSensorModule.h"
#include "config.h"
#include <Arduino.h>

void initUltrasonicSensors() {
    pinMode(TRIGGER_PIN_1, OUTPUT);
    pinMode(ECHO_PIN_1, INPUT);
    // Initialize other sensors if connected
}

long readUltrasonicDistance(int sensorIndex) {
    int triggerPin, echoPin;

    switch (sensorIndex) {
        case 1:
            triggerPin = TRIGGER_PIN_1;
            echoPin = ECHO_PIN_1;
            break;
        // Add cases for other sensors if needed
        default:
            return -1; // Invalid sensor index
    }

    // Trigger the ultrasonic sensor
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(5);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    // Read the echo time
    long duration = pulseIn(echoPin, HIGH, 26000); // Timeout after ~450cm
    if (duration == 0) {
        return -1; // No echo received
    }
    long distance = (duration / 2) * 0.03432;       // Convert to centimeters

    return distance;
}
