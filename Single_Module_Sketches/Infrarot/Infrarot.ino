#include <IRremote.h>

const int RECV_PIN = 7;  // Adjust to your IR sensor's data pin
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();  // Start the receiver
  Serial.println("IR Receiver is enabled");
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.print("IR Signal received: ");
    Serial.println(results.value, HEX);
    irrecv.resume();  // Receive the next signal
  }
}
