#include "microphoneModule.h"
#include "config.h"
#include <Arduino.h>

void initMicrophone() {
    pinMode(MIC_PIN, INPUT);  // Set the microphone pin as input
}

int readMicrophone() {
    int soundLevel = analogRead(MIC_PIN);  // Read analog value from the microphone
    return soundLevel;  // Return the sound level
}
