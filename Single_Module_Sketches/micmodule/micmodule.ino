#include <FastLED.h>

#define MIC_PIN A0       // AO pin of the microphone connected to A0
#define LED_PIN 42       // Data pin for the LED strip
#define NUM_LEDS 8       // Total number of LEDs
#define BRIGHTNESS 100   // LED brightness

CRGB leds[NUM_LEDS];

// Variables for microphone range
int minValue = 105;  // Set minimum detectable mic value
int maxValue = 120;  // Set maximum detectable mic value
int peakLed = 0;     // Peak LED index

void setup() {
  Serial.begin(9600);  // Start Serial Monitor for debugging
  Serial.println("Setup Complete!");
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  // Read the raw microphone value
  int micValue = analogRead(MIC_PIN);

  // Debugging: Print microphone value
  Serial.print("Mic Value: ");
  Serial.println(micValue);

  // Apply noise gate
  if (micValue < minValue) micValue = minValue;  // Ignore very low noise

  // Map the microphone value to a range for visualization
  int loudness = map(micValue, minValue, maxValue, 0, 255);
  loudness = constrain(loudness, 0, 255);  // Keep it within bounds

  // Map loudness to the number of LEDs
  int numLedsOn = map(loudness, 0, 255, 1, NUM_LEDS);

  // Implement a peak hold effect
  if (numLedsOn > peakLed) peakLed = numLedsOn;  // Keep the peak
  peakLed = max(peakLed - 1, 0);  // Gradually fade down

  // Enhanced color gradient (blue -> green -> yellow)
  uint8_t hue;
  if (loudness < 128) {
    hue = map(loudness, 0, 127, 160, 96);  // Blue to Green
  } else {
    hue = map(loudness, 128, 255, 96, 64);  // Green to Yellow
  }

  // Clear all LEDs
  FastLED.clear();

  // Light up LEDs based on the loudness and peak
  for (int i = 0; i < numLedsOn; i++) {
    leds[i] = CHSV(hue, 255, BRIGHTNESS);  // Hue changes with loudness
  }

  // Highlight the peak LED in red for emphasis
  if (peakLed > 0 && peakLed < NUM_LEDS) {
    leds[peakLed - 1] = CRGB::Red;
  }

  // Show the updated LED pattern
  FastLED.show();

  // Add a short delay to stabilize the visualization
  delay(30);
}
