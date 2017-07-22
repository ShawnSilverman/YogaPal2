//Shawn's Code
//3 MUX Boards
//Prints for Processing
//LED Strip

//initialize
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

//Give convenient names to the control pins
#define CONTROL2    2
#define CONTROL3    3
#define CONTROL4    4
#define CONTROL5    5
#define CONTROL6    6
#define CONTROL7    7
#define CONTROL8    8
#define CONTROL9    9
#define CONTROL10   10
#define CONTROL11   11
#define CONTROL12   12
#define CONTROL13   13

//initialize pin for LED's and the number of them you want to work with
int PIN = A3;
const int pinCount = 48;  //The number of pins (i.e. the length of the array)
const int pSensNum = 8;
int count = 0;
int numPixel = pinCount;

int thresholdOne = 620;  /*red*/
int thresholdTwo = 700;  /*green*/

//initialize pixels using the adafruit inclusion
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(numPixel, PIN, NEO_GRB + NEO_KHZ800);

int color = (100, 0, 0 );

int sum     = 0;

int timer = 100;          // The higher the number, the slower the timing.
int muxArray[48];         //initialize muxArray corresponding
int arrPads[pinCount];

int senLocs[pSensNum][2] = {
  {12, 16}, //channel 0
  {16, 20}, //channel 1
  {20, 24}, //channel 2
  {24, 28}, //channel 3
  {9, 12}, //channel 4
  {6, 9}, //channel 5
  {3, 6}, //channel 6
  {0, 3}, //channel 7
};

void setup() {
  pixels.setBrightness(50);
  pixels.begin();
  pixels.show();

  //Set MUX control pins to output
  pinMode(CONTROL2, OUTPUT);
  pinMode(CONTROL3, OUTPUT);
  pinMode(CONTROL4, OUTPUT);
  pinMode(CONTROL5, OUTPUT);
  pinMode(CONTROL6, OUTPUT);
  pinMode(CONTROL7, OUTPUT);
  pinMode(CONTROL8, OUTPUT);
  pinMode(CONTROL9, OUTPUT);
  pinMode(CONTROL10, OUTPUT);
  pinMode(CONTROL11, OUTPUT);
  pinMode(CONTROL12, OUTPUT);
  pinMode(CONTROL13, OUTPUT);

  Serial.begin(9600);
}


/*binary function definition*/
//Checks each of the 48 pins from the 3 MUX chips and writes the values to the analogs
//This for loop is used to scroll through and store the 16 inputs on each multiplexer
void checkBinaryPins() {
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
    muxArray[i] = analogRead(1);
  }
  for (int i = 32; i < 48; i++)
  {
    digitalWrite(CONTROL10, (i & 15) >> 3);
    digitalWrite(CONTROL11, (i & 7) >> 2);
    digitalWrite(CONTROL12, (i & 3) >> 1);
    digitalWrite(CONTROL13, (i & 1) >> 0);
    muxArray[i] = analogRead(2);
  }
}

/*Loop*/
void loop() {
  sum = 0;
  count = 0;

  //runs the checkBinaryPins function
  checkBinaryPins();

  for (int i = 0; i < pSensNum; i++) {
    if (muxArray[i] > thresholdOne) {
      arrPads[i] = muxArray[i];
      count++;
    }
    else {
      arrPads[i] = 0;
    }

    sum = sum + arrPads[i];
    Serial.print(muxArray[i]);
    if ((i) < (pSensNum - 1)) {
      Serial.print(",");
    }
  }
  Serial.println();
  Serial.print("sum = ");
  Serial.print(sum);
  Serial.println();
  Serial.print("count = ");
  Serial.print(count);

  thresholdCheck();

  /*For threshold pressure sensor checks*/
  //    if (arrPads[i] > thresholdTwo) {
  //      pixels.setPixelColor(i, 0, 255, 0);   /*green*/
  //      pixels.show();
  //    }
  //    else if (arrPads[i] > thresholdOne) {
  //      pixels.setPixelColor(i, 255, 0, 0);   /*red*/
  //      pixels.show();
  //
  //    }
  //    else {
  //      pixels.setPixelColor(i, 0, 0, 255);   /*blue*/
  //      pixels.show();
  //    }
  //  }

  Serial.println();
  delay(timer);
}


/*Pixel Color function definition*/
//sets the pixel color based on inputs
void pixelColor( String color, int str, int fin ) {
  for ( int l = str; l < fin; l++) {
    if ( color == "Red" ) {
      redLED( l );
    } else if ( color == "Green") {
      grnLED( l );
    } else if ( color == "Blue") {
      bluLED( l );
    } else if ( color == "Purple") {
      purLED( l );
    }
    delay(10);
  }
}


/*Threshold check to set colors*/
void thresholdCheck() {
  for (int k = 0; k < pSensNum; k ++) {
    if ( count >=  5) {
      //set to Purple
      for (int z = 0; z < pSensNum; z ++) {
        pixelColor( "Purple", senLocs[z][0], senLocs[z][1] );
      }
      Serial.println();
      Serial.print("sum = ");
      Serial.print(sum);
      Serial.println();
      Serial.print("count = ");
      Serial.print(count);
    }
    else if (arrPads[k] > thresholdOne) {
      //set to Green
      pixelColor( "Green", senLocs[k][0], senLocs[k][1] );
    }
    else if ( (arrPads[k] < thresholdOne) && (sum > thresholdOne) ) {
      //set to Red
      pixelColor( "Red", senLocs[k][0], senLocs[k][1] );
    }
    else if ( (arrPads[k] < thresholdOne) && (sum < thresholdOne) ) {
      //set to Blue
      pixelColor( "Blue", senLocs[k][0], senLocs[k][1] );
    }
    else {
      //set to Blue
      pixelColor( "Blue", senLocs[k][0], senLocs[k][1] );
    }
  }
}


/*Color changing functions*/
//turns LEDs red
void redLED( int x ) {
  //Red   = 255, 0, 0
  pixels.setPixelColor( x, pixels.Color( 255, 0, 0 ));
  pixels.show();
}

//turns LEDs green
void grnLED( int x ) {
  //Green = 0, 255, 0
  pixels.setPixelColor( x, pixels.Color( 0, 255, 0 ));
  pixels.show();
}

//turns LEDs blue
void bluLED( int x ) {
  //Blue  = 0, 0, 255
  pixels.setPixelColor( x, pixels.Color( 0, 0, 255 ));
  pixels.show();
}

//turns LEDs Purple
void purLED( int x ) {
  //Purple  = 75, 0, 130
  pixels.setPixelColor( x, pixels.Color( 75, 0, 130 ));
  pixels.show();
}

