//THIS FUNCTION WILL DETECT, AND STORE IN THE ARRAY colourArray, THE COLOUR THAT IS UNDER THE MBOT, AFTER IT IS TRIGGERED TO STOP BY THE LINE CHECKER

// decoder pins and LDR pin declared in main.ino


#define RGBWait 200 
#define LDRWait 10
#define RANGE 30
float colourArray[] = {0,0,0};
float whiteArray[] = {255,255,255};
float blackArray[] = {520,533,672};
float greyDiff[] = {172,154,41};
float referenceColour[5][3] = {{60, 62, 223}, {130, 79, 227}, {194, 139, 59}, {181, 224, 55}, {203, 208, 223}};

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

int detectColour() {
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

int assignCode() {
  float euclideanDistance[6] = {1000}; // temporary value, all euclidean distance values will be lower than this
  float minimum = euclideanDistance[0];
  int minPosition = 0;
  
  // Serial.println(colourArray[0]);
  // Serial.println(colourArray[1]);
  // Serial.println(colourArray[2]);
  for (long i = 1; i < 6; i++) 
  {

    euclideanDistance[i] = sqrt(sq(colourArray[0] - referenceColour[i-1][0]) + 
                                sq(colourArray[1] - referenceColour[i-1][1]) + 
                                sq(colourArray[2] - referenceColour[i-1][2]));
  }
  euclideanDistance[0] = sqrt(sq(colourArray[0] - 255) + 
                              sq(colourArray[1] - 255) + 
                              sq(colourArray[2] - 255));

  for (int i = 0; i < 6; i++) {
    // Serial.println("Euclidean Distance: ");
    // Serial.println(euclideanDistance[i]);
    if (euclideanDistance[i] < minimum) 
    {
      // get colour with closest distance
      minimum = euclideanDistance[i];
      minPosition = i;
    }
  }
  return minPosition;
}

