#ifndef MODES_H
#define MODES_H


#define COLOR CRGB::Red  // Change to any color you prefer

void updateUltrasonicMode(long distances[]);
void updateMicrophoneMode(int soundLevel);
void updateLightSensorMode(int lightValue);
void updateTempSensorMode(int temperatureValue);
void updateMultipleSensorsMode(long distances[], int micLevel, int temp, int light);
void updateRainbowMode();
void updateTestPatternMode();

#endif
