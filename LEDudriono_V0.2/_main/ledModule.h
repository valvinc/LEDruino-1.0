#ifndef LED_MODULE_H
#define LED_MODULE_H

#include <Arduino.h>
#include <FastLED.h>

void initLEDs();
void updateLEDs(int numLedsOn, uint16_t hue);

#endif
