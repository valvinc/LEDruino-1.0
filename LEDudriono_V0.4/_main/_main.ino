#include "sensorLedManager.h"  // Manages sensor reading and LED updates
#include "ledModule.h"         // LED matrix functions
#include "remoteControl.h"     // IR remote control input handling
#include "config.h"            // Configuration constants
#include "modes.h"             // Modes for LED visualization
int currentMode = -1;
// Timing variables for different tasks
unsigned long lastSensorRead = 0;
unsigned long lastLEDUpdate = 0;
const unsigned long sensorInterval = 50;  // Interval for sensor updates (ms)
const unsigned long ledUpdateInterval = 50;  // Interval for LED updates (ms)

void setup() {
    Serial.begin(9600);
    initSensorsAndLEDs();  // Initialize sensors and LEDs
}

void loop() {
    
    // Check for input from the remote control
    checkRemoteInput(&currentMode); 
    readAllSensors();
    //printSensorValues(); 
    updateLEDsBasedOnMode(currentMode);

}
