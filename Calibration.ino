#define RGBWait 200
#define LDRWait 10 
#define LDR {{1},{1}} //y3
//#define LED 13 idk where the check light indicator is

int ledArray[3][2] = {{0,0},{0,1},{1,0}}; // pin y0, y1, y2

int red = 0;
int green = 0;
int blue = 0;

float colourArray[] = {0,0,0];
float whiteArray[] = {0,0,0};
float blackArray[] = {0,0,0};
float redArray[] = {0,0,0};
float orangeArray[] = {0,0,0};
float greenArray[] = {0,0,0};
float blueArray[] = {0,0,0};
float pinkArray[] = {0,0,0};
float greyDiff[] = {0,0,0};

char colourStr[3][5] = {"R = ", "G = ", "B = "};

void calibration_setup(){
for(int c = 0;c<=2;c++){
pinMode(ledArray[c],OUTPUT);
}
//pinMode(LED,OUTPUT); //Check Indicator -- OFF during Calibration
//begin serial communication
Serial.begin(9600);
setBalance(); //calibration
storeColour();
//digitalWrite(LED, HIGH); //Check Indicator -- ON after Calibration
}

void setBalance(){
//set white balance
Serial.println("Put White Sample For Calibration ...");
delay(5000); 
digitalWrite(LED,LOW); //Check Indicator OFF during Calibration
for(int i = 0;i<=2;i++){
digitalWrite(ledArray[i],HIGH); //LED ON
delay(RGBWait);
whiteArray[i] = getAvgReading(5); //input values into array
digitalWrite(ledArray[i],LOW); //LED OFF
delay(RGBWait);
}

//set black balance
Serial.println("Put Black Sample For Calibration ...");
delay(5000);
for(int i = 0;i<=2;i++){
digitalWrite(ledArray[i],HIGH); //LED ON
delay(RGBWait);
blackArray[i] = getAvgReading(5); //input values into array
digitalWrite(ledArray[i],LOW); /LED OFF
delay(RGBWait);
  
greyDiff[i] = whiteArray[i] - blackArray[i];
}
}

void setColour(){
Serial.println("Put PINK Sample For Calibration ...");
delay(5000); 
for(int i = 0;i<=2;i++){
digitalWrite(ledArray[i],HIGH); //LED ON
delay(RGBWait);
colourArray[i] = getAvgReading(5); //input values into array
pinkArray[i] = (colourArray[i] - blackArray[c])/(greyDiff[i])*255;
digitalWrite(ledArray[i],LOW); /LED OFF
delay(RGBWait);
}

Serial.println("Put RED Sample For Calibration ...");
delay(5000); 
for(int i = 0;i<=2;i++){
digitalWrite(ledArray[i],HIGH); //LED ON
delay(RGBWait);
colourArray[i] = getAvgReading(5); //input values into array
redArray[i] = (colourArray[i] - blackArray[c])/(greyDiff[i])*255;
digitalWrite(ledArray[i],LOW); /LED OFF
delay(RGBWait);
}

Serial.println("Put ORANGE Sample For Calibration ...");
delay(5000); 
for(int i = 0;i<=2;i++){
digitalWrite(ledArray[i],HIGH); //LED ON
delay(RGBWait);
colourArray[i] = getAvgReading(5); //input values into array
orangeArray[i] = (colourArray[i] - blackArray[c])/(greyDiff[i])*255;
digitalWrite(ledArray[i],LOW); /LED OFF
delay(RGBWait);
}

Serial.println("Put GREEN Sample For Calibration ...");
delay(5000); 
for(int i = 0;i<=2;i++){
digitalWrite(ledArray[i],HIGH); //LED ON
delay(RGBWait);
colourArray[i] = getAvgReading(5); //input values into array
greenArray[i] = (colourArray[i] - blackArray[c])/(greyDiff[i])*255;
digitalWrite(ledArray[i],LOW); /LED OFF
delay(RGBWait);
}

Serial.println("Put BLUE Sample For Calibration ...");
delay(5000); 
for(int i = 0;i<=2;i++){
digitalWrite(ledArray[i],HIGH); //LED ON
delay(RGBWait);
blueArray[i] = getAvgReading(5); //input values into array
redArray[i] = (colourArray[i] - blackArray[c])/(greyDiff[i])*255;
digitalWrite(ledArray[i],LOW); /LED OFF
delay(RGBWait);
}
}

int getAvgReading(int times) {
int reading;
int total =0;
for(int i = 0;i < times;i++) {
  reading = analogRead(LDR);
  total = reading + total;
  delay(LDRWait);
  }return total/times;
}
