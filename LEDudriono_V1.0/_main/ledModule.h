#ifndef LED_MODULE_H
#define LED_MODULE_H

#include "config.h"
#include <FastLED.h>

extern CRGB leds[NUM_LEDS]; // LED array accessible globally

void initLEDs();
int XY(int x, int y);

#endif
