
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
for(int c = 0; c < 3; c++) {
  shine_led(c); 
  delay(RGBWait);
  colourArray[c] = getAvgReading(5);
  colourArray[c] = (colourArray[c] - blackArray[c])/(greyDiff[c])*255;
  shine_led(IR); 
  delay(RGBWait);
 }
}

int assignCode() {
  float euclideanDistance = sqrt(referenceColour[i][0]*referenceColour //EDITING HALFWAY LOL
  
}


return 0;
}