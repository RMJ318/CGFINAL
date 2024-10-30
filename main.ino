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

MeDCMotor motor1(M1);
MeDCMotor motor2(M2);
MeLineFollower lineFinder(PORT_2);

void setup()
{
  pinMode(DECODE_PIN0, OUTPUT);
  pinMode(DECODE_PIN1, OUTPUT);
  pinMode(LDR_IN, INPUT);
  pinMode(IR_IN, INPUT);
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
    // see colour
  }
  else
  {
    move_forward();
    nudge();
  }
  //delay(10); bot might take too long figuring out everything above to wait
}
