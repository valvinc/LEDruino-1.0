#include "ledModule.h"
#include "config.h"
#include <FastLED.h>

// Define the LED array
CRGB leds[NUM_LEDS];

int XY(int x, int y) {
    if (x < 0 || x >= MATRIX_WIDTH || y < 0 || y >= MATRIX_HEIGHT) {
        return -1;  // Return -1 for invalid coordinates
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
    FastLED.setBrightness(30);    // Set the brightness of the LEDs
    FastLED.clear();              // Clear the LED array
    FastLED.show();               // Update the LEDs to reflect the cleared state
}

void updateLEDs(int numLedsOn, uint16_t hue) {
    CRGB color = CHSV(hue, 255, 255);  // Convert the hue to an RGB color

    // Clear all LEDs before updating
    FastLED.clear();

    int totalPixels = NUM_LEDS;        // Total number of pixels in the matrix
    int pixelsToLight = constrain(numLedsOn, 0, totalPixels);  // Ensure the number of LEDs to light is within bounds

    int count = 0;  // Counter for the number of LEDs lit
    // Iterate over the matrix to light up the LEDs
    for (int y = 0; y < MATRIX_HEIGHT; y++) {
        for (int x = 0; x < MATRIX_WIDTH; x++) {
            if (count < pixelsToLight) {
                int index = XY(x, y);  // Get the linear index for the (x, y) coordinate
                if (index >= 0 && index < NUM_LEDS) {
                    leds[index] = color;  // Set the LED color
                }
                count++;
            } else {
                break;  // Exit if the desired number of LEDs are lit
            }
        }
        if (count >= pixelsToLight) {
            break;  // Exit the outer loop as well
        }
    }

    FastLED.show();  // Update the LEDs to reflect the changes
}
