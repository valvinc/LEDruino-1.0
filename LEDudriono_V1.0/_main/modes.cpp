#include "modes.h"
#include "config.h"
#include "ledModule.h"
#include <FastLED.h>

long ultrasonicDistances[NUM_SENSORS] = {-1, -1, -1};
int microphoneLevel = 0;
int temperatureValue = 0;
int lightValue = 0;

// Ultrasonic distance mapping (assuming these are defined in config.h)
// If they're not defined, you can define them here.
#ifndef MIN_DISTANCE
#define MIN_DISTANCE 5
#endif

#ifndef MAX_DISTANCE
#define MAX_DISTANCE 60
#endif



// Temperature-to-color mapping (Celsius)
int TEMP_MIN = 10;        // Lower bound of temperature range
int TEMP_MAX = 35;        // Upper bound of temperature range
int TEMP_HUE_COLD = 160;  // Hue for cold (blue)
int TEMP_HUE_HOT = 0;     // Hue for hot (red)

// Light-to-brightness mapping
// Consider that darkness ~15 or 20, daylight ~the values you see (e.g., 274).
// Currently, the animation logic expects a range of 10 to 90 mapped to 30-255.
// If needed, you can adjust these to better fit your sensor output range.
int LIGHT_MIN = 10;       // Minimum light sensor value
int LIGHT_MAX = 300;       // Maximum light sensor value
int BRIGHTNESS_MIN = 30;  // Minimum brightness
int BRIGHTNESS_MAX = 300; // Maximum brightness

// Microphone (sound level) to rows mapping
int SOUND_MIN = 88;       // Minimum sound level
int SOUND_MAX = 95;       // Maximum sound level
// The rows will be mapped from 0 to MATRIX_HEIGHT internally.


// You can also expose hues for the ultrasonic sensors here if desired
uint8_t ULTRA_HUE_1 = 120; // Green for sensor 1 diagonal
uint8_t ULTRA_HUE_2 = 160; // Blue for sensor 2 wave
uint8_t ULTRA_HUE_3 = 200; // Another Blue variant for sensor 3 diagonal


// =======================================================================
// Update Multiple Sensors Mode
// =======================================================================
void updateMultipleSensorsMode(long distances[], int soundLevel, int temperatureVal, int lightVal) {
    const int W = MATRIX_WIDTH; // Matrix width
    const int H = MATRIX_HEIGHT; // Matrix height

    FastLED.clear(); // Clear all LEDs

    // 1. Temperature: Global color setting
    uint8_t tempHue = map(temperatureVal, TEMP_MIN, TEMP_MAX, TEMP_HUE_COLD, TEMP_HUE_HOT);

    // 2. Light: Adjust global brightness
    uint8_t baseBrightness = map(lightVal, LIGHT_MIN, LIGHT_MAX, BRIGHTNESS_MIN, BRIGHTNESS_MAX);
    baseBrightness = constrain(baseBrightness, BRIGHTNESS_MIN, BRIGHTNESS_MAX);

    // 3. Apply Background Color
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            leds[XY(x, y)] = CHSV(tempHue, 255, baseBrightness);
        }
    }

    // 4. Microphone: Multicolor rows based on sound level
    int litRows = map(soundLevel, SOUND_MIN, SOUND_MAX, 0, H);
    litRows = constrain(litRows, 0, H);

    for (int y = 0; y < litRows; y++) {
        uint8_t rowHue = map(y, 0, (litRows > 1 ? litRows - 1 : 1), 96, 0);
        for (int x = 0; x < W; x++) {
            leds[XY(x, y)] = CHSV(rowHue, 255, 255); // Bright multicolor rows
        }
    }

    // 5. Ultrasonic Sensors: Diagonal and center animations

    // Sensor 1: Top-left diagonal covering 4 rows
    if (distances[0] != -1) {
        int diagonalLength = map(distances[0], MIN_DISTANCE, MAX_DISTANCE, 0, H);
        diagonalLength = constrain(diagonalLength, 0, H);

        for (int d = 0; d < diagonalLength; d++) {
            for (int rowOffset = 0; rowOffset < 4; rowOffset++) { // 4 rows per sensor
                int x = d; // Diagonal: left to right
                int y = d + rowOffset; // Adjust row for 4-row representation
                if (x < W / 2 && y < H) {
                    leds[XY(x, y)] = CHSV(ULTRA_HUE_1, 255, 255); // Green
                }
            }
        }
    }

    // Sensor 2: Center column as a 4x4 block
    if (distances[1] != -1) {
        int blockPosition = map(distances[1], MIN_DISTANCE, MAX_DISTANCE, 0, H - 4); // Ensure block stays within bounds
        blockPosition = constrain(blockPosition, 0, H - 4);

        for (int y = blockPosition; y < blockPosition + 4; y++) { // 4 rows
            for (int x = (W / 2) - 2; x < (W / 2) + 2; x++) { // 4 columns centered
                if (x >= 0 && x < W && y >= 0 && y < H) { // Bounds check
                    leds[XY(x, y)] = CHSV(ULTRA_HUE_2, 255, 255); // Blue block
                }
            }
        }
    }

    // Sensor 3: Top-right diagonal covering 4 rows
    if (distances[2] != -1) {
        int diagonalLength = map(distances[2], MIN_DISTANCE, MAX_DISTANCE, 0, H);
        diagonalLength = constrain(diagonalLength, 0, H);

        for (int d = 0; d < diagonalLength; d++) {
            for (int rowOffset = 0; rowOffset < 4; rowOffset++) { // 4 rows per sensor
                int x = W - 1 - d; // Diagonal: right to left
                int y = d + rowOffset; // Adjust row for 4-row representation
                if (x >= W / 2 && y < H) {
                    leds[XY(x, y)] = CHSV(ULTRA_HUE_3, 255, 255); // Red
                }
            }
        }
    }

    FastLED.show(); // Push updates to LEDs
}


