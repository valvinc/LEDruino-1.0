#ifndef SENSOR_LED_MANAGER_H
#define SENSOR_LED_MANAGER_H

#include "config.h"



// Global variables for sensor data
extern long ultrasonicDistances[NUM_SENSORS]; 
extern int microphoneLevel;
extern int temperatureValue;
extern int lightValue;

void initSensorsAndLEDs();
void readAllSensors();
void updateLEDsBasedOnMode(int currentMode);
void printSensorValues(); 

#endif
