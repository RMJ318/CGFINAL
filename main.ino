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

float baseline_left;
float baseline_right; // used by move forward function

void setup()
{
  pinMode(DECODE_PIN0, OUTPUT);
  pinMode(DECODE_PIN1, OUTPUT);
  pinMode(LDR_IN, INPUT);
  pinMode(IR_IN, INPUT);
  baseline_left = ultrasound_dist();
  baseline_right = ir_dist();
  calibration_setup();
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
    int colour = detectColour();
    switch (colour) {
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
  else
  {
    moveForward();
    delay(50); //delay 50ms
  }
}
