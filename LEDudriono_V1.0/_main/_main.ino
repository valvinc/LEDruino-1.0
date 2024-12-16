#include "sensorLedManager.h"  // Manages sensor reading and LED updates
#include "ledModule.h"         // LED matrix functions
#include "remoteControl.h"     // IR remote control input handling
#include "config.h"            // Configuration constants
#include "modes.h"             // Modes for LED visualization
int currentMode = -1;
 

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
