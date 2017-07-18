import processing.serial.*;
Serial myPort;  // Create object from Serial class

Cell[][] grid;

// Number of columns and rows in the grid
int cols = 12;
int rows = 6;
//length and width of the squares
int rectSize;
int radius = 30;
int threshold = 400;
int thresholdTwo = 500;
//initialize color array
color colors[];
//initialize sensors array
int[][] pSensors;
int raw[];


final int linefeed = 10;
final int maxSensors = cols * rows;
boolean madeContact = false;


void setup() {
  // I know that the first port in the serial list on my mac
  // is Serial.list()[0].
  String portName = Serial.list()[3];
  myPort = new Serial(this, portName, 9600);
  myPort.bufferUntil(linefeed);
  
  //the length of sensors array is columns times rows
  pSensors = new int[cols][rows];
  raw = new int[maxSensors];

  size(1400, 800);
  background(0);
  surface.setResizable(true);

  //fill in all 4 colors rgb()
  colors = new color[4]; /*size*/ colors[0] = color(255, 0, 0); /*red*/ colors[1] = color(0, 255, 0); /*green*/ colors[2] = color(0, 0, 255); /*blue*/ colors[3] = color(128, 0, 128); /*purple*/

  //draw the grid of cells with x columns and y rows
  grid = new Cell[cols][rows];
  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      if (cols == rows) {
        rectSize = round(height/rows);
      } else {
        rectSize = round(width/cols);
      }
      // Initialize each object
      grid[i][j] = new Cell(i*rectSize, j*rectSize, rectSize, rectSize, radius);
    }
  }
}

void draw() {
  if (madeContact==false) {
    //start handshake w/controller
    myPort.write('\r');
  }
  // The counter variables i and j are also the column and row numbers and 
  // are used as arguments to the constructor for each object in the grid.  
  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      grid[i][j].display(colors[2]);
      if (pSensors[i][j] > thresholdTwo){
        grid[i][j].display(colors[1]);
      }
      else if (pSensors[i][j] > threshold){
        grid[i][j].display(colors[0]);
      }
    }
  }
}

void serialEvent(Serial myPort) {
  madeContact = true;
  String rawInput = myPort.readStringUntil(linefeed);

  if (rawInput != null) {
    rawInput = trim(rawInput);

    int[] sensors = int(split(rawInput, ','));

    for (int i=0; i<sensors.length; i++) {
      raw[i] = sensors[i];
    }
    
    //convert the single array rows[] into the double array pSensors[]
    for (int j = 0; j < rows; j++) {
      for (int i = 0; i < cols; i++) {
        pSensors[i][j] = raw[(j * cols) + i];
      }
    }
    
    //print in the serial monitor the reading from each sensors
    for (int i = 0; i < sensors.length; i++) {
      print(sensors[i]);
      print(",");
    }
    delay(100);
    println("");
  }
  myPort.write('\r');
}

// A Cell object
class Cell {
  // A cell object knows about its location in the grid 
  // as well as its size with the variables x,y,w,h,r
  float x, y;   // x,y location
  float w, h;   // width and height
  float r;      // pixel radius of squares corners

  // Cell Constructor
  Cell(float cellX, float cellY, float cellW, float cellH, float radius) {
    x = cellX; y = cellY; w = cellW; h = cellH; r = radius;
  } 

  void display(color boxColor) {
    stroke(0);
    // Color calculated using sine wave
    fill(boxColor);
    rect(x, y, w, h, r);
  }
}