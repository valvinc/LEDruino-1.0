const int sensorPin = A1; // TMP36-Sensor an A0
const float voltageReference = 5.0; // Versorgungsspannung (5V oder 3.3V)

void setup() {
  Serial.begin(9600); // Startet die serielle Kommunikation
}

void loop() {
  // Analogen Wert vom TMP36 auslesen
  int sensorValue = analogRead(sensorPin);

  // Spannung berechnen
  float voltage = sensorValue * (voltageReference / 1023.0);

  // Temperatur in Celsius berechnen
  float temperatureC = (voltage - 0.5) * 100;

  // Temperatur in Fahrenheit berechnen (optional)
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;

  // Ergebnisse ausgeben
  Serial.print("Spannung: ");
  Serial.print(voltage);
  Serial.println(" V");

  Serial.print("Temperatur: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  Serial.print("Temperatur: ");
  Serial.print(temperatureF);
  Serial.println(" °F");

  delay(1000); // 1 Sekunde Pause
}
