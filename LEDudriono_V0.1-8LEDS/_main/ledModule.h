// ledModule.h - LED Module Header

#ifndef LED_MODULE_H
#define LED_MODULE_H

#include <Arduino.h>  // For uint16_t

void initLEDs();
void updateLEDs(int numLedsOn, uint16_t hue);

#endif
