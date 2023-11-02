int photocellPin = 0;  // the cell and 10K pulldown are connected to a0
int lightVal;
bool turned = false;

int S1 = 5;
int D1 = 4;
int S2 = 6;
int D2 = 7;

int forward = LOW;
int backward = HIGH;

// movement functions
void mForward() {  // move forward
  digitalWrite(D1, forward);
  digitalWrite(D2, forward);

  analogWrite(S1, 70);
  analogWrite(S2, 70);
}

void mBackward() {  // move backwards
  digitalWrite(D1, backward);
  digitalWrite(D2, backward);

  analogWrite(S1, 70);
  analogWrite(S2, 70);
}

void tRight(int time) {  // turn right
  analogWrite(S2, 0);
  digitalWrite(D1, forward);
  analogWrite(S1, 70);
  delay(time);
}

void tLeft(int time) {  // turn left
  analogWrite(S1, 0);
  digitalWrite(D2, forward);
  analogWrite(S2, 70);
  delay(time);
}


// setup and loop funtions
void setup(void) {
  Serial.begin(9600);
  pinMode(photocellPin, INPUT);

  pinMode(S1, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(D2, OUTPUT);

  analogWrite(photocellPin, HIGH);
}

void loop(void) {
  lightVal = analogRead(photocellPin);  // figure out a range

  if (lightVal > 500) {
    mForward();

  } else if (lightVal < 500 && turned == false) {
    turned = !turned;
    tLeft(500);
    mForward();
    delay(500);

    lightVal = analogRead(photocellPin);


  } else if (lightVal < 500 && turned == true) {
    turned = !turned;
    tRight(500);
    mForward();
    delay(500);

    lightVal = analogRead(photocellPin);
  }

}