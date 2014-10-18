/*
Adam Detector
Turns on an LED when and object (Adam) is within distance threshold.
*/

const int IR_READ = 1;
const int LED_HERE = 0;
const int LED_GONE = 1;
const int NUM_READINGS = 10;
const float VOLTS_PER_UNIT = 5.0 / 1024;
const float THRESHOLD = 0.5; // Voltage threshold from sensor to indicate Adam is here.

// Use average of multiple readings to smooth sensor input.
int sensorReadings[NUM_READINGS];

// Use millis() to limit the frequency of Adam checks
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
unsigned long adamCheckInterval = 1000;
boolean firstRun = true;

void setup() {
  pinMode(LED_HERE, OUTPUT);
  pinMode(LED_GONE, OUTPUT);
}

void loop() {
  // The IR sensor datasheet says the first measurement takes place in 38.3 ms +/- 9.6 ms.
  // The output is unstable until 5 ms after this first measurement takes place.
  if (firstRun) {
    firstRun = false;
    delay(50);
  }
  
  currentMillis = millis();

  if (previousMillis == 0 || currentMillis - previousMillis > adamCheckInterval) {
    previousMillis = currentMillis;

    if (isAdamHere()) {
      digitalWrite(LED_HERE, HIGH);
      digitalWrite(LED_GONE, LOW);
    }
    else {
      digitalWrite(LED_HERE, LOW);
      digitalWrite(LED_GONE, HIGH);
    }
  }
}

boolean isAdamHere() {
  int total = 0;
  float average = 0;
  for (int index = 0; index < NUM_READINGS; index++) {
    total = total + analogRead(IR_READ);

    delay(10);
  }

  // calculate the average:
  average = (total * 1.0) / NUM_READINGS;
  
  float voltage = average * (5.0 / 1024);
  return voltage >= THRESHOLD;
}
