#define numRows 2
#define numCols 2
#define sensorPoints numRows*numCols

int rows[] = { 
  A0, A1};   
int cols[] = { 
  2,3};  
int incomingValues[36] = {
};   


void setup() {
  // set all rows and columns to INPUT (high impedance):
  for(int i=0; i<numRows; i++){
    pinMode(rows[i], INPUT);
  }
    for(int i=0; i<numCols; i++){
    pinMode(cols[i], INPUT);
  }
  Serial.begin(9600);
}

void loop() {
  for(int colCount=0; colCount<numCols; colCount++){
    pinMode(cols[colCount], OUTPUT);  // set as OUTPUT
    digitalWrite(cols[colCount], LOW);  // set LOW
    delay(100);
    
    for(int rowCount=0; rowCount<numRows; rowCount++){
      pinMode(rows[rowCount], INPUT_PULLUP);  // set as INPUT with PULLUP RESISTOR
      delay(1);
      incomingValues[ ( (colCount)*numRows) + (rowCount)] = analogRead(rows[rowCount]);  // read INPUT
      
      // set pin back to INPUT
      pinMode(rows[rowCount], INPUT);

    }// end rowCount

    pinMode(cols[colCount], INPUT);  // set back to INPUT!

  }// end colCount

  // Print the incoming values of the grid:
  for(int i=0; i<sensorPoints; i++){
    Serial.print(incomingValues[i]);
    if(i<sensorPoints-1) Serial.print(",");
  }
  Serial.println();
}













