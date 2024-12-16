// ledModule.cpp - LED Handling

#include "ledModule.h"
#include "config.h"
#include <FastLED.h>   // For CRGB and FastLED functions

// Define the LED array
CRGB leds[NUM_LEDS];

void initLEDs() {
    FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(30);

   //     for (int i = 0; i < NUM_LEDS; i++) {
      //  leds[i] = CRGB::Red;
    //}
    FastLED.clear();
    FastLED.show();
}

void updateLEDs(int numLedsOn, uint16_t hue) {
    CRGB color = CHSV(hue, 255, 255);
    Serial.print(" hue: ");
    Serial.println(hue);
    Serial.print(" LEDnumber: ");
    Serial.println(numLedsOn);


    for (int i = 0; i < NUM_LEDS; i++) {
        if (i < numLedsOn) {
            leds[i] = color;
        } else {
            leds[i] = CRGB::Green;
        }
    }

    FastLED.show();
    // Do not call FastLED.show() here to optimize performance
}
