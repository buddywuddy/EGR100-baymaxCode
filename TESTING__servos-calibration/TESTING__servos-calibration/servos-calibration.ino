// program exercises servo attached to port ‘‘servoport’’
// Include the Servo, Wire, and LiquidCrystal I2C libraries
#include <Servo.h>;
  Servo myservo; // create servo object to control a servo
  int servoport = 9;
  int pos = 0; // variable to store the servo position

void setup(){
  Serial.begin(9600); // initialize serial communication at 9600 baud
  pinMode(servoport,OUTPUT); //set output port
  myservo.attach(servoport); // attaches the servo on pin 9 to the servo
  //object, 600-2400 us pulse width range
  }

void loop(){
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