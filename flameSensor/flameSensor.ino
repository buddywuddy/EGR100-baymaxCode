int flamePin = 4;
int IRval;
int L_IR;
int R_IR;

int S1 = 5;
int D1 = 4;
int S2 = 6;
int D2 = 7;

int forward = LOW;
int backward = HIGH;

// movement functions
void stop(int time){                      // force stop
  analogWrite(S1, 0);
  analogWrite(S2, 0);
  delay(time);
}

void mForward(int speed, int time) {                 // move forward
  digitalWrite(D1, forward);
  digitalWrite(D2, forward);

  analogWrite(S1, speed);
  analogWrite(S2, speed);
  delay(time);
}

void mBackward(int speed, int time) {                // move backwards
  digitalWrite(D1, backward);
  digitalWrite(D2, backward);

  analogWrite(S1, speed);
  analogWrite(S2, speed);
  delay(time);
}

void tRight(int speed,int time) {           // turn right
  analogWrite(S2, 0);
  digitalWrite(D1, forward);
  analogWrite(S1, speed);
  delay(time);
}

void tLeft(int speed, int time) {            // turn left
  analogWrite(S1, 0);
  digitalWrite(D2, forward);
  analogWrite(S2, speed);
  delay(time);
}


// setup and loop funtions -----------------------------------------------
void setup(void) {
  Serial.begin(9600);
  pinMode(flamePin, INPUT);

  pinMode(S1, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(D2, OUTPUT);
}

void loop() {           //range flame detetcted: 650 - 0
  IRval = analogRead(flamePin);

  if(IRval < 300){
    stop(1000);


  }else if(IRval < 400){
    mForward(50, 100);

  }else if(IRval < 600){
    stop(500);

    tLeft(50, 50);
    stop(500);
    L_IR = analogRead(flamePin);

    tRight(70, 100);
    stop(500);
    R_IR = analogRead(flamePin);

    tLeft(50, 50);

    if(L_IR > R_IR){
      tLeft(50, 50);
    }else if(R_IR > L_IR){
      tRight(50, 50);
    }

  }else{
    mForward(70, 100);


  }
}
