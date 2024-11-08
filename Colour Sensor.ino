//THIS FUNCTION WILL DETECT, AND STORE IN THE ARRAY colourArray, THE COLOUR THAT IS UNDER THE MBOT, AFTER IT IS TRIGGERED TO STOP BY THE LINE CHECKER

// decoder pins and LDR pin declared in main.ino


#define RGBWait 200 
#define LDRWait 10

int colourCode = 0;
//RED == 1
//ORANGE == 2
//GREEN == 3
//BLUE == 4 
// PINK == 5


void shine_led(int i)
{
  // shines red/green/blue/IR if i is 0/1/2/3
  // 0 -> 0 0, 1 -> 0 1, etc
  digitalWrite(DECODE_PIN0, i / 2); 
  digitalWrite(DECODE_PIN1, i % 2);
}

int detectColour_2() {
detect();
return assignCode();
}

void detect() {                        
for(int c = 0; c < 3; c++) { // for each colour LED
  // Serial.println("LED ON");
  shine_led(c); //turn ON selected LED
  delay(RGBWait);
  colourArray[c] = getAvgReading(5); //get ave reading of the colour the LDR is exposed to
  colourArray[c] = (colourArray[c] - blackArray[c])/(greyDiff[c])*255;
  // Serial.println("LED OFF");
  shine_led(IR); //turn OFF selected LED
  delay(RGBWait);
 }
}

int assignCode(){
  for (int i = 0; i < 3; i++)
  {
    Serial.println(colourArray[i]);
  }
  if ((colourArray[0] >= (redArray[0] - 20) && colourArray[0] <= (redArray[0] + 20)) && 
      (colourArray[1] >= (redArray[1] - 20) && colourArray[1] <= (redArray[1] + 20)) &&
      (colourArray[2] >= (redArray[2] - 20) && colourArray[2] <= (redArray[2] + 20)))
      {
        return 1; // RED
      }
  if ((colourArray[0] >= (orangeArray[0] - 20) && colourArray[0] <= (orangeArray[0] + 20)) && 
      (colourArray[1] >= (orangeArray[1] - 20) && colourArray[1] <= (orangeArray[1] + 20)) &&
      (colourArray[2] >= (orangeArray[2] - 20) && colourArray[2] <= (orangeArray[2] + 20)))
      {
        return 2; // ORANGE
      } 
  if ((colourArray[0] >= (greenArray[0] - 20) && colourArray[0] <= (greenArray[0] + 20)) && 
      (colourArray[1] >= (greenArray[1] - 20) && colourArray[1] <= (greenArray[1] + 20)) &&
      (colourArray[2] >= (greenArray[2] - 20) && colourArray[2] <= (greenArray[2] + 20)))
      {
        return 3; // GREEN
      } 
  if ((colourArray[0] >= (blueArray[0] - 20) && colourArray[0] <= (blueArray[0] + 20)) && 
      (colourArray[1] >= (blueArray[1] - 20) && colourArray[1] <= (blueArray[1] + 20)) &&
      (colourArray[2] >= (blueArray[2] - 20) && colourArray[2] <= (blueArray[2] + 20)))
      {
        return 4; // BLUE
      } 
  if ((colourArray[0] >= (pinkArray[0] - 20) && colourArray[0] <= (pinkArray[0] + 20)) && 
      (colourArray[1] >= (pinkArray[1] - 20) && colourArray[1] <= (pinkArray[1] + 20)) &&
      (colourArray[2] >= (pinkArray[2] - 20) && colourArray[2] <= (pinkArray[2] + 20)))
      {
       return 5; // PINK
      }
return 0;
}

