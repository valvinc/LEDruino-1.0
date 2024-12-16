#ifndef CONFIG_H
#define CONFIG_H



// LED Matrix Configuration
#define LED_PIN           42
#define MATRIX_WIDTH      16
#define MATRIX_HEIGHT     16
#define NUM_LEDS          (MATRIX_WIDTH * MATRIX_HEIGHT)
#define BRIGHTNESS        80
// Ultrasonic Sensor Pins
#define TRIGGER_PIN_1     7
#define ECHO_PIN_1        6
#define TRIGGER_PIN_2     5
#define ECHO_PIN_2        4
#define TRIGGER_PIN_3     3
#define ECHO_PIN_3        2 

// Other Sensor Pins
#define MIC_PIN           A0    // Microphone analog input pin
#define LIGHT_SENSOR_PIN  A1    // Light sensor analog input pin
#define TEMP_SENSOR_PIN   A2    // Temperature sensor analog input pin

// IR Receiver Pin
#define IR_RECV_PIN       11

// Modes
#define MODE_ULTRASONIC           0
#define MODE_MICROPHONE           1
#define MODE_TEMPERATURE_SENSOR   2
#define MODE_LIGHT_SENSOR         3
#define MODE_MULTIPLE_SENSORS     4
#define MODE_RAINBOW              5

#define NUM_SENSORS 6


#define SMOOTHING_WINDOW 6 // Number of samples for the moving average for mic

#endif
