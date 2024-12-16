#include "ultrasonicSensorModule.h"
#include "config.h"
#include <Arduino.h>

void initUltrasonicSensors() {
    // Initialize the pins for Ultrasonic Sensor 1
    pinMode(TRIGGER_PIN_1, OUTPUT);
    pinMode(ECHO_PIN_1, INPUT);
    // Initialize additional sensors
    pinMode(TRIGGER_PIN_2, OUTPUT);
    pinMode(ECHO_PIN_2, INPUT);
    pinMode(TRIGGER_PIN_3, OUTPUT);
    pinMode(ECHO_PIN_3, INPUT);
}

long readUltrasonicDistance(int sensorIndex) {
    int triggerPin, echoPin;

    // Select the correct trigger and echo pins based on the sensor index
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
            return -1;  // Return -1 for an invalid sensor index
    }

    // Send a 10 microsecond pulse to trigger the ultrasonic sensor
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(5);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    // Read the duration of the echo pulse
    long duration = pulseIn(echoPin, HIGH, 26000);  // Timeout after 26 ms
    if (duration == 0) {
        return -1;  // No echo received
    }

    // Calculate the distance based on the duration of the echo pulse
    long distance = (duration / 2) * 0.03432;  // Speed of sound is 343.2 m/s

    return distance;  // Return the measured distance in centimeters
}
