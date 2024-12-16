#include "sensorLedManager.h"  // Include the sensor and LED manager
#include "ledModule.h"         // Include the LED module
#include "remoteControl.h"     // Include the remote control module
#include "config.h"            // Include configuration constants

int currentMode = MODE_ULTRASONIC;  // Initialize the current mode to Ultrasonic Sensor mode

void setup() {
    Serial.begin(9600);            // Start serial communication at 9600 baud
    initSensorsAndLEDs();          // Initialize sensors and LEDs
    initRemoteControl();           // Initialize the IR remote control
}

void loop() {
    checkRemoteInput(&currentMode);       // Check for input from the IR remote to change modes
    readAllSensors();                     // Read data from all sensors
    updateLEDsBasedOnMode(currentMode);   // Update LEDs based on the current mode and sensor data
    delay(50);                            // Small delay before the next loop iteration
}
