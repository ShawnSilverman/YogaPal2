//Shawn's Code
//6 MUX Boards daisy chained
//Prints for Processing or a Table
//LED Strip

//initialize
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

int PIN = 5;



//array of pin locations
#define CONTROL2  2
#define CONTROL3  3
#define CONTROL4  4
#define CONTROL5  5

// The higher the number, the slower the timing.
int timer = 350;

// the number of pins (i.e. the length of the array)
//MUST CHANGE THIS IF PIN COUNT CHANGES
const int pinCount = 96;
const int cols = 6;
const int rows = 6;

//initialize pixels using the adafruit inclusion
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(pinCount, PIN, NEO_GRB + NEO_KHZ800);

int thresholdOne = 100;  /*red*/
int thresholdTwo = 700;  /*green*/

//initialize mux0array for length 16 corresponding to the 16 pins on the MUX board
int muxArray[pinCount];
int arrPads[pinCount];
int pSensDubArray[cols][rows];

void setup() {
  //Set all pins to output
  pinMode(CONTROL2, OUTPUT);
  pinMode(CONTROL3, OUTPUT);
  pinMode(CONTROL4, OUTPUT);
  pinMode(CONTROL5, OUTPUT);

  Serial.begin(9600);
}

int digitalWriteFunction(int i) {
  digitalWrite(CONTROL2, (i & 15) >> 3);
  digitalWrite(CONTROL3, (i & 7) >> 2);
  digitalWrite(CONTROL4, (i & 3) >> 1);
  digitalWrite(CONTROL5, (i & 1) >> 0);
}

void loop() {
  int analogPin = 0;

  //This for loop is used to scroll through and store the 16 inputs on the FIRST multiplexer
  for (int i = 0; i < 96; i++) {
    digitalWriteFunction(i);
    muxArray[i] = analogRead(analogPin);

    if (((i + 1) % 16) == 0) {
      analogPin++;
    }
  }

  //Set arrPads[i] to be muxArray[i]
  for (int i = 0; i < pinCount; i++) {
    arrPads[i] = muxArray[i];
    if (muxArray[i] > thresholdOne) {
      arrPads[i] = muxArray[i];
    }
    else {
      arrPads[i] = 0;
    }
  }
  
//  printFunctionTable();
  printFunctionProcessing();
  delay(300);
}

//prints the layout for Processing to read it
void printFunctionProcessing() {
  for (int i = 0; i < rows*cols; i++) {
    Serial.print(arrPads[i]);
    if ((i) < (rows*cols - 1))  {
      Serial.print(",");
    }
  }
  Serial.println();
}

//prints a table rows by columns
void printFunctionTable() {
  printHeadOrFoot(0);
  int count = 0;

  for (int j = 0; j < rows; j++) {
    for (int i = 0; i < cols; i++) {
      pSensDubArray[i][j] = arrPads[count];
      Serial.print(pSensDubArray[i][j]);
      count++;
      Serial.print("\t");
    }
    Serial.println("");
  }
  printHeadOrFoot(1);
}

//Prints the header or footer depending on the input
void printHeadOrFoot(int check) {
  if (check == 0) {
    //prints ===
    for (int i = 0; i < cols*7; i++) {
      Serial.print("=");
    }
    Serial.println("");
    //prints col numbers
    for (int i = 0; i < cols; i++) {
      Serial.print(i);
      Serial.print("\t");
    }
    Serial.println("");
    //prints ===
    for (int i = 0; i < cols*7; i++) {
      Serial.print("=");
    }
    Serial.println("");
  }

  if (check == 1) {
    //prints ===
    for (int i = 0; i < cols; i++) {
      Serial.print("--");
      Serial.print("\t");
    }
    Serial.println("");
    Serial.println("");
  }
}
