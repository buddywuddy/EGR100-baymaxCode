#include <Servo.h>;
Servo servo
int pos = 0;

// analog ports
int L_sharpPin = 
int R_sharpPin =

int flamePin = 

int servoPin = 9

// digital ports
int touchPin  = 8;

// motor pins
int S1 = 5;
int D1 = 4;
int S2 = 6;
int D2 = 7;

int forward = HIGH;
int backward = LOW;

// function for the touch sensor
void touchSensor(){
  int touchState = digitalRead(touchPin); // read new state

  if (touchState == HIGH) {                       // if touch sensor not triggered, move forward at 70 speed
    digitalWrite(D1, forward);
    digitalWrite(D2, forward);

    analogWrite(S1, 70);
    analogWrite(S2, 70);
  }
  else if (touchState == LOW) {                   // if touch sensor triggered, move backward, then pivot 90 degrees
    digitalWrite(D1, backward);
    digitalWrite(D2, backward);

    analogWrite(S1, 70);
    analogWrite(S2, 70);
    delay(1000);

    analogWrite(S1, 0);
    digitalWrite(D2, forward);
    analogWrite(S2, 70);
    delay(1000);
  }
}

void servos(){
  int delta = 50; // milliseconds delay between servo steps
  for(pos = 0; pos < 181; pos++){
    Serial.print("pos: ");
    Serial.println(pos); // in steps of 1 degree
    myservo.write(pos);
    // tell servo to go to position in variable ‘pos’
    delay(delta);
    // waits for the servo to reach the position
    }

  for(pos =180; pos > 0; pos--){
    Serial.print("pos: ");
    Serial.println(pos);
    myservo.write(pos);
    delay(delta);
  }

}

void sharpSensor(){

}

void setup() {
  Serial.begin(9600);
  
  servo.attach(servoPin); // attaches the servo on pin 9 to the servo 

  // input pins             
  pinMode(touchPin, INPUT);
  pinMode(flamePin, INPUT)
  pinMode(L_sharpPin, INPUT);
  pinMode(R_sharpPin, INPUT);
  
  // output pins
  pinMode(servoPin,OUTPUT);


  pinMode(S1, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(D2, OUTPUT);
}

void loop() {
  touchSensor();
}