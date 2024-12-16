int trigger = 7;
int echo = 6;
long duration = 1;
long distance = 0;
int signal = 3;
const int minDistance = 10;    
const int maxDistance =90; 

void setup()
{
Serial.begin (9600);
pinMode(trigger, OUTPUT);
pinMode(echo, INPUT);
pinMode(signal, OUTPUT);
}

void loop()
{
digitalWrite(trigger, LOW);
delay(5);
digitalWrite(trigger, HIGH);
delay(10);
digitalWrite(trigger, LOW);
duration = pulseIn(echo, HIGH);
distance = (duration/2) * 0.03432;
if (distance >= 500 || distance <= 0)
{
Serial.println("Kein Messwert");

}
else{
Serial.println(distance);
Serial.println(" cm");
}
  if (distance <= minDistance) {
    // At 3 cm or less, beep constantly
    digitalWrite(signal, HIGH);
  } 
  else if (distance <= maxDistance) {
    // Map the distance to a delay range (e.g., 50 ms at 5 cm to 1000 ms at 30 cm)
    int beepDelay = map(distance, minDistance, maxDistance, 50, 1000);
    // Ensure beepDelay does not drop below a minimum value for audibility
    beepDelay = max(beepDelay, 50);
    // Trigger the beep
    digitalWrite(signal, HIGH);
    delay(35); // short beep duration
    digitalWrite(signal, LOW);

    delay(beepDelay); // Varying delay based on distance
  } else {
    // Stop beeping if outside the max distance
    digitalWrite(signal, LOW);
  }
  delay(50);
}