#include "sensorLedManager.h"
#include "ultrasonicSensorModule.h"
#include "microphoneModule.h"
#include "tempSensorModule.h"
#include "lightSensorModule.h"
#include "ledModule.h"
#include "sensorLedManager.h"
#include "modes.h"
#include <Arduino.h>


void initSensorsAndLEDs() {
    initUltrasonicSensors();
    initMicrophone();
    initTempSensor();
    initLightSensor();
    initLEDs();
}

void readAllSensors() {
    // Aktuelle Zeit abrufen
    unsigned long currentMillis = millis();

    // **Ultraschallsensoren: Sehr häufig (z. B. alle 50 ms pro Sensor)**
    static int currentSensor = 0;
    static unsigned long lastUltrasonicMillis = 0;
    if (currentMillis - lastUltrasonicMillis >= 50) { // Priorisierte schnelle Abfrage
        lastUltrasonicMillis = currentMillis;

        // Trigger den aktuellen Sensor und lese die Distanz
        ultrasonicDistances[currentSensor] = readUltrasonicDistance(currentSensor + 1);
        // Wechsel zum nächsten Sensor
        currentSensor = (currentSensor + 1) % 3; // Zyklisch durch alle Sensoren
    }

    // **Mikrofon: Häufig (z. B. alle 50 ms)**
    static unsigned long lastMicrophoneMillis = 0;
    if (currentMillis - lastMicrophoneMillis >= 10) {
        lastMicrophoneMillis = currentMillis;
        microphoneLevel = readMicrophone();
        // Serial.print("Microphone Level: ");
        // Serial.println(microphoneLevel);

    }

    // **Lichtsensor: Weniger häufig (z. B. alle 2 Sekunden)**
    static unsigned long lastLightMillis = 0;
    if (currentMillis - lastLightMillis >= 5000) {
        lastLightMillis = currentMillis;
        lightValue = readLightSensor();
        // Serial.print("Light Level: ");
        // Serial.println(lightValue);

    }

    // **Temperatursensor: Selten (z. B. alle 5 Sekunden)**
    static unsigned long lastTempMillis = 0;
    if (currentMillis - lastTempMillis >= 5000) {
        lastTempMillis = currentMillis;
        temperatureValue = readTempSensor();
        // Serial.print("Temperature: ");
        // Serial.print(temperatureValue);
        // Serial.println(" °C");

    }
}

void updateLEDsBasedOnMode(int currentMode) {
    // LEDs aktualisieren basierend auf dem aktuellen Modus
    switch (currentMode) {
        case MODE_ULTRASONIC:
            updateUltrasonicMode(ultrasonicDistances);
            break;
        case MODE_MICROPHONE:
            updateMicrophoneMode(microphoneLevel);
            break;
        case MODE_TEMPERATURE_SENSOR:
            updateTempSensorMode(temperatureValue);
            break;
        case MODE_LIGHT_SENSOR:
            updateLightSensorMode(lightValue);
            break;
        case MODE_MULTIPLE_SENSORS:
            updateMultipleSensorsMode(ultrasonicDistances, microphoneLevel, temperatureValue, lightValue);
            break;
        case MODE_RAINBOW:
            updateRainbowMode();
            break;
        default:
            updateRainbowMode();
            break;
    }
}

void printSensorValues() {
    // Print Ultrasonic Distances
    for (int i = 0; i < 3; i++) {
        Serial.print("Ultraschall Sensor ");
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(ultrasonicDistances[i]);
        Serial.println(" cm");
    }

    // Print Microphone Level
    Serial.print("Mikrofon Level: ");
    Serial.println(microphoneLevel);

    // Print Temperature Value
    Serial.print("Temperatur: ");
    Serial.print(temperatureValue);
    Serial.println(" °C");

    // Print Light Value
    Serial.print("Licht Level: ");
    Serial.println(lightValue);

    // Spacer for better readability
    Serial.println("--------------------------------");
}
