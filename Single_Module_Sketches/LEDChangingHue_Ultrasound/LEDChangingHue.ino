#include <Adafruit_NeoPixel.h>

#define LED_PIN     42    // Pin connected to the NeoPixel strip
#define NUM_LEDS    8    // Number of LEDs in the strip

int trigger = 10;
int echo = 11;
long duration = 1;
long distance = 0;

const int minDistance = 10;    
const int maxDistance = 90; 

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  
  strip.begin();          
  strip.setBrightness(50); // Set brightness (0 to 255)
  strip.show();           
}

void loop()
{
  // Trigger the ultrasonic sensor
  digitalWrite(trigger, LOW);
  delayMicroseconds(5);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  
  // Read the echo time
  duration = pulseIn(echo, HIGH, 26000); // Timeout after ~450cm
  distance = (duration / 2) * 0.03432; // Convert to centimeters
  
  // Check if the distance is valid
  if (distance >= 500 || distance <= 0) {
    Serial.println("No valid measurement");
    
    // Turn off all LEDs when there's no valid measurement
    for (int i = 0; i < NUM_LEDS; i++) {
      strip.setPixelColor(i, 0); // Turn off the LED
    }
    strip.show();
    
    delay(100); // Small delay before the next measurement
    return; // Skip the rest of the loop
  }

  // Display the valid distance
  Serial.print(distance);
  Serial.println(" cm");
  
  // Calculate the number of LEDs to light up
  int numLedsOn = 0;

  if (distance <= minDistance) {
    numLedsOn = NUM_LEDS; // Light all LEDs
  } else if (distance >= maxDistance) {
    numLedsOn = 0; // Light no LEDs
  } else {
    // Map the distance inversely to the number of LEDs
    numLedsOn = map(distance, maxDistance, minDistance, 0, NUM_LEDS);
    numLedsOn = constrain(numLedsOn, 0, NUM_LEDS);
  }

  // Calculate color based on distance (from red to blue)
  uint16_t hue = map(distance, maxDistance, minDistance, 0, 65535); // Hue from red to blue
  uint32_t color = strip.gamma32(strip.ColorHSV(hue, 255, 255));

  // Update the LEDs based on the distance
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < numLedsOn) {
      strip.setPixelColor(i, color);
    } else {
      strip.setPixelColor(i, 0); // Turn off the LED
    }
  }

  strip.show(); // Update the strip
  
  delay(100); // Small delay before the next measurement
}
