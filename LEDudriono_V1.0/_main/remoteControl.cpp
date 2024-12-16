#include "remoteControl.h"
#include "config.h"
#include <Keypad.h>
#include <Arduino.h>

// Keypad setup
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns

// Corrected key mapping based on your confirmed keypad layout
char keys[ROWS][COLS] = {
    {'D', '#', '0', '*'},
    {'C', '9', '8', '7'},
    {'B', '6', '5', '4'},
    {'A', '3', '2', '1'}
};

// Correct row and column pin assignments based on the working configuration
byte rowPins[ROWS] = {18, 19, 20, 21}; // A4-A7 (actual row pins)
byte colPins[COLS] = {14, 15, 16, 17}; // A0-A3 (actual column pins)

// Create the Keypad object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


// Check for keypad input and update the current mode
void checkRemoteInput(int* currentMode) {
    char key = keypad.getKey(); // Get the key pressed

    if (key) {
        Serial.print("Key pressed: ");
        Serial.println(key);

        // Map keys to corresponding modes
        switch (key) {
            case '1':
                *currentMode = MODE_MULTIPLE_SENSORS;
                Serial.println("Mode set to: Multiple Sensors");
                break;
            case '2':
                *currentMode = MODE_MICROPHONE;
                Serial.println("Mode set to: Microphone");
                break;
            case '5':
                *currentMode = MODE_TEMPERATURE_SENSOR;
                Serial.println("Mode set to: Temperature Sensor");
                break;
            case '4':
                *currentMode = MODE_LIGHT_SENSOR;
                Serial.println("Mode set to: Light Sensor");
                break;
            case '3':
                *currentMode = MODE_ULTRASONIC;
                Serial.println("Mode set to: Ultrasonic");
                break;
            case '6':
                *currentMode = MODE_RAINBOW;
                Serial.println("Mode set to: Rainbow");
                break;
            default:
                Serial.println("Invalid key, no mode change.");
                break;
        }
    }
}
