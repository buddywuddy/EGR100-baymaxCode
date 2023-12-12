#include <Servo.h>

// ANALOG PORTS
int movedBack = 0;
int R_sharpPin = 0;
int distanceL = analogRead(R_sharpPin);

int L_sharpPin = 1;
int distanceR = analogRead(L_sharpPin);

const int closeThreshold = 200;
const int farThreshold = 125;

int B_stripePin = 5;
int B_stripeReading = analogRead(B_stripePin)*4;
int B_stripeThreshold = 900;
String B_color = "";

int F_stripePin = 2;
int F_stripeReading = analogRead(F_stripePin)*4;
int F_stripeThreshold = 1000;
String F_color = "";

int stripeCount = 0;
bool inRoom;

int R_flamePin = 4;
int rFlame = analogRead(R_flamePin);
int L_flamePin = 3;
int lFlame = analogRead(L_flamePin);
int flameThreshold = 1000;
int fireThreshold = 985;


Servo motorServo;

// DIGITAL PORTS
const int touchPin  = 8; // Arduino pin connected to the OUTPUT pin of touch sensor
int touchState = digitalRead(touchPin); // read new state

int fanPin = 10;
int servoPin = 9;

int S1 = 5;
int D1 = 4;
int S2 = 6;
int D2 = 7;

int forward = LOW;
int backward = HIGH;

// MOVEMENT FUNCTIONS
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
//-------------------------------------------------------------
void touch(){
  touchState = digitalRead(touchPin);
  if (touchState == HIGH) {
    mForward(175);
  }
  else if (touchState == LOW) {
    mBackward(175);
    delay(400);

  }
}

void rightWallFollowing(){
  distanceR = analogRead(L_sharpPin);
  if (distanceR < farThreshold){
    tRight(175);
    delay(100);
  } else {
    mForward(175);
  }

  // Check left sensor for wall
  if (distanceR > closeThreshold) {
    // Wall on the left, turn right
    tLeft(175);
    delay(100);
  } else {
    // No wall on the left, move forward
    mForward(175);
  }
  touch();
}

void leftWallFollowing(){
  distanceL = analogRead(R_sharpPin);
  if (distanceL < 125){
    tLeft(175);
    delay(100);
  } else {
    mForward(175);
  }

  // Check left sensor for wall
  if (distanceL > 185) {
    // Wall on the left, turn right
    tRight(175);
    delay(100);
  } else {
    // No wall on the left, move forward
    mForward(175);
  }
  touch();
}

void stripe(){
  B_stripeReading = analogRead(B_stripePin)*4;
  F_stripeReading = analogRead(F_stripePin)*4;

  if (B_stripeReading < B_stripeThreshold){
    B_color = "WHITE";
  } else {
    B_color = "BLACK";
  }

  if (F_stripeReading < F_stripeThreshold){
    F_color = "WHITE";
  } else {
    F_color = "BLACK";
  }

  if (F_color.equals(B_color) && B_color.equals("WHITE")){
    stripeCount++;
  } else if (F_color.equals("BLACK") && B_color.equals("WHITE")){
    inRoom = true;
  } else if (F_color.equals("WHITE") && B_color.equals("BLACK")){
    inRoom = false;
  }
}

void servoTurn(){
  for (int angle = 60; angle <= 130; angle += 1) {
    motorServo.write(angle);  // Move the servo to the specified angle
    delay(10);  // Wait for the servo to reach the position
  }

  for (int angle = 130; angle >= 60; angle -= 1) {
    motorServo.write(angle);  // Move the servo to the specified angle
    delay(10);  // Wait for the servo to reach the position
  }
}

void flame(){
  lFlame = analogRead(L_flamePin);
  rFlame = analogRead(R_flamePin);
  
  if (lFlame < flameThreshold){
    tLeft(100);
    if (lFlame < fireThreshold){
      stop();
      // digitalWrite(fanPin, HIGH);
      servoTurn();
      delay(1000);
    }
  }

  if (rFlame < flameThreshold){
    tRight(100);
    if (rFlame < fireThreshold){
      stop();
      // digitalWrite(fanPin, HIGH);
      servoTurn();
      delay(1000);
    }
  }

  motorServo.write(90);
  digitalWrite(fanPin, LOW);
}

//-------------------------------------------------------------
void setup() {
  motorServo.attach(servoPin);

  pinMode(touchPin, INPUT);

  pinMode(L_sharpPin, INPUT);
  pinMode(R_sharpPin, INPUT);
  pinMode(L_flamePin, INPUT);
  pinMode(R_flamePin, INPUT);
  pinMode(F_stripePin, INPUT);
  pinMode(B_stripePin, INPUT);

  pinMode(fanPin, OUTPUT);

  pinMode(S1, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(D2, OUTPUT);

  Serial.begin(9600);

  mForward(100);
  delay(1000);

  if (distanceR < distanceL){
    start = "right";
  } else if (distanceL < distanceR){
    start = "left";
  }

}

void loop() {
  if (distanceR < distanceL
  stripe();
  rightWallFollowing();

  flame();
}