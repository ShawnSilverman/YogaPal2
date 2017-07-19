//Shawn's Code

//Give convenient names to the control pins
#define CONTROL2 2
#define CONTROL3 3
#define CONTROL4 4
#define CONTROL5 5
#define CONTROL6 6
#define CONTROL7 7
#define CONTROL8 8
#define CONTROL9 9

// The higher the number, the slower the timing.
int timer = 350;
int pinArray[] = {2, 3, 4, 5, 6, 7, 8, 9};

// the number of pins (i.e. the length of the array)
//MUST CHANGE THIS IF PIN COUNT CHANGES
const int pinCount = 16; 

//initialize mux0array for length 16 corresponding to the 16 pins on the MUX board
int muxArray[32];

int arrPads[pinCount];   

void setup() {
  //Set MUX control pins to output
  pinMode(CONTROL2, OUTPUT);
  pinMode(CONTROL3, OUTPUT);
  pinMode(CONTROL4, OUTPUT);
  pinMode(CONTROL5, OUTPUT);
  pinMode(CONTROL6, OUTPUT);
  pinMode(CONTROL7, OUTPUT);
  pinMode(CONTROL8, OUTPUT);
  pinMode(CONTROL9, OUTPUT);

//  for (int i = 0; i < 8; i++) {
//    pinMode(pinArray[i], OUTPUT);
//  }

  //setup serial monitor
  Serial.begin(9600);
}

void loop() {
  //This for loop is used to scroll through and store the 16 inputs on the FIRST multiplexer
  for (int i = 0; i < 16; i++)
  {
    digitalWrite(CONTROL2, (i & 15) >> 3);
    digitalWrite(CONTROL3, (i & 7) >> 2);
    digitalWrite(CONTROL4, (i & 3) >> 1);
    digitalWrite(CONTROL5, (i & 1) >> 0);
    muxArray[i] = analogRead(0);
  }
  for (int i = 16; i < 32; i++)
  {
    digitalWrite(CONTROL6, (i & 15) >> 3);
    digitalWrite(CONTROL7, (i & 7) >> 2);
    digitalWrite(CONTROL8, (i & 3) >> 1);
    digitalWrite(CONTROL9, (i & 1) >> 0);

    //Read and store the input value at a location in the array
    muxArray[i] = analogRead(1);
  }
  
  for (int i = 0; i < 16; i++) {
    arrPads[i] = muxArray[i];
  //print out the value of each pad in the serial monitor
    Serial.print(arrPads[i]);
    if ((i) < (16 - 1))  {
      Serial.print(","); 
    } 
  }
  Serial.print(","); 
  for (int i = 16; i < 32; i++) {
    arrPads[i] = muxArray[i];
  //print out the value of each pad in the serial monitor
    Serial.print(arrPads[i]);
    if ((i) < (32 - 1))  {
      Serial.print(","); 
    } 
  }
  Serial.println();
  delay(timer);
}
