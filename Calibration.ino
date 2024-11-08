#define RGBWait 200
#define LDRWait 10 
//#define LED 13 idk where the check light indicator is

float colourArray[] = {0,0,0};
float whiteArray[] = {0,0,0};
float blackArray[] = {0,0,0};
float greyDiff[] = {0,0,0};
float referenceColours[3][5];
//RED == 1
//ORANGE == 2
//GREEN == 3
//BLUE == 4 
// PINK == 5

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
	for (int i = 0; i < 5; i++) {
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
		
		for (int i = 0; i < 3; i++) {
			Serial.println(referenceColour[j][i]);
		}
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
