#include <MeMCore.h>

MeDCMotor motor1(M1);  // Motor 1 connected to port M1
MeDCMotor motor2(M2);  // Motor 2 connected to port M2
MeLineFollower lineFinder(PORT_2); // Linefinder connected to port 2

#define motor_speed 128; 
#define FWD_INT //a very short interval for forward();
#define TURN_INT //interval for 90 degree turn;
#define UTURN_INT //interval for u turn;
#define DTURN_INT //interval between each 90 deg turns in a double turn;
#define sampling_interval //interval before inserting the next paper;
//all these in units of milliseconds

// following are for move_forward
#define K_1 0.5;
#define K_2 0.5; //these values will have to be fine tuned

// store previous, baseline just to initialise to random val
float prev_offset_l = baseline_l;
float prev_offset_r = baseline_r;
// end of move_forward values

int colourCode = 0;
//RED == 1
//ORANGE == 2
//GREEN == 3
//BLUE == 4 
// PINK == 5

// gets distance from ultrasonic sensor
float ultrasound_dist()
{
  pinMode(ULTRASONIC, OUTPUT);
  digitalWrite(ULTRASONIC, LOW); 
  delayMicroseconds(2); 
  digitalWrite(ULTRASONIC, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(ULTRASONIC, LOW);
  
  pinMode(ULTRASONIC, INPUT);
  long duration = pulseIn(ULTRASONIC, HIGH, TIMEOUT); 
  if (duration > 0) 
  {
    return (duration / 2.0 / 1000000 * SPEED_OF_SOUND * 100); 
  }
  else
  {
    return -1;
  }
}

float ir_dist() // ir distance reading is likely to be unreliable
{
  float ambient = analogRead(IR_IN); // ambient light level, subtract from recorded 
  delayMicroseconds(10);
  digitalWrite(DECODE_PIN0, HIGH);
  digitalWrite(DECODE_PIN1, HIGH);
  float ir_in = analogRead(IR_IN) - ambient;
  // magic to linearise and convert ir reading to cm
  return ir_in;
}

void celebrate() {// Code for playing celebratory tune
  
}
void stopMotor() {// Code for stopping motor
  motor1.stop();
  motor2.stop();
}

void move_forward() { // Code for moving forward for some short interval
{
  //get distance w/ ultrasound
 ultrasound_dist = ultrasound_dist();
  if (ultrasound_dist > 0)
  {
    float offset_left = baseline_left - ultrasound_dist();
  }
  else // use ir to get distance
   {
    float offset_right = baseline_right - ir_dist();
  }
 // correction = (k1 * (distance from center)) - k2 * (d/dx distance from center))
 int correction = round(K_1 * offset_left - K_2 * (offset_left - prev_offset_left));
 int speed_left = 128 + correction;
 int speed_right = 128 - correction;
 motor1.run(speed_left);
 motor2.run(speed_right);
}

void turnRight() {// Code for turning right 90 deg
  motor1.run(motor_speed);
  motor2.run(motor_speed_slower);
  delay(turn_interval);
}
void turnLeft() {// Code for turning left 90 deg
  motor1.run(motor_speed_slower);
  motor2.run(motor_speed);
  delay(turn_interval);
}
void uTurn() {// Code for u-turn
  motor1.run(motor_speed);
  motor2.run(-motor_speed);
  delay(uTurn_interval);
}
void doubleLeftTurn() {// Code for double left turn
  turnLeft();
  moveForward();
  delay(doubleTurn_interval);
  turnLeft();
}
void doubleRightTurn() {// Code for double right turn
  turnRight();
  moveForward();
  delay(doubleTurn_interval);
  turnRight();
}

// nudge replaced with proportional movement in forward

// combined shineRed/Green/Blue into single function, also in colour sensor

// moved detectColour to colour_sensor.ino


void setup()
{
  //pinmode codes
  white_sample = detect_colour();
  delay(sampling_interval);
  red_sample = detect_colour();
  delay(sampling_interval);
}

// movement code shifted to main.ino
