// Connect a start switch/touch sensor to digital port 12
// Use analog port 1 for Sharp sensor
// Global variables
int L_Sharp = 1; //use analog port 1 for Sharp sensor
int R_Sharp = 2;
int start sw = 8; //digital port ID, start switch
int interval = 250; //interval between sensor readings

void start press(int sw){
  //sw represents the digital port number that’s connected to the switch
  //function waits for switch to be pressed and released
  while(digitalRead(sw) == HIGH){} //exit when switch pressed
  while(digitalRead(sw) == LOW) {} // continue when switch released
  }

void setup(){
  pinMode(start sw, INPUT);
  // initialize the Serial monitor
  Serial.begin(9600);
  Serial.println(‘‘Hit Start Button’’);
  start press(start sw);
}

void loop(){
  int L_Reading;
  L_Reading = analogRead(L_Sharp);
  //print the sensor reading
  Serial.println(L_Reading);
  delay(interval);

  int R_Reading;
  R_Reading = analogRead(R_Sharp);
  Serial.println(R_Reading);
  delay(interval);
}

