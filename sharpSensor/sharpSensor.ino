#include <Servo.h>
int dir = 1;
int opposite = 0;
bool runOnce = false;
int speed = 150;
bool turned = false;

// ANALOG PORTS
int movedBack = 0;
int R_sharpPin = 0;
int distanceL = analogRead(R_sharpPin);

int L_sharpPin = 1;
int distanceR = analogRead(L_sharpPin);

const int closeThreshold = 225;
const int farThreshold = 200;

int B_stripePin = 5;
int B_stripeReading = analogRead(B_stripePin)*4;
int B_stripeThreshold = 900;
String B_color = "";

int F_stripePin = 2;
int F_stripeReading = analogRead(F_stripePin)*4;
int F_stripeThreshold = 1000;
String F_color = "";

int circleCount = 0;
bool inRoom;

int R_flamePin = 4;
int rFlame = analogRead(R_flamePin);
int L_flamePin = 3;
int lFlame = analogRead(L_flamePin);
int flameThreshold = 990;
int fireThreshold = 800;


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

// MOVEMENT FUNCTIONS --------------------------------------------------------------------------
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
    mForward(speed);
  }
  else if (touchState == LOW) {
    mBackward(speed);
    delay(400);

  }
}


void wallFollowing(int direction){
  if (direction == 0){
    distanceL = analogRead(R_sharpPin);
    if (distanceL < 125){
      tLeft(speed);
      delay(100);
      mForward(75);
      delay(75);
   } else {
     mForward(speed);
    }

    // Check left sensor for wall
    if (distanceL > 200) {
      // Wall on the left, turn right
      tRight(speed);
      delay(100);
    } else {
     // No wall on the left, move forward
     mForward(speed);
    }
    touch();

  } else if (direction == 1){
    distanceR = analogRead(L_sharpPin);
    if (distanceR < farThreshold){
      tRight(speed);
      delay(100);
      mForward(75);
      delay(75);
    } else {
      mForward(speed);
    }

    // Check left sensor for wall
    if (distanceR > closeThreshold) {
      // Wall on the left, turn right
      tLeft(speed);
      delay(100);
    } else {
      // No wall on the left, move forward
      mForward(speed);
    }
    touch();
  }
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
    circleCount++;
  } 
  // else if (F_color.equals("BLACK") && B_color.equals("WHITE") && circleCount == 0){
  //   inRoom = true;
  //   mForward(100);
  //   delay(250);

  //   // if (dir == 0 && turned == false){
  //   //   mForward(100);
  //   //   delay(500);

  //   //   tRight(150);
  //   //   delay(750);
  //   //   mForward(100);
  //   //   delay(500);
  //   //   tRight(150);
  //   //   delay(750);
  //   //   mForward(100);
  //   //   delay(500);
  //   //   tRight(150);
  //   //   delay(750);
  //   //   mForward(100);
  //   //   delay(500);
  //   //   tRight(150);
  //   //   delay(750);

  //   //   turned = true;
  //   // }
  // } else if (F_color.equals("WHITE") && B_color.equals("BLACK") && circleCount == 0){
  //   inRoom = false;
  //   mForward(100);
  //   delay(250);
  // }
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

if (lFlame < 965 || rFlame < 975){
    mForward(35);
    stop();
    digitalWrite(fanPin, HIGH);
    servoTurn();
    if (lFlame < rFlame){
      tLeft(100);
      if (lFlame < 935 && rFlame < 965){
        stop();
        servoTurn();
      }
    } else if (rFlame < lFlame){
      tRight(100);
      if (lFlame < 935 && rFlame < 965){
        stop();
        servoTurn();
      }
    }
    delay(2000);
  }
  
  // if (lFlame < flameThreshold){
  //   tLeft(100);
  //   if (lFlame < fireThreshold){
  //     stop();
  //     // digitalWrite(fanPin, HIGH);
  //     servoTurn();
  //     delay(1000);
  //   }
  // }

  // if (rFlame < flameThreshold){
  //   tRight(100);
  //   if (rFlame < fireThreshold){
  //     stop();
  //     // digitalWrite(fanPin, HIGH);
  //     servoTurn();
  //     delay(1000);
  //   }
  // }

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

  distanceR = analogRead(L_sharpPin);
  distanceL = analogRead(R_sharpPin);

  if (distanceR > closeThreshold){ //if wall on right start with right wall following
    dir = 1;
    opposite = 0;
  } else if (distanceL > 185 ){ //if wall on left start wil left wall following
    dir = 0;
    opposite = 1;
  }

  mForward(150);    //initial move off of the circle;
  delay(1000);

}


void loop() {
  // wallFollowing(dir); //start wall following based on the position at the start
  stripe();
  flame();

  if (circleCount == 0){
    wallFollowing(dir);
  }

  // if (inRoom == false){
  //   wallFollowing(dir);
  // } else if (inRoom == true){
  //   wallFollowing(opposite);
  // }

  if(circleCount != 0){
    if (runOnce == false){
      mBackward(150);
      delay(250);
      if (dir == 1){
        tLeft(100);
        delay(400);
      } else if (dir == 0){
        tRight(100);
        delay(400);
        mForward(100);
        delay(400);
      }
      runOnce = true;
    }
    wallFollowing(opposite); //when the circle has been passed, start wall following in the opposite direction
  }
}