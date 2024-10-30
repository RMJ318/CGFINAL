#include <MeMCore.h>

MeDCMotor motor1(M1);  // Motor 1 connected to port M1
MeDCMotor motor2(M2);  // Motor 2 connected to port M2

int motor_speed = //forward speed
int motor_speed_slightly_slower = //a lower speed for nudging
int motor_speed_slower = ;//a lower speed for turning

unsigned long forward_interval = //a very short interval for forward();
unsigned long turn_interval = //interval for 90 degree turn;
unsigned long uTurn_interval = //interval for u turn;
unsigned long doubleTurn_interval = //interval between each 90 deg turns in a double turn;
unsigned long nudge_interval = //a very short interval for nudge();
unsigned long sampling_interval = //interval before inserting the next paper;
//all these in units of milliseconds

int colourCode = 0;
//RED == 1
//ORANGE == 2
//GREEN == 3
//BLUE == 4 
// PINK == 5
 

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
void shineRed() {
// Code for turning on the red LED only
  digitalWrite(redPin, HIGH);  
  delay(100);                  
  digitalWrite(redPin, LOW);
}
void shineGreen() {
// Code for turning on the green LED only
  digitalWrite(redPin, HIGH);  
  delay(100);                  
  digitalWrite(redPin, LOW);
}
void shineBlue() {
// Code for turning on the blue LED only
  digitalWrite(bluePin,HIGH);
  delay(100);
  digitaoWrite(bluepin,LOW);
}
int detectColour()
{
  int red_value, green_value, blue_value;
// Shine Red, read LDR after some delay
  shineRed();
 red_value = analogRead(LDR_pin);   
 delay(100);
// Shine Green, read LDR after some delay
  shineGreen();
 green_value = analogRead(LDR_pin);  
 delay(100);
// Shine Blue, read LDR after some delay
  shineBlue();
 blue_value = analogRead(LDR_pin);   
 delay(100);
// Run algorithm for colour decoding
 if (red_value > green_value && red_value > blue_value) {
    return 1;
  } else if (green_value > red_value && green_value > blue_value) {
    return 3;
  } else if (blue_value > red_value && blue_value > green_value) {
    return 4;
  } else if (red_value > blue_value && green_value > blue_value) {
    return 2; 
  } else {
    return 5;
  }
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
 int distance = readUltrasonic();
// Read IR sensing distance (turn off IR, read IR detector, turn on IR, read IR
//detector, estimate distance)
 int irDistance = readIRDistance();
// if within black line, stop motor, detect colour, and take corresponding action
 if (distance < 10) { 
    stopMotor();
    int detected_colour = detectColour();
  switch (detected_colour) {
      case 1: 
        turnRight();  
        break;
      case 2:  
        doubleRightTurn();  
        break;
      case 3:  
        moveForward();  
        break;
      case 4:  
        turnLeft(); 
        break;
      case 5:  
        uTurn();  
        break;
      default:
        stopMotor();
  }
 }
// else if too near to left wall, nudge right
 else if (irDistance < 10) {  
    nudgeRight();
 }
// else if too near to right wall, nudge left
  else if (irDistance > 50) {  
    nudgeLeft();
  }
// else move forward
   else {
    moveForward(); 
   }
}

