#include <Servo.h>;
Servo servo;

// analog ports
int L_sharpPin = 0;
int R_sharpPin = 1;

int flamePin = 4;

int servoPin = 9;

int stripePin = 2;
int lightVal;

// digital ports
int touchPin = 8;

// motor pins
int S1 = 5;
int D1 = 4;
int S2 = 6;
int D2 = 7;

int forward = LOW;
int backward = HIGH;

/* ------------------------ MOVEMENT FUNCTIONS ------------------------
  stop: 
    sets speed of both motors to stop baymax

  mForward:
    parameters --> speed, time
    moves baymax forward at some defined 'speed' and for 'time' milliseconds

  mBackward:
    parameters --> speed, time
    moves baymax forward at some defined 'speed' and for 'time' milliseconds

  tRight:
    parameters --> speed, time
    sets one motor to speed 0 while the other motor moves forward at some defined 
    'speed' and for 'time' milliseconds.

    Pivots baymax to the right

  tLeft:
    parameters --> speed, time
    sets one motor to speed 0 while the other motor moves forward at some defined 
    'speed' and for 'time' milliseconds.
    
    Pivots baymax to the left
------------------------------------------------------------------ */

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

/* ------------------------ TOUCH SENSOR ------------------------ */
void touchSensor() {
  int touchState = digitalRead(touchPin);  // read new state

  if (touchState == HIGH) {
    mForward(150, 100);
  } else if (touchState == LOW && sharpSensor(L_sharpPin) > 400) {
    mBackward(150, 1000);

    tRight(150, 250);
  } else if (touchState == LOW && sharpSensor(R_sharpPin) > 400) {
    mBackward(150, 1000);

    tLeft(150, 250);
  }
}

void servos() {  //UNFINISHED
}

/* ------------------------ SHARP SENSOR ------------------------- */
int sharpSensor(int sharpPin) {
  int distance;
  distance = analogRead(sharpPin);
}

/* ------------------------ STRIPE SENSOR ------------------------ */
bool stripeSensor() {  // UNFINISHED
  bool inRoom = false;
  lightVal = analogRead(stripePin);

  if (lightVal > 500) {
    inRoom = true;
  }
  return inRoom;
}

/* ------------------------- FLAME SENSOR ------------------------ */
void flameSensor() {  // UNFINISHED
  bool flameDetected = false;
  int IRval;
  int L_IR;
  int R_IR;

  IRval = analogRead(flamePin);

  if (IRval < 600) {  // flame range: 600-0  -->  stop baymax when IRval < 150 to prevent burning
    flameDetected = true;
  }

  if (flameDetected == false) {
    tRight(150, 100);

  } else if (flameDetected == true && IRval < 400) {
    mForward(150, 100);
    extinguish();

    flameDetected = false;
  }

  //once flame no longer detected, turn 180 and continue
  mBackward(150, 500);
  tLeft(150, 250);
}

/* -------------------- EXTINGUISHING SEQUENCE ------------------- */
void extinguish() {  // UNFINISHED
  //code that turns on extinguishing mechanism
}

/* ----------------------------------------------------------------------------------------------
  Setup Function:
    Serial.begin
    Set INPUT/OUTPUT pinmodes for all sensors
    initialize servo objects

  Loop Function:
    startup sequence to move robot out of start zone
    loop the touch sensor function --> if baymax runs into a wall, back up, turn, keep moving
    when the stripe sensor triggered, baymax has entered a room --> execute flame sequence 
---------------------------------------------------------------------------------------------- */

void setup() {
  Serial.begin(9600);

  servo.attach(servoPin);  // attaches the servo on pin 9 to the servo

  // input pins
  pinMode(touchPin, INPUT);
  pinMode(flamePin, INPUT);
  pinMode(L_sharpPin, INPUT);
  pinMode(R_sharpPin, INPUT);
  pinMode(stripePin, INPUT);

  // output pins
  pinMode(servoPin, OUTPUT);

  pinMode(S1, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(D2, OUTPUT);
}

void loop() {
  mForward(150, 1000);

  touchSensor();
  // if (stripeSensor() == true){
  //   flameSensor();
  // }
}