#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif 
#define PIN 9
#define NUMPIXELS 8

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {

pixels.begin();
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
pixels.setPixelColor(0, pixels.Color(0,255,0));

pixels.show();
delay(1000);

pixels.setPixelColor(0, pixels.Color(0,0,0));
pixels.show();
delay (1000);

}
