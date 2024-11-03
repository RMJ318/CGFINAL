//THIS FUNCTION WILL DETECT, AND STORE IN THE ARRAY colourArray, THE COLOUR THAT IS UNDER THE MBOT, AFTER IT IS TRIGGERED TO STOP BY THE LINE CHECKER

// decoder pins and LDR pin declared in main.ino

#define RED_LED 0;
#define GREEN_LED 1;
#define BLUE_LED 2;
#define IR 3
#define RGBWait 200 
#define LDRWait 10

int red = 0;
int green = 0;
int blue = 0;

float colourArray[] = {0,0,0}; //return to mBot movement
int colourCode = 0;
//RED == 1
//ORANGE == 2
//GREEN == 3
//BLUE == 4 
// PINK == 5

char colourStr[3][5] = {"R = ", "G = ", "B = "};

void setup() { //set each RGB pin to output mode
for(int c = 0;c<=2;c++) {
detect();
assignCode();
}

void shine_led(int i)
{
  // shines red/green/blue/IR if i is 0/1/2/3
  // 0 -> 0 0, 1 -> 0 1, etc
  digitalWrite(DECODE_PIN0, i / 2); 
  digitalWrite(DECODE_PIN1, i % 2);
}

void detect() {                        
for(int c = 0; c < 3; c++) { // for each colour LED
  shine_led(c); //turn ON selected LED
  delay(RGBWait);
  colourArray[c] = getAvgReading(5); //get ave reading of the colour the LDR is exposed to
  colourArray[c] = (colourArray[c] - blackArray[c])/(greyDiff[c])*255;
  shine_led(IR); //turn OFF selected LED
  delay(RGBWait);
 }
}

int assignCode(){
if (         (colourArray[0] >= (redArray[0] - 20) && colourArray <= (redArray[0] + 20)) && 
             (colourArray[1] >= (redArray[1] - 20) && colourArray <= (redArray[1] + 20)) &&
             (colourArray[2] >= (redArray[2] - 20) && colourArray <= (redArray[2] + 20)) ){
return 1; // RED
} else if (  (colourArray[0] >= (orangeArray[0] - 20) && colourArray <= (orangeArray[0] + 20)) && 
             (colourArray[1] >= (orangeArray[1] - 20) && colourArray <= (orangeArray[1] + 20)) &&
             (colourArray[2] >= (orangeArray[2] - 20) && colourArray <= (orangeArray[2] + 20)) ){
return 2; // ORANGE
} else if (  (colourArray[0] >= (greenArray[0] - 20) && colourArray <= (greenArray[0] + 20)) && 
             (colourArray[1] >= (greenArray[1] - 20) && colourArray <= (greenArray[1] + 20)) &&
             (colourArray[2] >= (greenArray[2] - 20) && colourArray <= (greenArray[2] + 20)) ){
return 3: // GREEN
} else if (  (colourArray[0] >= (blueArray[0] - 20) && colourArray <= (blueArray[0] + 20)) && 
             (colourArray[1] >= (blueArray[1] - 20) && colourArray <= (blueArray[1] + 20)) &&
             (colourArray[2] >= (blueArray[2] - 20) && colourArray <= (blueArray[2] + 20)) ){
return 4; // BLUE
} else if (  (colourArray[0] >= (pinkArray[0] - 20) && colourArray <= (pinkArray[0] + 20)) && 
             (colourArray[1] >= (pinkArray[1] - 20) && colourArray <= (pinkArray[1] + 20)) &&
             (colourArray[2] >= (pinkArray[2] - 20) && colourArray <= (pinkArray[2] + 20)) ){
return 5; // PINK
}
}

int getAvgReading(int times) {
  int reading;
  int total = 0;
  for(int i = 0; i < times; i++) {
    reading = analogRead(LDR);
    total = reading + total;
    delay(LDRWait);
  }
  return total / times;
}
