
#define motor_speed 192
// #define FWD_INT 50 //a very short interval for forward();
#define turn_interval 100//interval for 90 degree turn;
//all these in units of milliseconds

// following are for move_forward
#define K_1 12
#define K_2 11 //these values will have to be fine tuned

// store previous, baseline just to initialise to random val
float prev_offset_left = baseline_left;
float prev_offset_right = baseline_right;
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
  Serial.print("duration: ");
  Serial.println(duration);
  if (duration > 0) 
  {
    return (duration / 2.0 / 1000000 * SPEED_OF_SOUND * 100); 
  }
  
  return -1;
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

void moveForward() { // Code for moving forward for some short interval
  //get distance w/ ultrasound
  float ultrasound_d = ultrasound_dist();
  Serial.print("usound dist: ");
  Serial.print(ultrasound_d);
  float offset_left = 0;
  int speed_left = 192;
  int speed_right = 192;
  if (ultrasound_d > 0)
  {
    offset_left = baseline_left - ultrasound_d;
    Serial.print("offset_left ");
    Serial.print(offset_left);
    int correction = round(K_1 * offset_left - K_2 * (offset_left - prev_offset_left));
    prev_offset_left = offset_left;
    Serial.print("Correction factor: ");
    Serial.println(correction);
    speed_left += correction;
    speed_right += -correction;
  }
  else // use ir to get distance
  {
    motor1.run(-192);
    motor2.run(192);
  //   float offset_right = baseline_right - ir_dist();
  }
  motor1.run(-speed_left);
  motor2.run(speed_right);
 // correction = (k1 * (distance from center)) - k2 * (d/dx distance from center))
}

void turnRight() {// Code for turning right 90 deg
  motor1.run(motor_speed);
  motor2.run(motor_speed);
  delay(turn_interval);
  stopMotor();
}

void turnLeft() {// Code for turning left 90 deg
  motor1.run(-motor_speed);
  motor2.run(-motor_speed);
  delay(turn_interval);
  stopMotor();
}

void uTurn() {// Code for u-turn
  motor1.run(motor_speed);
  motor2.run(motor_speed);
  delay(2 * turn_interval);
  stopMotor();
}

void doubleLeftTurn() {// Code for double left turn
  turnLeft();
  delay(50);
  stopMotor();
  for (int tick = 0; tick < 40; tick++); // move forward for 40 ticks
  {
  moveForward();
  delay(50);
  }
  stopMotor();
  delay(50);
  turnLeft();
  stopMotor();
}
void doubleRightTurn() {// Code for double right turn
  turnRight();
  delay(50);
  stopMotor();
  for (int tick = 0; tick < 40; tick++); // move forward for 40 ticks
  {
  moveForward();
  delay(50);
  }
  stopMotor();
  delay(50);
  turnRight();
  stopMotor();
}

// nudge replaced with proportional movement in forward

// combined shineRed/Green/Blue into single function, also in colour sensor

// moved detectColour to colour_sensor.ino



// movement code shifted to main.ino
