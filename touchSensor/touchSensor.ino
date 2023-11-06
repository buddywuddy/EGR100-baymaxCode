const int TOUCH_SENSOR_PIN  = 8; // Arduino pin connected to the OUTPUT pin of touch sensor
const int LED_PIN           = 13; // Arduino pin connected to LED's pin

int S1 = 5;
int D1 = 4;
int S2 = 6;
int D2 = 7;

int forward = LOW;
int backward = HIGH;

void mForward(){
  digitalWrite(D1, forward);
  digitalWrite(D2, forward);

  analogWrite(S1, 150);
  analogWrite(S2, 150);
}

void mBackward(){
  digitalWrite(D1, backward);
  digitalWrite(D2, backward);

  analogWrite(S1, 150);
  analogWrite(S2, 150);
}

void tRight(int time){
  analogWrite(S2, 0);
  digitalWrite(D1, forward);
  analogWrite(S1, 150);
  delay(time);
}

void tLeft(int time){
  analogWrite(S1, 0);
  digitalWrite(D2, forward);
  analogWrite(S2, 150);
  delay(time);
}

void setup() {
  Serial.begin(9600);               // initialize serial
  pinMode(TOUCH_SENSOR_PIN, INPUT); // set arduino pin to input mode
  pinMode(LED_PIN, OUTPUT);         // set arduino pin to output mode

  pinMode(S1, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(D2, OUTPUT);
}

void loop() {
  int touchState = digitalRead(TOUCH_SENSOR_PIN); // read new state

  if (touchState == HIGH) {
    digitalWrite(LED_PIN, LOW);
    mForward();
  }
  else if (touchState == LOW) {
    digitalWrite(LED_PIN, HIGH);
    mBackward();
    delay(1000);

    tLeft(500);
  }
}