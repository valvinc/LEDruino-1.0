// _config.h - Configuration File

#ifndef CONFIG_H
#define CONFIG_H

// Pin configuration
#define LED_PIN         42      // Pin connected to the NeoPixel matrix
#define MATRIX_WIDTH    8       // Number of LEDs in your strip
#define MATRIX_HEIGHT   1       // Height is 1 for a strip
#define NUM_LEDS        (MATRIX_WIDTH * MATRIX_HEIGHT)
#define NUM_SENSORS     3       // Number of ultrasonic sensors

// Ultrasonic sensor pins
#define TRIGGER_PIN_1   10      // Pin connected to ultrasonic sensor 1 trigger
#define ECHO_PIN_1      11      // Pin connected to ultrasonic sensor 1 echo
#define TRIGGER_PIN_2   12      // Pin connected to ultrasonic sensor 2 trigger
#define ECHO_PIN_2      13      // Pin connected to ultrasonic sensor 2 echo
#define TRIGGER_PIN_3   14      // Pin connected to ultrasonic sensor 3 trigger
#define ECHO_PIN_3      15      // Pin connected to ultrasonic sensor 3 echo

// Sensor thresholds
const int MIN_DISTANCE = 10;    // Minimum distance to start lighting LEDs (in cm)
const int MAX_DISTANCE = 90;    // Maximum distance to light up all LEDs (in cm)

#endif
