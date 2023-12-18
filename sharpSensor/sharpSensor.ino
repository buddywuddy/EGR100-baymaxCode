// IMPORT LIBRARIES
#include <Servo.h>
bool runOnce = false;
bool turned = false;


// ANALOG PORTS --------------------------------------------------------------------------

// sharp sensor pins and global variables
int R_sharpPin = 0;
int distanceL = analogRead(R_sharpPin);
int L_sharpPin = 1;
int distanceR = analogRead(L_sharpPin);

const int closeThreshold = 225;
const int farThreshold = 200;


// stripe sensor pins and global variables
int B_stripePin = 5;
int B_stripeReading = analogRead(B_stripePin)*4;
int B_stripeThreshold = 900;
String B_color = "";

int F_stripePin = 2;
int F_stripeReading = analogRead(F_stripePin)*4;
int F_stripeThreshold = 1000;
String F_color = "";

int dir = 1;
int opposite = 0;
int circleCount = 0;
bool inRoom;


// flame sensor pins and global variables
int R_flamePin = 4;
int rFlame = analogRead(R_flamePin);
int L_flamePin = 3;
int lFlame = analogRead(L_flamePin);
int flameThreshold = 990;
int fireThreshold = 800;


// servos
Servo motorServo;


// DIGITAL PORTS --------------------------------------------------------------------------

// touch sensor pin and global variables
const int touchPin  = 8; 
int touchState = digitalRead(touchPin);


// extinguishing mechanism pins
int fanPin = 10;
int servoPin = 9;


// motor pins and global variables
int S1 = 5;
int D1 = 4;
int S2 = 6;
int D2 = 7;

int forward = LOW;
int backward = HIGH;
int speed = 150;

// MOVEMENT FUNCTIONS --------------------------------------------------------------------------
// stop:
void stop() {
  analogWrite(S1, 0);
  analogWrite(S2, 0);
}


// move forward:
void mForward(int speed) {
  digitalWrite(D1, forward);
  digitalWrite(D2, forward);

  analogWrite(S1, speed);
  analogWrite(S2, speed);
}

// move backward:
void mBackward(int speed) {
  digitalWrite(D1, backward);
  digitalWrite(D2, backward);

  analogWrite(S1, speed);
  analogWrite(S2, speed);
}

// turn right:
void tRight(int speed) {
  analogWrite(S2, 0);
  digitalWrite(D1, forward);
  analogWrite(S1, speed);
}

// turn left:
void tLeft(int speed) {
  analogWrite(S1, 0);
  digitalWrite(D2, forward);
  analogWrite(S2, speed);
}


// SENSOR FUNCTIONS --------------------------------------------------------------------------

//touch sensor function!
void touch(){
  touchState = digitalRead(touchPin);   //read the state of the touch sensor
  if (touchState == HIGH) {             // if touchstate is high, sensor hasn;t been activated keep moving forward
    mForward(speed);
  } else if (touchState == LOW) {       // if touchstate is low, sensor has been activated so move backward a bit
    mBackward(speed);
    delay(400);
  }
}

// wall following function:
// parameters: direction (takes in an initial direction value that tells the robot which wall to start following based on the hallway it starts in)
void wallFollowing(int direction){      // 
  if (direction == 0){                  // left wall following:
    distanceL = analogRead(R_sharpPin);
    if (distanceL < 125){               // if robot is too far from the wall, turn left a little to stay on the left wall
      tLeft(speed);
      delay(100);
      mForward(75);
      delay(75);
   } else {
     mForward(speed);
    }

    if (distanceL > 200) {              // if robot is too close to the wall, turn right a little to not bump into the wall
      tRight(speed);
      delay(100);
    } else {
     mForward(speed);
    }
    touch();                            
                                        // run touch sensor code in case robot hits the wall
  } else if (direction == 1){           // right wall following:
    distanceR = analogRead(L_sharpPin);
    if (distanceR < farThreshold){      // if robot is too far from the wall, turn right a little to stay on the left wall
      tRight(speed);
      delay(100);
      mForward(75);
      delay(75);
    } else {
      mForward(speed);
    }

    if (distanceR > closeThreshold) {   // if robot is too close to the wall, turn left a little to not bump into the wall
      tLeft(speed);
      delay(100);
    } else {
      mForward(speed);
    }
    touch();
                                        // run touch sensor code in case robot hits the wall
  }
}


