// Define pin assignments
const int stripePin = A0;

// Define threshold value for detecting the white stripe
const int threshold = 600;  // Adjust this value based on sensor readings

int S1 = 5;
int D1 = 4;
int S2 = 6;
int D2 = 7;

int forward = LOW;
int backward = HIGH;

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

//---------------------------------------------------------

void setup() {
  // Motor setup
  pinMode(stripePin, INPUT);

  pinMode(S1, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(D2, OUTPUT);


  // Serial communication for debugging (optional)
  Serial.begin(9600);
}

void loop() {
  // Read the photocell value
  int photocellValue = analogRead(stripePin);

  // Check if the robot is on the white stripe
  if (photocellValue > threshold) {
    // Move forward
    mForward(150, 100);
  } else {
    // Stop and turn until the white stripe is found
    stop();
    findWhiteStripe();
  }
}


void findWhiteStripe() {
  // Turn right until the white stripe is found
  tRight(150,100);
  stop();
}