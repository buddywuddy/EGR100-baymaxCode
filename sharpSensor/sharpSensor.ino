int L_sharpPin = 0;
int R_sharpPin = 1;

const int TOUCH_SENSOR_PIN  = 8; // Arduino pin connected to the OUTPUT pin of touch sensor
const int LED_PIN           = 13; // Arduino pin connected to LED's pin

int S1 = 5;
int D1 = 4;
int S2 = 6;
int D2 = 7;

int forward = LOW;
int backward = HIGH;

// movement functions
void stop() {
  analogWrite(S1, 0);
  analogWrite(S2, 0);
}

void mForward(int speed, int time) {
  digitalWrite(D1, forward);
  digitalWrite(D2, forward);

  analogWrite(S1, speed);
  analogWrite(S2, speed);
  delay(time);
}

void mBackward(int speed, int time) {
  digitalWrite(D1, backward);
  digitalWrite(D2, backward);

  analogWrite(S1, speed);
  analogWrite(S2, speed);
  delay(time);
}

void tRight(int speed, int time) {
  analogWrite(S2, 0);
  digitalWrite(D1, forward);
  analogWrite(S1, speed);
  delay(time);
}

void tLeft(int speed, int time) {
  analogWrite(S1, 0);
  digitalWrite(D2, forward);
  analogWrite(S2, speed);
  delay(time);
}

// Define threshold distances for wall following
const int wallThresholdLeft = 200;  // Adjust this value based on sensor readings
const int wallThresholdRight = 200; // Adjust this value based on sensor readings


void setup() {
  pinMode(L_sharpPin, INPUT);
  pinMode(R_sharpPin, INPUT);

  pinMode(S1, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(D2, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // Read sensor values
  int leftSensorValue = analogRead(L_sharpPin);
  int rightSensorValue = analogRead(R_sharpPin);

  // Check left sensor for wall
  if (leftSensorValue > wallThresholdLeft) {
    // Wall on the left, turn right
    tRight(150, 500);
  } else {
    // No wall on the left, move forward
    mForward(150, 100);
  }

  // Check right sensor for wall
  if (rightSensorValue > wallThresholdRight) {
    // Wall on the right, turn left
    tLeft(150, 500);
  } else {
    // No wall on the right, move forward
    mForward(150, 100);
  }

  int touchState = digitalRead(TOUCH_SENSOR_PIN); // read new state

  if (touchState == HIGH) {
    digitalWrite(LED_PIN, LOW);
    mForward(150, 100);
  }
  else if (touchState == LOW) {
    digitalWrite(LED_PIN, HIGH);
    mBackward(150, 100);

    if (leftSensorValue > wallThresholdLeft) {
      // Wall on the left, turn right
      tRight(150, 500);
    }

  // Check right sensor for wall
    if (rightSensorValue > wallThresholdRight) {
      // Wall on the right, turn left
      tLeft(150, 500);
    }

  }
}