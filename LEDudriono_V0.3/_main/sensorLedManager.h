#ifndef SENSOR_LED_MANAGER_H
#define SENSOR_LED_MANAGER_H

#include "config.h"  // Include configuration constants

// Function declarations for the sensor and LED manager

// Initialization functions
void initSensorsAndLEDs();                     // Initialize all sensors and LEDs

// Sensor reading functions
void readAllSensors();                         // Read data from all sensors

// LED update functions based on mode
void updateSensorsAndLEDs(int currentMode);    // Update sensors and LEDs based on the current mode
void updateLEDsBasedOnMode(int currentMode);   // Update LEDs based on the current mode and sensor data

// Individual update functions for each mode
void updateUltrasonicMode();                   // Update LEDs for Ultrasonic Sensor mode
void updateMicrophoneMode();                   // Update LEDs for Microphone mode
void updateLightSensorMode();                  // Update LEDs for Light Sensor mode
void updateTempSensorMode();                   // Update LEDs for Temperature Sensor mode
void updateRainbowMode();                      // Update LEDs for Rainbow mode
void updateMultipleSensorsMode();              // Update LEDs for Multiple Sensors mode

// Variables to store sensor data
extern long ultrasonicDistances[NUM_SENSORS];  // Array to store distances from ultrasonic sensors
extern int microphoneLevel;                    // Variable to store microphone sound level
extern int temperatureValue;                   // Variable to store temperature value
extern int lightValue;                         // Variable to store light sensor value

#endif  // SENSOR_LED_MANAGER_H
