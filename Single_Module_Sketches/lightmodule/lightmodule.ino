const int lichtsensorPin = A2; // Pin für den Lichtsensor (analog)

void setup() {
  Serial.begin(9600); // Startet die serielle Kommunikation
}

void loop() {
  // Analogen Wert vom Lichtsensor auslesen
  int lichtWert = analogRead(lichtsensorPin);

  // Lichtintensität auf dem seriellen Monitor ausgeben
  Serial.print("Lichtintensität: ");
  Serial.println(lichtWert);

  delay(500); // Kurze Pause für Stabilität
}
