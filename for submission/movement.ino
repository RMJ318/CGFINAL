// #define FWD_INT 50 //a very short interval for forward();
#define motor_speed 192
#define turn_interval 400//interval for 90 degree turn;
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
  // Serial.print("duration: ");
  // Serial.println(duration);
  if (duration > 0) 
  {
    // return distance
    return (duration / 2.0 / 1000000 * SPEED_OF_SOUND * 100); 
  }
  // return -1 if timeout, error handling handled by caller
  return -1;
}

int read_ave(int pin, int k)
{
  delay(10);
  int total = 0;
  for (int i = 0; i < k; i++)
  {
    total += analogRead(pin);
    // Serial.print("total: ");
    // Serial.println(total);
    delay(5);
  } 
  return total / k;
}

float offset(void)
{
  float total = (float)read_ave(IR_IN, SAMPLES);
  return 1024 - total;
}

float ir_dist() // ir distance reading is likely to be unreliable
{
  shine_led(0);
  float o1 = offset(); //obtain ambient conditions
  // Serial.print("offset: ");
  // Serial.println(o1);

  float k1 = 2125; // constants used in linearising IR output
  float k2 = 0.85;
  
  delay(10);
  shine_led(IR);
  float raw = 1024 - (float)read_ave(IR_IN, SAMPLES); // obtain with emitter on
  // Serial.print("raw: ");
  // Serial.println(raw);
  float dist = (k1 * (1/(raw - o1))) - k2; // subtract ambient from reading and linearise
  // Serial.print("Distance: ");
  // Serial.println(dist);
  return dist;
}

void celebrate() {// Code for playing celebratory tune
{
buzzer.tone(659, 200); 
buzzer.tone(587,200); 
buzzer.tone(369,400); 
buzzer.tone(415,400); 
buzzer.tone(554,200); 
buzzer.tone(493,200); 
buzzer.tone(293,400); 
buzzer.tone(329,400); 
buzzer.tone(493,200); 
buzzer.tone(440,200); 
buzzer.tone(277,400); 
buzzer.tone(329,400); 
buzzer.tone(440,800); 
buzzer.noTone();
  delay(30000);
}
  
}
void stopMotor() {// Code for stopping motor
  motor1.stop();
  motor2.stop();
}

void moveBackabit()
{
    stopMotor(); 
    motor1.run(motor_speed);
    motor2.run(-motor_speed);
    delay(250);
    stopMotor(); 
}

void moveForward() { // Code for moving forward for some short interval
  //get distance w/ ultrasound
  float ultrasound_d = ultrasound_dist();
  // Serial.print("usound dist: ");
  // Serial.println(ultrasound_d);
  float offset_left = 0;
  int speed_left = motor_speed;
  int speed_right = motor_speed;
  
  if (ultrasound_d > 0)
  {
    offset_left = baseline_left - ultrasound_d;
    // Serial.print("offset_left ");
    // Serial.print(offset_left);
    // correction = (k1 * (distance from center)) - k2 * (d/dx distance from center))
    int correction = round(K_1 * offset_left - K_2 * (offset_left - prev_offset_left));
    prev_offset_left = offset_left; // update prev_offset_left
    // Serial.print("Correction factor: ");
    // Serial.println(correction);
    speed_left += correction;
    speed_right += -correction;
  }
  else // use ir to get distance
  {
    // Serial.println("IR Fallback active");
    float offset_right = ir_dist();
    // Serial.print("offset_right: ");
    // Serial.print(offset_right);
    if (offset_right < 4)
    {
      speed_left = motor_speed / 2;
    }
  }
  motor1.run(-speed_left);
  motor2.run(speed_right);

}

void turnRight() {// Code for turning right 90 deg
  motor1.run(-motor_speed);
  motor2.run(-motor_speed);
  delay(turn_interval);
  stopMotor();
}

void turnLeft() {// Code for turning left 90 deg
  motor1.run(motor_speed);
  motor2.run(motor_speed);
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
  stopMotor();

  motor1.run(-motor_speed);
  motor2.run(motor_speed);
  delay(900);
  stopMotor();

  delay(200);
  turnLeft();
  stopMotor();
}
void doubleRightTurn() {// Code for double right turn
  turnRight();
  stopMotor();

  motor1.run(-motor_speed);
  motor2.run(motor_speed);
  delay(900);
  stopMotor();
  
  delay(200);
  turnRight();
  stopMotor();
}
