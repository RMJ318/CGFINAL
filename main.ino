/**
* this the main function folder
*/

#include "MeOrion.h"

// LED control pins, connected to 2 - 4 Decoder
#define DECODE_PIN0 = A0;
#define DECODE_PIN1 = A1;

MeLineFollower lineFinder(PORT_2);

// input
#define LDR_IN = A2;
#define IR_IN = A3;


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
    // see colour
  }
  else
  {
    move_forward();
  }
  //delay(10); bot might take too long figuring out everything above to wait
}
