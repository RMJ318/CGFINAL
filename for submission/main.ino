/**
* this the main function folder
*/

#include "MeOrion.h"

// LED control pins, connected to 2 - 4 Decoder
// inputs too
#define DECODE_PIN0 A0
#define DECODE_PIN1 A1
#define LDR_IN A2
#define IR_IN A3
#define ULTRASONIC 12
#define TIMEOUT 1600
#define SPEED_OF_SOUND 343

#define RED_LED 0
#define GREEN_LED 1
#define BLUE_LED 2
#define IR 3
#define SAMPLES 5


MeDCMotor motor1(M1);  // Motor 1 connected to port M1
MeDCMotor motor2(M2);  // Motor 2 connected to port M2
MeLineFollower lineFinder(PORT_2); // Linefinder connected to port 2
MeBuzzer buzzer;

float baseline_left = 12;
float baseline_right = 17; // used by move forward function

//function prototypes

// movement
float ultrasound_dist();
int read_ave(int pin, int k);
float offset();
float ir_dist();
void stopMotor();
void moveForward();
void turnRight();
void turnLeft();
void uTurn();
void doubleLeftTurn();
void doubleRightTurn();

// colour detection
// void calibration_setup(); // no longer needed as colours have been hardcoded
int detectColour();
int assignCode();
void shine_led(int i);
void detect();
void setBalance();
void setColour();
int getAvgReading(int times);

void setup()
{
  pinMode(DECODE_PIN0, OUTPUT);
  pinMode(DECODE_PIN1, OUTPUT);
  pinMode(LDR_IN, INPUT);
  pinMode(IR_IN, INPUT);
  shine_led(IR);
  Serial.begin(9600);
  // calibration_setup();
}

void loop()
{
  int sensorState = lineFinder.readSensors();
  Serial.println(sensorState);
  if (sensorState == 0) //line detected
  {
    stopMotor();
    moveBackabit();
    int colour = detectColour();
    Serial.println("detectColour output:");
    switch (colour) 
    {
      case 1: 
        Serial.println("Red");
        Serial.println("Turn Left");
        turnLeft();
        break;
      case 2:  
        Serial.println("Orange");
        Serial.println("uTurn");
        uTurn();
        break;
      case 3:  
        Serial.println("Green");
        Serial.println("Right Turn");
        turnRight();
        break;
      case 4:  
        Serial.println("Blue");
        Serial.println("dTurn Right");
        doubleRightTurn();
        break;
      case 5:  
        Serial.println("Pink");
        Serial.println("dLeft Turn");
        doubleLeftTurn();
        break;
      default:
        Serial.println("Stop");
        stopMotor();
        celebrate();
    }
    delay(50);
  }
  else
  {
    delay(50);
    moveForward();
  }
   //delay 50ms
}

