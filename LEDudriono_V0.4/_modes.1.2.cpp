#include "modes.h"
#include "config.h"
#include "ledModule.h"
#include <FastLED.h>

// For microphone normalization if needed:
static const int minValue = 50;   // Noise floor, adjust as needed
static const int maxValue = 1023; // Max ADC input

static int nextLedIndex(int index) {
    // Currently just returns the same index.
    // Modify if a different traversal pattern is desired.
    return index;
}

void updateTestPatternMode() {
    FastLED.clear();
    for (int y = 0; y < MATRIX_HEIGHT; y++) {
        for (int x = 0; x < MATRIX_WIDTH; x++) {
            int index = XY(x, y);
            if (index != -1) {
                leds[index] = COLOR;
            }
        }
        FastLED.show();
        delay(500); // Wait 500ms before lighting the next row
        FastLED.clear();
    }
}

void updateUltrasonicMode(long distances[]) {
    int validCount = 0;
    long total = 0;
    for (int i = 0; i < 3; i++) {
        if (distances[i] != -1) {
            total += distances[i];
            validCount++;
        }
    }

    FastLED.clear();
    if (validCount == 0) {
        FastLED.show();
        return;
    }

    int avg = total / validCount;
    int numLedsOn = map(avg, MAX_DISTANCE, MIN_DISTANCE, 0, NUM_LEDS);
    numLedsOn = constrain(numLedsOn, 0, NUM_LEDS);
    uint8_t hue = (uint8_t)map(avg, MAX_DISTANCE, MIN_DISTANCE, 0, 255);

    CRGB color = CHSV(hue, 255, LED_COLOR_VALUE);
    int count = 0;
    for (int y = MATRIX_HEIGHT - 1; y >= 0; y--) {
        for (int x = 0; x < MATRIX_WIDTH; x++) {
            int idx = XY(x,y);
            if (idx >= 0) {
                if (count < numLedsOn) {
                    leds[idx] = color;
                    count++;
                } else {
                    break;
                }
            }
        }
        if (count >= numLedsOn) break;
    }
    FastLED.show();
}

// Updated Microphone Mode (2D Circular Pattern)
void updateMicrophoneMode(int soundLevel) {
    int maxDim = max(MATRIX_WIDTH, MATRIX_HEIGHT);
    int radius = map(soundLevel, 0, 1023, 0, maxDim / 2);
    radius = constrain(radius, 0, maxDim / 2);

    // For example, map quiet=blue(160) to loud=red(0)
    uint8_t hue = (uint8_t)map(soundLevel, 0, 1023, 160, 0);

    FastLED.clear();
    int centerX = MATRIX_WIDTH / 2;
    int centerY = MATRIX_HEIGHT / 2;

    for (int y = 0; y < MATRIX_HEIGHT; y++) {
        for (int x = 0; x < MATRIX_WIDTH; x++) {
            int idx = XY(x, y);
            if (idx < 0) continue;
            int dx = x - centerX;
            int dy = y - centerY;
            int distSq = dx*dx + dy*dy;
            if (distSq <= radius*radius) {
                leds[idx] = CHSV(hue, 255, LED_COLOR_VALUE);
            }
        }
    }

    FastLED.show();
}

// Light Sensor Mode: Adjust HSV 'value' based on light level
void updateLightSensorMode(int lightValue) {
    uint8_t val = (uint8_t)map(lightValue, 0, 1023, 10, 255);
    FastLED.clear();
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(96, 255, val); // Hue=96(green), sat=255, value=val
    }
    FastLED.show();
}

// Temperature Sensor Mode: Smooth transition from blue (160) to red (0) between 0°C and 50°C
void updateTempSensorMode(int temperatureValue) {
    uint8_t targetHue = (uint8_t)map(temperatureValue, 0, 50, 160, 0);
    FastLED.clear();
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(targetHue, 255, LED_COLOR_VALUE);
    }
    FastLED.show();
}