/*
// =======================================================================
// Test Pattern Mode
// =======================================================================
void updateTestPatternMode() {
    FastLED.clear();
    for (int y = 0; y < MATRIX_HEIGHT; y++) {
        for (int x = 0; x < MATRIX_WIDTH; x++) {
            int index = XY(x, y);
            if (index != -1) {
                leds[index] = CHSV(96, 255, 200); // Static color for testing
            }
        }
        FastLED.show();
        delay(500); // Wait 500ms before moving to the next row
        FastLED.clear();
    }
}

*/
// =======================================================================
// Ultrasonic Mode: Shows average distance across sensors
// =======================================================================
void updateUltrasonicMode(long distances[]) {
    const int W = MATRIX_WIDTH; // Matrix width
    const int H = MATRIX_HEIGHT; // Matrix height

    FastLED.clear(); // Clear all LEDs

    // Sensor 1: Top-left diagonal covering 4 rows
    if (distances[0] != -1) {
        int diagonalLength = map(distances[0], MIN_DISTANCE, MAX_DISTANCE, 0, H);
        diagonalLength = constrain(diagonalLength, 0, H);

        for (int d = 0; d < diagonalLength; d++) {
            for (int rowOffset = 0; rowOffset < 4; rowOffset++) { // 4 rows per sensor
                int x = d; // Diagonal: left to right
                int y = d + rowOffset; // Adjust row for 4-row representation
                if (x < W / 2 && y < H) {
                    leds[XY(x, y)] = CHSV(ULTRA_HUE_1, 255, 255); // Green
                }
            }
        }
    }

    // Sensor 2: Center column as a 4x4 block
    if (distances[1] != -1) {
        int blockPosition = map(distances[1], MIN_DISTANCE, MAX_DISTANCE, 0, H - 4); // Ensure block stays within bounds
        blockPosition = constrain(blockPosition, 0, H - 4);

        for (int y = blockPosition; y < blockPosition + 4; y++) { // 4 rows
            for (int x = (W / 2) - 2; x < (W / 2) + 2; x++) { // 4 columns centered
                if (x >= 0 && x < W && y >= 0 && y < H) { // Bounds check
                    leds[XY(x, y)] = CHSV(ULTRA_HUE_2, 255, 255); // Blue block
                }
            }
        }
    }

    // Sensor 3: Top-right diagonal covering 4 rows
    if (distances[2] != -1) {
        int diagonalLength = map(distances[2], MIN_DISTANCE, MAX_DISTANCE, 0, H);
        diagonalLength = constrain(diagonalLength, 0, H);

        for (int d = 0; d < diagonalLength; d++) {
            for (int rowOffset = 0; rowOffset < 4; rowOffset++) { // 4 rows per sensor
                int x = W - 1 - d; // Diagonal: right to left
                int y = d + rowOffset; // Adjust row for 4-row representation
                if (x >= W / 2 && y < H) {
                    leds[XY(x, y)] = CHSV(ULTRA_HUE_3, 255, 255); // Red
                }
            }
        }
    }

    FastLED.show(); // Push updates to LEDs
}



// =======================================================================
// Light Sensor Mode: Adjusts brightness based on light
// =======================================================================
void updateLightSensorMode(int lightVal) {
    uint8_t val = map(lightVal, LIGHT_MIN, LIGHT_MAX, BRIGHTNESS_MIN, BRIGHTNESS_MAX);
    val = constrain(val, BRIGHTNESS_MIN, BRIGHTNESS_MAX);

    FastLED.clear();
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(96, 255, val); // Green hue with varying brightness
    }
    FastLED.show();
}


// =======================================================================
// Temperature Sensor Mode: Smooth color transition
// =======================================================================
void updateTempSensorMode(int temperatureVal) {
    uint8_t targetHue = map(temperatureVal, TEMP_MIN, TEMP_MAX, TEMP_HUE_COLD, TEMP_HUE_HOT);
    FastLED.clear();
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(targetHue, 255, 200); // Adjust hue based on temperature
    }
    FastLED.show();
}


// =======================================================================
// Rainbow Mode: Cycling rainbow animation
// =======================================================================
void updateRainbowMode() {
    static uint8_t baseHue = 0;
    for (int y = 0; y < MATRIX_HEIGHT; y++) {
        for (int x = 0; x < MATRIX_WIDTH; x++) {
            leds[XY(x, y)] = CHSV(baseHue + (x * 8), 255, BRIGHTNESS);
        }
    }
    FastLED.show();
    baseHue++;

}


// =======================================================================
// Microphone Mode: Sound-responsive rows
// =======================================================================
void updateMicrophoneMode(int soundLevel) {
    const int W = MATRIX_WIDTH;
    const int H = MATRIX_HEIGHT;

    int litRows = map(soundLevel, SOUND_MIN, SOUND_MAX, 0, H);
    litRows = constrain(litRows, 0, H);

    for (int y = 0; y < H; y++) {
        uint8_t rowHue = (y < litRows) ? map(y, 0, (litRows > 1 ? litRows - 1 : 1), 96, 0) : 160;
        uint8_t rowBrightness = (y < litRows) ? 255 : 50;

        for (int x = 0; x < W; x++) {
            leds[XY(x, y)] = CHSV(rowHue, 255, rowBrightness);
        }
    }
    FastLED.show();
}
