#define RGBWait 200
#define LDRWait 10 
//#define LED 13 idk where the check light indicator is

float colourArray[] = {0,0,0};
float whiteArray[] = {0,0,0};
float blackArray[] = {0,0,0};
float redArray[] = {0,0,0};
float orangeArray[] = {0,0,0};
float greenArray[] = {0,0,0};
float blueArray[] = {0,0,0};
float pinkArray[] = {0,0,0};
float greyDiff[] = {0,0,0};

char colourStr[3][5] = {"R = ", "G = ", "B = "};



void calibration_setup()
{
  setBalance(); //calibration
  setColour(); //reading for each colour
}

void setBalance() 
{
  Serial.println("Put White Sample For Calibration ...");
  delay(5000); 
	
  for(int i = 0; i<=2 ;i++) {
    shine_led(i); //turn ON selected LED
    delay(RGBWait);
    whiteArray[i] = getAvgReading(5);
    shine_led(IR); //turn OFF selected LED
    delay(RGBWait);
 }

  Serial.println("Put Black Sample For Calibration ...");
  delay(5000);
	
  for(int i = 0;i<=2;i++) {
    shine_led(i); //turn ON selected LED
    delay(RGBWait);
    blackArray[i] = getAvgReading(5); 
    shine_led(IR); //turn OFF selected LED
    delay(RGBWait);
    greyDiff[i] = whiteArray[i] - blackArray[i];
   }
}

void setColour()
{
  Serial.println("Put PINK Sample For Calibration ...");
  delay(5000); 
  for(int i = 0; i <= 2;i++) {
    shine_led(i); //turn ON selected LED
    delay(RGBWait);
    colourArray[i] = getAvgReading(5); //input values into array
    pinkArray[i] = (colourArray[i] - blackArray[i])/(greyDiff[i])*255;
    shine_led(IR); //turn OFF selected LED
    delay(RGBWait);
  }

  Serial.println("Pink array:");
  for (int i = 0; i < 3; i++)
  {
    Serial.println(pinkArray[i]);
  }

  Serial.println("Put RED Sample For Calibration ...");
  delay(5000); 
  for(int i = 0;i<=2;i++) {
    shine_led(i); //turn ON selected LED
    delay(RGBWait);
    colourArray[i] = getAvgReading(5); 
    redArray[i] = (colourArray[i] - blackArray[i])/(greyDiff[i])*255;
    shine_led(IR); //turn OFF selected LED
    delay(RGBWait);
  }

  Serial.println("Red array:");
  for (int i = 0; i < 3; i++)
  {
    Serial.println(redArray[i]);
  }

  Serial.println("Put ORANGE Sample For Calibration ...");
  delay(5000); 
    for(int i = 0; i<= 2; i++) {
      shine_led(i); //turn ON selected LED
      delay(RGBWait);
      colourArray[i] = getAvgReading(5); 
      orangeArray[i] = (colourArray[i] - blackArray[i])/(greyDiff[i])*255;
      shine_led(IR); //turn OFF selected LED
      delay(RGBWait);
  }

  Serial.println("Orange array:");
  for (int i = 0; i < 3; i++)
  {
    Serial.println(orangeArray[i]);
  }

  Serial.println("Put GREEN Sample For Calibration ...");
  delay(5000); 
  for(int i = 0;i<=2;i++) {
    shine_led(i); //turn ON selected LED
    delay(RGBWait);
    colourArray[i] = getAvgReading(5); 
    greenArray[i] = (colourArray[i] - blackArray[i])/(greyDiff[i])*255;
    shine_led(IR); //turn OFF selected LED
    delay(RGBWait);
    }

  Serial.println("Green array:");
  for (int i = 0; i < 3; i++)
  {
    Serial.println(greenArray[i]);
  }

  Serial.println("Put BLUE Sample For Calibration ...");
  delay(5000); 
  for(int i = 0;i<=2;i++) {
    shine_led(i); //turn ON selected LED
    delay(RGBWait);
    colourArray[i] = getAvgReading(5); 
    blueArray[i] = (colourArray[i] - blackArray[i])/(greyDiff[i])*255;
    shine_led(IR); //turn OFF selected LED
    delay(RGBWait);
  }

  Serial.println("Blue array:");
  for (int i = 0; i < 3; i++)
  {
    Serial.println(blueArray[i]);
  }
}

int getAvgReading(int times) {
  int reading;
  int total = 0;
  for(int i = 0; i < times; i++) {
    reading = analogRead(LDR_IN);
    total = reading + total;
    delay(LDRWait);
  }
	return total/times;
}
