#define RGBWait 200
#define LDRWait 10 
//#define LED 13 idk where the check light indicator is


/*
float colourArray[] = {0,0,0};
float whiteArray[] = {0,0,0};
float blackArray[] = {0,0,0};
float greyDiff[] = {0,0,0};


//float referenceColour[5][3];
char *message[5] = {"Red", "Orange", "Green", "Blue", "Pink"};
//RED == 1
//ORANGE == 2
//GREEN == 3
//BLUE == 4 
// PINK == 5

void calibration_setup()
{
  setBalance(); //calibration
  // setColour(); //reading for each colour
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
    Serial.println("whiteArray:");
    Serial.println(whiteArray[0]);
    Serial.println(whiteArray[1]);
    Serial.println(whiteArray[2]);
    Serial.println("greyDiff:");
    Serial.println(greyDiff[0]);
    Serial.println(greyDiff[1]);
    Serial.println(greyDiff[2]);
    Serial.println("blackArray:");
    Serial.println(blackArray[0]);
    Serial.println(blackArray[1]);
    Serial.println(blackArray[2]);
}

/*
void setColour()
{
	for (int i = 0; i < 5; i++) {
    Serial.println(message[i]);
		delay(5000); 
		for(int j = 0; j < 3 ; j++) {
			shine_led(j); 
			delay(RGBWait);
			colourArray[j] = getAvgReading(5); 
			referenceColour[i][j] = (colourArray[j] - blackArray[j])/(greyDiff[j])*255;
			shine_led(IR);
			delay(RGBWait);
  }
		Serial.print("Colour Code for reference colour");
		Serial.println(i);
		
		for (int j = 0; j < 3; j++) {
			Serial.println(referenceColour[i][j]);
		}
	}
  Serial.println("whiteajdakeh");
  Serial.println((whiteArray[0] - blackArray[0])/(greyDiff[0])*255);
  Serial.println((whiteArray[1] - blackArray[1])/(greyDiff[1])*255);
  Serial.println((whiteArray[2] - blackArray[2])/(greyDiff[2])*255);
}

*/


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
