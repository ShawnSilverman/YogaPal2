import processing.serial.*;
Serial myPort;  // Create object from Serial class

Cell[][] grid;

// Number of columns and rows in the grid
int gridCols = 3;
int gridRows = 3;
int cols = 6;
int rows = 6;
//length and width of the squares
int rectSize;
int radius = 30;
int threshold = 400;      //red
int thresholdTwo = 600;   //green
//initialize color array
color colors[];
//initialize sensors array
int[][] pSensors;
int raw[];

int countOne = 0;
int countTwo = 0;
int countThree = 0;
int countFour = 0;
int countFive = 0;
int countSix = 0;
int countSeven = 0;
int countEight = 0;
int countNine = 0;

final int linefeed = 10;
final int maxSensors = cols * rows;
boolean madeContact = false;


void setup() {
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
  colors = new color[4]; /*size*/
  colors[0] = color(255, 0, 0); /*red*/
  colors[1] = color(0, 255, 0); /*green*/
  colors[2] = color(0, 0, 255); /*blue*/
  colors[3] = color(128, 0, 128); /*purple*/

  //draw the grid of cells with x columns and y rows
  grid = new Cell[gridCols][gridRows];
  for (int i = 0; i < gridCols; i++) {
    for (int j = 0; j < gridRows; j++) {
      if (gridCols == gridRows) {
        rectSize = round(height/gridRows);
      } else {
        rectSize = round(width/gridCols);
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
  colorAssign();
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
    x = cellX; 
    y = cellY; 
    w = cellW; 
    h = cellH; 
    r = radius;
  } 

  void display(color boxColor) {
    stroke(0);
    // Color calculated using sine wave
    fill(boxColor);
    rect(x, y, w, h, r);
  }
}

void colorAssign() {
  countOne = 0;
  countTwo = 0;
  countThree = 0;
  countFour = 0;
  countFive = 0;
  countSix = 0;
  countSeven = 0;
  countEight = 0;
  countNine = 0;
  
  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      pSensors[i][j] = raw[(j * cols) + i];
      //Left Top Square
      if (pSensors[0][0]>500) {
        countOne++;
      } if (pSensors[0][1]>500) {
        countOne++;
      } if ((pSensors[1][0]>500)) {
        countOne++;
      } if (pSensors[1][1]>500) {
        countOne++;
      }
      //Left Middle Square
      if (pSensors[0][2]>500) {
        countTwo++;
      } if (pSensors[1][2]>500) {
        countTwo++;
      } if (pSensors[0][3]>500) {
        countTwo++;
      } if(pSensors[1][3]>500) {
        countTwo++;
      }
      //Left Bottom Square
        if (pSensors[0][4]>500) {
        countThree++;
      } if (pSensors[0][5]>500) {
        countThree++;
      } if (pSensors[1][4]>500) {
        countThree++;
      } if (pSensors[1][5]>500) {
        countThree++;
      } 
      //Middle Top Square
      if (pSensors[2][0]>500) {
        countFour++;
      } if (pSensors[2][1]>500) {
        countFour++;
      } if (pSensors[3][0]>500) {
        countFour++;
      } if (pSensors[3][1]>500) {
        countFour++;
      } 
      //Middle Middle Square
      if (pSensors[2][2]>500) {
        countFive++;
      } if (pSensors[2][3]>500) {
        countFive++;
      } if (pSensors[3][2]>500) {
        countFive++;
      } if (pSensors[3][3]>500) {
        countFive++;
      } 
      //Middle Bottom Square
      if (pSensors[2][4]>500) {
        countSix++;
      } if (pSensors[2][5]>500) {
        countSix++;
      } if (pSensors[3][4]>500) {
        countSix++;
      } if (pSensors[3][5]>500) {
        countSix++;
      }
      //Right Top Square
      if (pSensors[4][0]>500) {
        countSeven++;
      } if (pSensors[4][1]>500) {
        countSeven++;
      } if (pSensors[5][0]>500) {
        countSeven++;
      } if (pSensors[5][1]>500) {
        countSeven++;
      } 
      //Right Middle Square
      if (pSensors[4][2]>500) {
        countEight++;
      } if (pSensors[4][3]>500) {
        countEight++;
      } if (pSensors[5][2]>500) {
        countEight++;
      } if (pSensors[5][3]>500) {
        countEight++;
      } 
      //Right Bottom Square
      if (pSensors[4][4]>500) {
        countNine++;
      } if (pSensors[4][5]>500) {
        countNine++;
      } if (pSensors[5][4]>500) {
        countNine++;
      } if (pSensors[5][5]>500) {
        countNine++;
      } 
    }
  }
  
  if (countOne > 71) {
    grid[0][0].display(colors[1]);
  } else if (countOne < 71) {
    grid[0][0].display(colors[2]);
  } if (countTwo > 71) {
    grid[0][1].display(colors[1]);
  } else if (countTwo < 71) {
    grid[0][1].display(colors[2]);
  } if (countThree > 71) {
    grid[0][2].display(colors[1]);
  } else if (countThree < 71) {
    grid[0][2].display(colors[2]);
  } if (countFour > 71) {
    grid[1][0].display(colors[1]);
  } else if (countFour < 71) {
    grid[1][0].display(colors[2]);
  } if (countFive > 71) {
    grid[1][1].display(colors[1]);
  } else if (countFive < 71) {
    grid[1][1].display(colors[2]);
  } if (countSix > 71) {
    grid[1][2].display(colors[1]);
  } else if (countSix < 71) {
    grid[1][2].display(colors[2]);
  } if (countSeven > 71) {
    grid[2][0].display(colors[1]);
  } else if (countSeven < 71) {
    grid[2][0].display(colors[2]);
  } if (countEight > 71) {
    grid[2][1].display(colors[1]);
  } else if (countEight < 71) {
    grid[2][1].display(colors[2]);
  } if (countNine > 71) {
    grid[2][2].display(colors[1]);
  } else if (countNine < 71) {
    grid[2][2].display(colors[2]);
  }
   println(countOne);
}