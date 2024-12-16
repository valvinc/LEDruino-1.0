#include "sensorLedManager.h"
#include "ledModule.h"
void setup() {
    Serial.begin(9600);
    initSensorsAndLEDs();
}

void loop() {
    updateSensorsAndLEDs();
    delay(50); // Small delay before the next measurement
}
