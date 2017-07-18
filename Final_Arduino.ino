//Shawn's Code
 
// The higher the number, the slower the timing.
int timer = 350;

// an array of pin numbers to which the analogs are attached
//MUST CHANGE THIS IF PIN COUNT CHANGES
int padPins[] = { 0, 1, 2, 3, 4, 5};
/*,               0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 
                  12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 
                  24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 
                  36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 
                  48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 
                  60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71*/ 

// the number of pins (i.e. the length of the array)
//MUST CHANGE THIS IF PIN COUNT CHANGES
const int pinCount = 6; 

int arrPads[pinCount];   

void setup() {
  //setup serial monitor
  Serial.begin(9600);
  // use a for loop to initialize each pin as an output:
  for (int i = 0; i < pinCount; i++) {
    pinMode(padPins[i], OUTPUT);
  }
}

void loop() {
//    arrPads[0] = analogRead(padPins[0]);
//    Serial.print(arrPads[0]);
    
      
  for (int i = 0; i < pinCount; i++) {
    arrPads[i] = analogRead(padPins[i]);
  //print out the value of each pad in the serial monitor
//    Serial.print("Reading ");
//    Serial.print(i);
//    Serial.print(": ");
//    Serial.println(arrPads[i]);
    Serial.print(arrPads[i]);
    if ((i) < (pinCount - 1))  {
      Serial.print(","); 
    } 
  }
  Serial.println();
  delay(timer);
}
