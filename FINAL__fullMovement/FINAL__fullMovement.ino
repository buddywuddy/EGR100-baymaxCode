#include <Servo.h>;
Servo servo;
int pos = 0;

// analog ports
int L_sharpPin = 
int R_sharpPin =

int flamePin =
int IRval; 

int servoPin = 9;

int stripePin =
int lightVal;

// digital ports
int touchPin  = 8;

// motor pins
int S1 = 5;
int D1 = 4;
int S2 = 6;
int D2 = 7;

int forward = LOW;
int backward = HIGH;

void mForward(){
  digitalWrite(D1, forward);
  digitalWrite(D2, forward);

  analogWrite(S1, 70);
  analogWrite(S2, 70);
}

void mBackward(){
  digitalWrite(D1, backward);
  digitalWrite(D2, backward);

  analogWrite(S1, 70);
  analogWrite(S2, 70);
}

void tRight(int time){
  analogWrite(S2, 0);
  digitalWrite(D1, forward);
  analogWrite(S1, 70);
  delay(time);
}

void tLeft(int time){
  analogWrite(S1, 0);
  digitalWrite(D2, forward);
  analogWrite(S2, 70);
  delay(time);
}

// function for the touch sensor
void touchSensor(){
  int touchState = digitalRead(TOUCH_SENSOR_PIN); // read new state

  if (touchState == HIGH) {
    digitalWrite(LED_PIN, LOW);
    mForward();
  }
  else if (touchState == LOW && sharpSensor(L_SharpPin) == HIGH) {
    digitalWrite(LED_PIN, HIGH);
    mBackward();
    delay(1000);

    tRight();
  }else if (touchState == LOW && sharpSensor(R_SharpPin) == HIGH) {
    digitalWrite(LED_PIN, HIGH);
    mBackward();
    delay(1000);

    tLeft();
  }
}

void servos(){                            //UNFINISHED
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

void sharpSensor(int sharpPin){
//sharp Sensor Code
}


bool stripeSensor(){                      //UNFINISHED
  bool inRoom = false;
  lightVal = analogRead(stripePin);
  
  if (lightVal > threshold){
    inRoom = true;
  }
  return inRoom;
}


void flameSensor(){                        //UNFINISHED
  bool flameDetected = false;
  IRval = analogRead(flamePin);

  if(IRVal > threshold){   //threshold must be defined
    flameDetected = true;
  }

  if (flameDetected == false){
    tRight(100);

  } else if (flameDetected == true && IRval < threshold){
    mForward();
    extinguish();
  }

}

void extinguish(){                        //UNFINISHED
  //code that turns on extinguishing mechanism
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
  if (stripeSensor() == true){
    flameSensor();
  }
}