int L_sharpPin = 0;
int R_sharpPin = 1;

const int touchPin = 8;  // Arduino pin connected to the OUTPUT pin of touch sensor

int S1 = 5;
int D1 = 4;
int S2 = 6;
int D2 = 7;

int forward = LOW;
int backward = HIGH;

// Define threshold distance for wall following
int threshold = 200;

// movement functions
void stop() {
  analogWrite(S1, 0);
  analogWrite(S2, 0);
}

void mForward(int speed) {
  digitalWrite(D1, forward);
  digitalWrite(D2, forward);
  analogWrite(S1, speed);
  analogWrite(S2, speed);
}

void mBackward(int speed) {
  digitalWrite(D1, backward);
  digitalWrite(D2, backward);

  analogWrite(S1, speed);
  analogWrite(S2, speed);
}

void tRight(int speed) {
  analogWrite(S2, 0);
  digitalWrite(D1, forward);
  analogWrite(S1, speed);
}

void tLeft(int speed) {
  analogWrite(S1, 0);
  digitalWrite(D2, forward);
  analogWrite(S2, speed);
}

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
  // Read distance from the two Sharp sensors
  int distanceL = analogRead(L_sharpPin);
  int distanceR = analogRead(R_sharpPin);

  // Check if the robot is too close to the wall
  if (distanceL > threshold) {
    // Wall on the left, turn right
    tRight(150);
  } else {
    // No wall on the left, move forward
    mForward(150);
  }

  // Check right sensor for wall
  if (distanceR > threshold) {
    // Wall on the right, turn left
    tLeft(150);
  } else {
    // No wall on the right, move forward
    mForward(150);
  }

  int touchState = digitalRead(touchPin);  // read new state

  if (touchState == HIGH) {
    mForward(150);
  } else if (touchState == LOW) {
    mBackward(150);
    delay(500);

    // if (distanceL > threshold) {
    //   // Wall on the left, turn right
      tRight(150);
      delay(500);
    // }

    // // Check right sensor for wall
    // if (distanceR > threshold) {
    //   // Wall on the right, turn left
    //   tLeft(150);
    //   delay(500);
    // }
  }






  // if (distanceL < thresholdDistance && distanceR < thresholdDistance) {
  //   // Turn right
  //   tRight(100, 200);
  // } else if (distanceL > thresholdDistance && distanceR > thresholdDistance) {
  //   // Move forward
  //   mForward(100, 100);
  // } else {
  //   // Adjust the robot's path
  //   if (distanceL < distanceR) {
  //     // Turn right
  //     tRight(100, 200);
  //   } else {
  //     // Move forward
  //     mForward(100, 100);
  //   }
  // }

  // int touchState = digitalRead(TOUCH_SENSOR_PIN);  // read new state

  // if (touchState == HIGH) {
  //   digitalWrite(LED_PIN, LOW);
  //   mForward(100, 100);
  // } else if (touchState == LOW) {
  //   digitalWrite(LED_PIN, HIGH);
  //   mBackward(100, 100);

  //   if (distanceL > thresholdDistance) {
  //     // Wall on the left, turn right
  //     tRight(100, 200);
  //   }

  //   // Check right sensor for wall
  //   if (distanceR > thresholdDistance) {
  //     // Wall on the right, turn left
  //     tLeft(100, 200);
  //   }
  // }
}