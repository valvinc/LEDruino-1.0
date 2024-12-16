#include "microphoneModule.h"
#include "config.h"
#include <Arduino.h>

// Constants for smoothing

static int micBuffer[SMOOTHING_WINDOW] = {0};  // Circular buffer for sound levels
static int micIndex = 0;  // Current index in the circular buffer

void initMicrophone() {
    pinMode(MIC_PIN, INPUT);  // Set the microphone pin as input
}

int readMicrophone() {
    // Read raw analog value from the microphone
    int rawSoundLevel = analogRead(MIC_PIN);

    // Add raw value to the smoothing buffer
    micBuffer[micIndex] = rawSoundLevel;
    micIndex = (micIndex + 1) % SMOOTHING_WINDOW;  // Increment index in a circular manner

    // Calculate the average of the buffer values
    long sum = 0;
    for (int i = 0; i < SMOOTHING_WINDOW; i++) {
        sum += micBuffer[i];
    }

    int soundLevel = sum / SMOOTHING_WINDOW;  // Compute the smoothed value
    return soundLevel;  // Return the smoothed sound level
}
