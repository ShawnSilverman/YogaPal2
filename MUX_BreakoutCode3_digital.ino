//Mux_Shield_DigitalIn_Example
//http://mayhewlabs.com/arduino-mux-shield

/*
This example shows how to read and store all pins as digital inputs into arrays and print the results over serial.
Switches should be connected from ground to the pin input.
Internal pull-up resistors are used on the inputs, so when a switch is depressed, the reading
changes from 1 to 0, but to correct this logic, the digitalRead function is corrected with '!' 
to actually store a 1 when a switch is depressed.

To simplify this code further, one might use nested for loops or function calls.
*/

//Give convenient names to the control pins
#define CONTROL0 5    
#define CONTROL1 4
#define CONTROL2 3
#define CONTROL3 2

//Create arrays for data from the the MUXs
//See the Arduino Array Reference: http://www.arduino.cc/en/Reference/Array
int mux0array[16];

void setup()
{
  //Set MUX control pins to output
  pinMode(CONTROL0, OUTPUT);
  pinMode(CONTROL1, OUTPUT);
  pinMode(CONTROL2, OUTPUT);
  pinMode(CONTROL3, OUTPUT);
  
  //Open the serial port at 28800 bps
  Serial.begin(9600);
  
  //Set analog pins to digital input  
  pinMode(14, INPUT);         
  pinMode(15, INPUT);
  pinMode(16, INPUT);
  
  //Turn on pullup resistors
  digitalWrite(14, HIGH);       
  digitalWrite(15, HIGH);
  digitalWrite(16, HIGH);
}
  

void loop()
{
  //This for loop is used to scroll through and store the 16 inputs on the FIRST multiplexer
  for (int i=0; i<16; i++)
  {
    //The following 4 commands set the correct logic for the control pins to select the desired input
    //See the Arduino Bitwise AND Reference: http://www.arduino.cc/en/Reference/BitwiseAnd
    //See the Aruino Bitshift Reference: http://www.arduino.cc/en/Reference/Bitshift
    digitalWrite(CONTROL0, (i&15)>>3); 
    digitalWrite(CONTROL1, (i&7)>>2);  
    digitalWrite(CONTROL2, (i&3)>>1);  
    digitalWrite(CONTROL3, (i&1));     
    
    //Read and store the input
    //Since internal pullup is on, the pin goes low on changing, so the value needs to be flipped from 0 to 1 (!)
    mux0array[i] = !digitalRead(14);
  }
  
  //The following lines are for printing out results of array0
  Serial.print("mux0array: ");
  for (int i=0; i<16; i++)
  {
    Serial.print(mux0array[i]);
    Serial.print("-");
  }
  Serial.println();  //line feed
}
