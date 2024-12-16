#include "ledModule.h"
#include "config.h"
#include <FastLED.h>

// Define the LED array
CRGB leds[NUM_LEDS];

// Function to map x and y to linear index
int XY(int x, int y) {
    if (x < 0 || x >= MATRIX_WIDTH || y < 0 || y >= MATRIX_HEIGHT) {
        return -1;
    }

    int i;
    if (y % 2 == 0) {
        // Even rows run left to right
        i = y * MATRIX_WIDTH + x;
    } else {
        // Odd rows run right to left
        i = y * MATRIX_WIDTH + (MATRIX_WIDTH - 1 - x);
    }
    return i;
}

void initLEDs() {
    FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(30);
    FastLED.clear();
    FastLED.show();
}

void updateLEDs(int numLedsOn, uint16_t hue) {
    CRGB color = CHSV(hue, 255, 255);

    // Clear all LEDs
    FastLED.clear();

    int totalPixels = NUM_LEDS;
    int pixelsToLight = constrain(numLedsOn, 0, totalPixels);

    int count = 0;
    for (int y = 0; y < MATRIX_HEIGHT; y++) {
        for (int x = 0; x < MATRIX_WIDTH; x++) {
            if (count < pixelsToLight) {
                int index = XY(x, y);
                if (index >= 0 && index < NUM_LEDS) {
                    leds[index] = color;
                }
                count++;
            } else {
                break;
            }
        }
        if (count >= pixelsToLight) {
            break;
        }
    }

    FastLED.show();
}
