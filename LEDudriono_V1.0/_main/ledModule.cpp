#include "ledModule.h" // LED-related functions
#include "config.h"    // Configuration constants
#include <FastLED.h>   // FastLED library for WS2812 LEDs

CRGB leds[NUM_LEDS]; // Array to hold LED color data

int XY(int x, int y) {
    // Convert (x, y) to a 1D index; handles zigzag wiring
    if (x < 0 || x >= MATRIX_WIDTH || y < 0 || y >= MATRIX_HEIGHT) {
        return -1; // Invalid coordinates
    }

    int i; // Linear index
    if (y % 2 == 0) {
        i = y * MATRIX_WIDTH + x; // Even rows: left-to-right
    } else {
        i = y * MATRIX_WIDTH + (MATRIX_WIDTH - 1 - x); // Odd rows: right-to-left
    }
    return i; // Return the calculated index
}

void initLEDs() {
  delay(20);
  // Initialize the LED strip
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);

    const int sectionSize = NUM_LEDS / 3; // Approximate size of each section
    const int remainder = NUM_LEDS % 3;  // Handle any leftover LEDs
    const int delayTime = 5;           // Delay between frames in milliseconds

    for (int shift = 0; shift < NUM_LEDS; shift++) {
        FastLED.clear();

        // Set red section
        for (int i = 0; i < sectionSize + (remainder > 0 ? 1 : 0); i++) {
            int index = (i + shift) % NUM_LEDS; // Wrap around the grid
            leds[index] = CRGB::Red;
        }

        // Set green section
        for (int i = 0; i < sectionSize + (remainder > 1 ? 1 : 0); i++) {
            int index = (i + shift + sectionSize) % NUM_LEDS; // Offset by one section
            leds[index] = CRGB::Green;
        }

        // Set blue section
        for (int i = 0; i < sectionSize; i++) {
            int index = (i + shift + sectionSize * 2 + (remainder > 1 ? 1 : 0)) % NUM_LEDS; // Offset by two sections
            leds[index] = CRGB::Blue;
        }

        FastLED.show();
        delay(delayTime);
    }

    // Optional: Clear LEDs at the end
    FastLED.clear();
    FastLED.show();
}
