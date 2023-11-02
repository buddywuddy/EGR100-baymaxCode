const int direction = 4; // digital pin 4 controls M1 direction
const int speed = 5; // analog pin 5 controls M1 speed
int spin = HIGH; // will determine which direction to spin
int vel = 0; // will determine magnitude of M1 rotation velocity, start at 0 (non moving)
void setup()
{
pinMode(direction, OUTPUT); // make sure our pins our outputs
pinMode(speed, OUTPUT);
}
void loop()
{
spin = !spin; // toggle the direction our motor is spinning
digitalWrite(direction, spin); // set motor direction to ‘‘spin’’ variable
// the direction of HIGH or LOW will be determined by the wiring of your motor
analogWrite(speed, vel); // set the speed of M1 to vel
delay (2000);
if (vel<=235) // increase vel in increments of 20 until 255
{
vel = vel+20;
}
else
{
vel = 255;
}
}