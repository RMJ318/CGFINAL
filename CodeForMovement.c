#include <MeMCore.h>

MeDCMotor motor1(M1);  // Motor 1 connected to port M1
MeDCMotor motor2(M2);  // Motor 2 connected to port M2

unsigned long forward_interval = 
unsigned long turn_interval = 
unsigned long uTurn_interval = 
unsigned long doubleTurn_interval =
unsigned long nudge_interval = 
unsigned long sampling_interval = 
int colouroutput;
int white_sample;
int black_sample;
int red_sample;
int blue_sample;
int green_sample;
int orange_sample;
 

void celebrate() {// Code for playing celebratory tune
  
}
void stopMotor() {// Code for stopping motor
  motor1.stop();
  motor2.stop();
}
void moveForward() {// Code for moving forward for some short interval
  {
    motor1.run(motor_speed);
    motor2.run(motor_speed);
    delay(forward_interval);
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
void nudgeLeft() {
  motor1.run(motor_speed_slightly_slower);
  motor2.run(motor_speed);
  delay(nudge_interval);
}
void nudgeRight() {// Code for nudging slightly to the right for some short
  motor1.run(motor_speed);
  motor2.run(motor_speed_slightly_slower);
  delay(nudge_interval);
}
void shineIR() {// Code for turning on the IR emitter only}
void shineRed() {// Code for turning on the red LED only}
void shineGreen() {// Code for turning on the green LED only}
void shineBlue() {// Code for turning on the blue LED only}
int detectColour()
{
// Shine Red, read LDR after some delay
// Shine Green, read LDR after some delay
// Shine Blue, read LDR after some delay
// Run algorithm for colour decoding
}
void setup()
{
  //pinmode codes
  white_sample = detect_colour();
  delay(sampling_interval);
  red_sample = detect_colour();
  delay(sampling_interval);
  
}
void loop()
{
// Read ultrasonic sensing distance (choose an appropriate timeout)
// Read IR sensing distance (turn off IR, read IR detector, turn on IR, read IR
detector, estimate distance)
// if within black line, stop motor, detect colour, and take corresponding action
// else if too near to left wall, nudge right
// else if too near to right wall, nudge left
// else move forward
}

