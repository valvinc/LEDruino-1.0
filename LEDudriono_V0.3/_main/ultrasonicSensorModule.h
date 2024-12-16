#ifndef ULTRASONIC_SENSOR_MODULE_H
#define ULTRASONIC_SENSOR_MODULE_H

// Function declarations for the ultrasonic sensor module
void initUltrasonicSensors();              // Initialize ultrasonic sensors
long readUltrasonicDistance(int sensorIndex); // Read distance from a specified ultrasonic sensor

#endif
