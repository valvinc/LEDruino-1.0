#ifndef CONFIG_H
#define CONFIG_H

#define LED_PIN           42
#define MATRIX_WIDTH      16
#define MATRIX_HEIGHT     16
#define NUM_LEDS          (MATRIX_WIDTH * MATRIX_HEIGHT)
#define NUM_SENSORS       3

#define TRIGGER_PIN_1     10
#define ECHO_PIN_1        11
#define TRIGGER_PIN_2     12
#define ECHO_PIN_2        13
#define TRIGGER_PIN_3     14
#define ECHO_PIN_3        15

#define MIC_PIN           A0
#define TEMP_SENSOR_PIN   A1
#define LIGHT_SENSOR_PIN  A2
#define IR_RECV_PIN       22  // Updated according to your code

const int MIN_DISTANCE = 10;
const int MAX_DISTANCE = 90;

// Modes
#define MODE_ULTRASONIC           0
#define MODE_MULTIPLE_SENSORS     1
#define MODE_MICROPHONE           2
#define MODE_LIGHT_SENSOR         3
#define MODE_TEMPERATURE_SENSOR   4

#endif
