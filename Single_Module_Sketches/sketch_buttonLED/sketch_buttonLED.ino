int trigger = 7;
int echo = 6;
long duration = 1;
long distance = 0;
int piezo = 3;
const int minDistance = 5;    
const int maxDistance =25; 

void setup()
{
Serial.begin (9600);
pinMode(trigger, OUTPUT);
pinMode(echo, INPUT);
pinMode(piezo, OUTPUT);
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

if (distance <= 30)
{
digitalWrite(piezo, HIGH);
}
else
{
digitalWrite(piezo, LOW);
}

delay(1000);
}