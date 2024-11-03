/**
* this the main function folder
*/

#include "MeOrion.h"

// LED control pins, connected to 2 - 4 Decoder
// inputs too
#define DECODE_PIN0 = A0;
#define DECODE_PIN1 = A1;
#define LDR_IN = A2;
#define IR_IN = A3;
#define ULTRASOUND 12;
#define TIMEOUT 2000;
#define SPEED_OF_SOUND 343;
#define BASELINE XXXX;
#define C_FACTOR 0.5; // Correction factor for forward movement

MeDCMotor motor1(M1);
MeDCMotor motor2(M2);
MeLineFollower lineFinder(PORT_2);

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

void move_forward()
{
  // proportional movement method
  //step 1: get distance w/ ultrasound
  if (ultrasound_dist > 0)
  {
    float offset_left = baseline_left / ultrasound_dist(); // >1 if too close to wall, <1 if too far from wall
  }
    // ir sensor as fallback
  else
  {
    float offset_right = baseline_right - ir_dist();
  }
  // 
  motor1.run(100 * offset_left) // run left wheel runs faster if close to left wall, and slower if far from left wall
}

float baseline_left;
float baseline_right;

void setup()
{
  pinMode(DECODE_PIN0, OUTPUT);
  pinMode(DECODE_PIN1, OUTPUT);
  pinMode(LDR_IN, INPUT);
  pinMode(IR_IN, INPUT);
  baseline_left = ultrasound_dist();
  baseline_right = ir_dist();
  Serial.begin(9600);
}

void loop()
{
  //step 1: IR Line detector
  int sensorState = lineFinder.readSensors();
  if (sensorState != S1_OUT_S2_OUT) //line detected
  {
    motor1.stop;
    motor2.stop;
    see_colour();
  }
  else
  {
    move_forward();
  }
  //delay(10); bot might take too long figuring out everything above to wait
}
