#include <MeMCore.h>

MeDCMotor motor1(M1);  // Motor 1 connected to port M1
MeDCMotor motor2(M2);  // Motor 2 connected to port M2

long right_duration = 
long left_duration = 

void celebrate() {// Code for playing celebratory tune
  
}
void stopMotor() {// Code for stopping motor
  motor1.stop();
  motor2.stop();
}
void moveForward() {// Code for moving forward for some short interval
  for(long i = 0; i < 2; i ++)
  {
    motor1.run(Forward_Left_Pins[i] , HIGH);
    motor1.run(Backward_Left_Pins[i] , LOW);
    motor1.run(Forward_Right_Pins[i] , HIGH);
    motor1.run(Backward_Right_Pins[i] , LOW);
  }

}
void turnRight() {// Code for turning right 90 deg
  for(long i = 0; i < 2; i ++)
  {
    motor1.run(Forward_Left_Pins[i] , HIGH);
    motor1.run(Backward_Left_Pins[i] , LOW);
    motor1.run(Forward_Right_Pins[i] , LOW);
    motor1.run(Backward_Right_Pins[i] , HIGH);
  }
  delay(right_duration)
}
void turnLeft() {// Code for turning left 90 deg
  for(long i = 0; i < 2; i ++)
  {
    motor1.run(Forward_Left_Pins[i] , LOW);
    motor1.run(Backward_Left_Pins[i] , HIGH);
    motor1.run(Forward_Right_Pins[i] , HIGH);
    motor1.run(Backward_Right_Pins[i] , LOW);
  }
  delay(left_duration)
}
void uTurn() {// Code for u-turn
  turnLeft();
  turnLeft();
}
void doubleLeftTurn() {// Code for double left turn
  turnLeft();
  moveForward();
  delay(doubleLeftTurn_interval);
  turnLeft();
}
void doubleRightTurn() {// Code for double right turn
  turnRight();
  moveForward();
  delay(doubleLeftTurn_interval);
  turnRight();
}
void nudgeLeft() {// Code for nudging slightly to the left for some short interval
  
}
void nudgeRight() {// Code for nudging slightly to the right for some short
interval}
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
// Configure pinMode for A0, A1, A2, A3
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

