#include "remoteControl.h"
#include "config.h"
#include <IRremote.h>

void initRemoteControl() {
    IrReceiver.begin(IR_RECV_PIN);
}

void checkRemoteInput(int* currentMode) {
    if (IrReceiver.decode()) {
        delay(200);
        unsigned long command = IrReceiver.decodedIRData.command;

        if (command > 0 && command < 95) {
            Serial.print("Dezimalwert: ");
            Serial.print(command);
            Serial.print(" >> ");

            if (command == 22) {
                *currentMode = MODE_ULTRASONIC;
                Serial.println("Mode: Ultrasonic Sensor");
            } else if (command == 25) {
                *currentMode = MODE_MULTIPLE_SENSORS;
                Serial.println("Mode: Multiple Sensors");
            } else if (command == 13) {
                *currentMode = MODE_MICROPHONE;
                Serial.println("Mode: Microphone");
            } else if (command == 12) {
                *currentMode = MODE_LIGHT_SENSOR;
                Serial.println("Mode: Light Sensor");
            } else if (command == 24) {
                *currentMode = MODE_TEMPERATURE_SENSOR;
                Serial.println("Mode: Temperature Sensor");
            } else {
                Serial.println("Unknown command");
            }
        }

        IrReceiver.resume();
    }
}
