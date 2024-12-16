#include "remoteControl.h"
#include "config.h"
#include <IRremote.h>                 // Include the IRremote library for IR communication

void initRemoteControl() {
    IrReceiver.begin(IR_RECV_PIN);    // Start the IR receiver on the specified pin
}

void checkRemoteInput(int* currentMode) {
    if (IrReceiver.decode()) {        // Check if an IR signal has been received
        delay(200);                   // Short delay to debounce

        unsigned long command = IrReceiver.decodedIRData.command;  // Get the received command

        if (command > 0 && command < 95) {  // Valid command range
            Serial.print("Dezimalwert: ");
            Serial.print(command);
            Serial.print(" >> ");

            // Map the IR remote commands to system modes
            if (command == 22) {                      // Command for Ultrasonic Sensor mode
                *currentMode = MODE_ULTRASONIC;
                Serial.println("Mode: Ultrasonic Sensor");
            } else if (command == 25) {               // Command for Microphone mode
                *currentMode = MODE_MICROPHONE;
                Serial.println("Mode: Microphone");
            } else if (command == 13) {               // Command for Temperature Sensor mode
                *currentMode = MODE_TEMPERATURE_SENSOR;
                Serial.println("Mode: Temperature Sensor");
            } else if (command == 12) {               // Command for Light Sensor mode
                *currentMode = MODE_LIGHT_SENSOR;
                Serial.println("Mode: Light Sensor");
            } else if (command == 24) {               // Command for Multiple Sensors mode
                *currentMode = MODE_MULTIPLE_SENSORS;
                Serial.println("Mode: Multiple Sensors");
            } else if (command == 27) {               // Command for Rainbow mode
                *currentMode = MODE_RAINBOW;
                Serial.println("Mode: Rainbow");
            } else {
                Serial.println("Unknown command");    // Unknown command received
            }
        }

        IrReceiver.resume();  // Prepare to receive the next IR signal
    }
}
