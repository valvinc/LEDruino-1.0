#ifndef CONFIG_H
#define CONFIG_H

// LED Matrix Configuration
#define LED_PIN           42                 // Pin connected to the LED strip
#define MATRIX_WIDTH      16                 // Width of the LED matrix
#define MATRIX_HEIGHT     16                 // Height of the LED matrix
#define NUM_LEDS          (MATRIX_WIDTH * MATRIX_HEIGHT) // Total number of LEDs

// Ultrasonic Sensor Pins
#define TRIGGER_PIN_1     10                // Trigger pin for Ultrasonic Sensor 1
#define ECHO_PIN_1        11                // Echo pin for Ultrasonic Sensor 1
#define TRIGGER_PIN_2     12                // Trigger pin for Ultrasonic Sensor 2
#define ECHO_PIN_2        13                // Echo pin for Ultrasonic Sensor 2
#define TRIGGER_PIN_3     14                // Trigger pin for Ultrasonic Sensor 3
#define ECHO_PIN_3        15                // Echo pin for Ultrasonic Sensor 3

// Other Sensor Pins
#define MIC_PIN           A0                // Microphone analog input pin
#define TEMP_SENSOR_PIN   A1                // Temperature sensor analog input pin
#define LIGHT_SENSOR_PIN  A2                // Light sensor analog input pin

#define NUM_SENSORS 6

// IR Receiver Pin
#define IR_RECV_PIN       22                // Pin connected to the IR receiver

// Ultrasonic Sensor Distance Range
const int MIN_DISTANCE = 10;                // Minimum distance for mapping (in cm)
const int MAX_DISTANCE = 90;                // Maximum distance for mapping (in cm)

// Modes for the LED visualization (re-added single sensor modes)
#define MODE_ULTRASONIC           0         // Mode for Ultrasonic Sensor
#define MODE_MICROPHONE           1         // Mode for Microphone
#define MODE_TEMPERATURE_SENSOR   2         // Mode for Temperature Sensor
#define MODE_LIGHT_SENSOR         3         // Mode for Light Sensor
#define MODE_MULTIPLE_SENSORS     4         // Mode for Multiple Sensors
#define MODE_RAINBOW              5         // Rainbow mode

#endif