// Refined Multiple Sensors Mode
// - Temperature sets hue
// - Light sets value (color brightness)
// - Three ultrasonic sensors set saturation spatially:
//   * Left sensor influences bottom-left corner, fading out diagonally
//   * Middle sensor influences bottom to top gradient
//   * Right sensor influences left to right gradient
// - Microphone adds a circular overlay that modifies hue/value inside a radius
void updateMultipleSensorsMode(long distances[], int soundLevel, int temperatureValue, int lightValue) {
    const int W = MATRIX_WIDTH;
    const int H = MATRIX_HEIGHT;

    // Hue from Temperature
    uint8_t baseHue = (uint8_t)map(temperatureValue, 0, 50, 160, 0);

    // Value from Light
    uint8_t baseVal = (uint8_t)map(lightValue, 0, 1023, 50, 255);

    // Convert distances to saturations
    auto getSatFromDistance = [&](long dist) -> uint8_t {
        if (dist < 0) {
            return 200; 
        } else {
            return (uint8_t)map(dist, MIN_DISTANCE, MAX_DISTANCE, 255, 50);
        }
    };

    uint8_t leftSat = getSatFromDistance(distances[0]);
    uint8_t midSat = getSatFromDistance(distances[1]);
    uint8_t rightSat = getSatFromDistance(distances[2]);

    // Position-based factor functions
    auto factor_left = [&](int x, int y) {
        float fx = 1.0f - ((float)x / (W - 1));
        float fy = 1.0f - ((float)y / (H - 1));
        return fx * fy; // max at bottom-left corner
    };

    auto factor_middle = [&](int /*x*/, int y) {
        return 1.0f - ((float)y / (H - 1)); // strong at bottom, weak at top
    };

    auto factor_right = [&](int x, int /*y*/) {
        return (float)x / (W - 1); // strong at right, weak at left
    };

    FastLED.clear();
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            int idx = XY(x, y);
            if (idx < 0) continue;

            float fl = factor_left(x, y);
            float fm = factor_middle(x, y);
            float fr = factor_right(x, y);

            float sumFactors = fl + fm + fr;
            uint8_t finalSat;
            if (sumFactors > 0) {
                float weightedSat = (leftSat * fl) + (midSat * fm) + (rightSat * fr);
                weightedSat /= sumFactors;
                finalSat = (uint8_t)constrain((int)weightedSat, 0, 255);
            } else {
                finalSat = 200; // fallback
            }

            leds[idx] = CHSV(baseHue, finalSat, baseVal);
        }
    }

    // Microphone overlay
    int maxDim = max(W, H);
    int radius = map(soundLevel, 0, 1023, 0, maxDim / 2);
    radius = constrain(radius, 0, maxDim / 2);

    int centerX = W / 2;
    int centerY = H / 2;
    uint8_t targetOverlayHue = 96; // hue we shift towards inside radius

    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            int idx = XY(x, y);
            if (idx < 0) continue;
            int dx = x - centerX;
            int dy = y - centerY;
            int distSq = dx*dx + dy*dy;

            if (distSq <= radius*radius && radius > 0) {
                float dist = sqrtf((float)distSq);
                float norm = 1.0f - (dist / (float)radius); // 1.0 at center, 0 at edge
                CHSV current = rgb2hsv_approximate(leds[idx]);

                // Shift hue towards green
                uint8_t hueDiff;
                if (targetOverlayHue > current.hue) {
                    hueDiff = targetOverlayHue - current.hue;
                    current.hue += (uint8_t)(hueDiff * norm);
                } else {
                    hueDiff = current.hue - targetOverlayHue;
                    current.hue -= (uint8_t)(hueDiff * norm);
                }

                // Boost value inside the circle
                uint8_t valueBoost = (uint8_t)(50 * norm);
                current.val = qadd8(current.val, valueBoost);

                leds[idx] = current;
            }
        }
    }

    FastLED.show();
}

void updateRainbowMode() {
    static uint8_t baseHue = 0;
    for (int y = 0; y < MATRIX_HEIGHT; y++) {
        for (int x = 0; x < MATRIX_WIDTH; x++) {
            leds[XY(x, y)] = CHSV(baseHue + (x * 8), 255, BRIGHTNESS);
        }
    }
    FastLED.show();
    baseHue++;
    delay(50); // Adjust as needed
}

void pdateMicrophoneMode(int soundLevel) {
    // Dimensions
    const int W = MATRIX_WIDTH;
    const int H = MATRIX_HEIGHT;

    // Map soundLevel to a hue: quiet=blue(160), loud=red(0)
    uint8_t baseHue = (uint8_t)map(soundLevel, 0, 1023, 160, 0);

    // Set a reasonable base saturation and value
    // For instance, full saturation and a moderate value from LED_COLOR_VALUE.
    // Adjust as needed.
    uint8_t baseSat = 255;
    uint8_t baseVal = LED_COLOR_VALUE;

    // Fill the entire matrix with the base color
    FastLED.clear();
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(baseHue, baseSat, baseVal);
    }

    // Calculate radius for the overlay circle based on soundLevel
    int maxDim = max(W, H);
    int radius = map(soundLevel, 0, 1023, 0, maxDim / 2);
    radius = constrain(radius, 0, maxDim / 2);

    // Center coordinates
    int centerX = W / 2;
    int centerY = H / 2;

    // Target hue for the overlay (green = 96)
    uint8_t targetOverlayHue = 96;

    // Inside the radius, shift hue towards green and boost value.
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            int idx = XY(x, y);
            if (idx < 0) continue;

            int dx = x - centerX;
            int dy = y - centerY;
            int distSq = dx*dx + dy*dy;

            if (distSq <= radius*radius && radius > 0) {
                float dist = sqrtf((float)distSq);
                float norm = 1.0f - (dist / (float)radius); // 1.0 at center, 0 at edge
                CHSV current = rgb2hsv_approximate(leds[idx]);

                // Shift hue towards green
                uint8_t hueDiff;
                if (targetOverlayHue > current.hue) {
                    hueDiff = targetOverlayHue - current.hue;
                    current.hue = current.hue + (uint8_t)(hueDiff * norm);
                } else {
                    hueDiff = current.hue - targetOverlayHue;
                    current.hue = current.hue - (uint8_t)(hueDiff * norm);
                }

                // Boost value inside the circle
                uint8_t valueBoost = (uint8_t)(50 * norm);
                current.val = qadd8(current.val, valueBoost);

                leds[idx] = current;
            }
        }
    }

    FastLED.show();
}
