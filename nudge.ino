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
    see_colour();
  }
  else
  {
    move_forward();
    nudge();
  }
  //delay(10); bot might take too long figuring out everything above to wait
}
