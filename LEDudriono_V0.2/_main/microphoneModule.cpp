#include "microphoneModule.h"
#include "config.h"
#include <Arduino.h>

void initMicrophone() {
    pinMode(MIC_PIN, INPUT);
}

int readMicrophone() {
    int soundLevel = analogRead(MIC_PIN);
    Serial.print("Microphone Sound Level: ");
    Serial.println(soundLevel);
    return soundLevel;
}
