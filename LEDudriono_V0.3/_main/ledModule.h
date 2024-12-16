#ifndef LED_MODULE_H
#define LED_MODULE_H

#include <Arduino.h>
#include <FastLED.h>

extern CRGB leds[];  // Declare the LED array globally for access in other modules

// Function declarations for the LED module
void initLEDs();                                // Initialize the LEDs
void updateLEDs(int numLedsOn, uint16_t hue);   // Update the LEDs based on the number of LEDs to turn on and the hue

#endif