// stripe sensor code:
void stripe(){
  B_stripeReading = analogRead(B_stripePin)*4;    // becuase the difference between whit enad black readings is too small, multiply the reading value by 4 to ensure a big enough difference between the readings
  F_stripeReading = analogRead(F_stripePin)*4;

  if (B_stripeReading < B_stripeThreshold){       // if the behind stripe sensor is less than the threshold, it outputs white as the color
    B_color = "WHITE";
  } else {                                        // if not, the output color is black
    B_color = "BLACK";
  }

  if (F_stripeReading < F_stripeThreshold){       // if the front stripe sensor is less than the threshold, it outputs white as the color
    F_color = "WHITE";
  } else {                                        // if not, the output color is black
    F_color = "BLACK";
  }

  // if both front and back stripe sensors output white, the robot is on the circle.
  if (F_color.equals(B_color) && B_color.equals("WHITE")){
    circleCount++;
  } 
}

// servos back and forth function
void servoTurn(){
  for (int angle = 60; angle <= 130; angle += 1) {
    motorServo.write(angle);
    delay(10);
  }

  for (int angle = 130; angle >= 60; angle -= 1) {
    motorServo.write(angle);
    delay(10);
  }
}


// flame sensor:
void flame(){
  lFlame = analogRead(L_flamePin);          // left flame reading
  rFlame = analogRead(R_flamePin);          // right flame reading

if (lFlame < 965 || rFlame < 975){          // if  the left or right flame reading are less than a threshold, than robot moves forward, stops, and the fan turns on and moves back and forth
    mForward(35);
    stop();
    digitalWrite(fanPin, HIGH);
    servoTurn();
    if (lFlame < rFlame){                   // if the left reading is higher than the right reading, the robot turns left
      tLeft(100);
      if (lFlame < 935 && rFlame < 965){    // if the robot gets too close, the it stops so the robot doesn't get burned
        stop();
        servoTurn();
      }
    } else if (rFlame < lFlame){            // if the right reading is higher than the right reading, the robot turns left
      tRight(100);
      if (lFlame < 935 && rFlame < 965){    // if the robot gets too close, the it stops so the robot doesn't get burned
        stop();
        servoTurn();
      }
    }
    delay(2000);
  }
  motorServo.write(90);                     // after the flame is put out, the fan turns of and the servos stop oscilating.
  digitalWrite(fanPin, LOW);
}


//-------------------------------------------------------------
void setup() {
  motorServo.attach(servoPin);

// Setting Pin Modes INPUT
  // digital ports
  pinMode(touchPin, INPUT);
  // analog ports
  pinMode(L_sharpPin, INPUT);
  pinMode(R_sharpPin, INPUT);
  pinMode(L_flamePin, INPUT);
  pinMode(R_flamePin, INPUT);
  pinMode(F_stripePin, INPUT);
  pinMode(B_stripePin, INPUT);


// Setting Pin Modes OUTPUT
  // digital ports
  pinMode(fanPin, OUTPUT);
  // analog ports
  pinMode(S1, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(D2, OUTPUT);

  Serial.begin(9600);

  // take initial sharp sensor readings
  distanceR = analogRead(L_sharpPin);
  distanceL = analogRead(R_sharpPin);


  // if wall is on right start right wall following, if wall is on left start left wall following
  if (distanceR > closeThreshold) {
    dir = 1;
    opposite = 0;
  } else if (distanceL > 185 ) {
    dir = 0;
    opposite = 1;
  }
  //move forward for 1 sec to get off the circle
  mForward(150);
  delay(1000);

}


void loop() {
  stripe();                        // run stripe sensor code
  flame();                         // run flame sensor code

  // if the robot hasn;t passed the circle yet, start the initial wall following
  if (circleCount == 0){
    wallFollowing(dir);
  }

  // if the circle has been passed, wall follow in the opposite direction
  if(circleCount != 0){
    if (runOnce == false){         // run the following only once:
      mBackward(150);              // move backward slightly to not get stuck in the corner
      delay(250);
      if (dir == 1){               // if robot strts right wall following turn left a bit to get into the floating room
        tLeft(100);
        delay(400);
      } else if (dir == 0){        // if robot starts left following, turn rught and move forward a bit
        tRight(100);
        delay(400);
        mForward(100);
        delay(400);
      }
      runOnce = true;              // run once is true now becuase it has been run once
    }
    wallFollowing(opposite);        // when the circle has been passed, start wall following in the opposite direction
  }
}