/*
Adam Detector
Turns on an LED when and object (Adam) is within distance threshold.
*/

const int IR_READ = 1;
const int IR_PIN = 2;
const int LED = 0;

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  delay(500);
  int sensorValue = analogRead(IR_READ);
  float voltage = sensorValue * (5.0 / 1023.0);
  if (voltage >= 0.5) {
    digitalWrite(LED, HIGH);
  }
  else {
    digitalWrite(LED, LOW);
  }
}
