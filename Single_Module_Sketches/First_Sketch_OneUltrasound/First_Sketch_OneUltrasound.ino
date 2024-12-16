#include <FastLED.h>

#define LED_PIN     42          // Pin connected to the NeoPixel matrix
#define MATRIX_WIDTH  16        // Width of the matrix
#define MATRIX_HEIGHT 16        // Height of the matrix
#define NUM_LEDS      MATRIX_WIDTH * MATRIX_HEIGHT

#define TRIGGER_PIN  10         // Pin connected to the ultrasonic sensor trigger
#define ECHO_PIN     11         // Pin connected to the ultrasonic sensor echo

long duration = 1;
long distance = 0;

const int minDistance = 10;     // Minimum distance to start lighting LEDs (in cm)
const int maxDistance = 90;     // Maximum distance to light up all LEDs (in cm)

CRGB leds[MATRIX_WIDTH][MATRIX_HEIGHT];  // 2D LED array for the matrix

void setup() {
  Serial.begin(9600);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  FastLED.addLeds<NEOPIXEL, LED_PIN>((CRGB*)leds, NUM_LEDS);  // Set up the LED matrix
  FastLED.setBrightness(50);   // Set brightness (0 to 255)
  FastLED.clear();             // Clear all LEDs initially
  FastLED.show();              // Update the matrix
}

void loop() {
  // Trigger the ultrasonic sensor
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Read the echo time
  duration = pulseIn(ECHO_PIN, HIGH, 26000); // Timeout after ~450cm
  distance = (duration / 2) * 0.03432;       // Convert to centimeters

  // Check if the distance is valid
  if (distance >= 500 || distance <= 0) {
    Serial.println("No valid measurement");
    FastLED.clear(); // Turn off all LEDs when there's no valid measurement
    FastLED.show();
    delay(100);      // Small delay before the next measurement
    return;          // Skip the rest of the loop
  }

  // Display the valid distance
  Serial.print(distance);
  Serial.println(" cm");

  // Calculate the number of LEDs to light up
  int numLedsOn = 0;

  if (distance <= minDistance) {
    numLedsOn = NUM_LEDS; // Light all LEDs
  } else if (distance >= maxDistance) {
    numLedsOn = 0;        // Light no LEDs
  } else {
    // Map the distance inversely to the number of LEDs
    numLedsOn = map(distance, maxDistance, minDistance, 0, NUM_LEDS);
    numLedsOn = constrain(numLedsOn, 0, NUM_LEDS);
  }

  // Calculate color based on distance (from red to blue)
  uint16_t hue = map(distance, maxDistance, minDistance, 0, 65535); // Hue from red to blue
  CRGB color = CHSV(hue >> 8, 255, 255);

  // Update the LEDs based on the distance
  int ledsOnCount = 0;
  for (int x = 0; x < MATRIX_WIDTH; x++) {
    for (int y = 0; y < MATRIX_HEIGHT; y++) {
      if (ledsOnCount < numLedsOn) {
        leds[x][y] = color;
        ledsOnCount++;
      } else {
        leds[x][y] = CRGB::Black; // Turn off the LED
      }
    }
  }

  FastLED.show(); // Update the matrix
  delay(100);     // Small delay before the next measurement
}
