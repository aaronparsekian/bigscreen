//big screens
//nyu itp fall 2016
//by lisa jamhoury, aaron parsekian
//processing 2.2.1
//done on a macbook pro os sierra
//october 2016
//based on code from tom arduino.cc
//https://www.arduino.cc/en/Tutorial/Graph
//and parsing info from
//https://www.processing.org/reference/split_.html

// Graphing sketch


// This program takes ASCII-encoded strings
// from the serial port at 9600 baud and graphs them. It expects values in the
// range 0 to 1023, followed by a newline, or newline and carriage return

// Created 20 Apr 2005
// Updated 24 Nov 2015
// by Tom Igoe
// This example code is in the public domain.

import processing.serial.*;

Serial myPort;        // The serial port
int xPos = 1;         // horizontal position of the graph
float inByte = 0;

void setup () {
  // set the window size:
  size(400, 300);

  // List all the available serial ports
  // if using Processing 2.1 or later, use Serial.printArray()
  println(Serial.list());

  // I know that the first port in the serial list on my mac
  // is always my  Arduino, so I open Serial.list()[0].
  // Open whatever port is the one you're using.
  myPort = new Serial(this, Serial.list()[3], 115200);

  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');

  // set inital background:
  background(0);
}
void draw () {
  // draw the line:
  stroke(127, 34, 255);
  line(xPos, height, xPos, height - inByte);

  // at the edge of the screen, go back to the beginning:
  if (xPos >= width) {
    xPos = 0;
    background(0);
  } else {
    // increment the horizontal position:
    xPos++;
  }
}


void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');

  if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);

    float[] numbers = float(split(inString, ','));
    
    for (int i = 0; i < numbers.length; i++) {
      //numbers[i] = float(numbers[i]);
      if (i == 0) {
        print("x: ");
      } else if (i == 1) {
        print("y: ");
      } else if (i == 2) {
        print("z: ");
      }
      println(numbers[i]);
    }

    // convert to an int and map to the screen height:
    //inByte = float(inString);
    //println(inByte);
    //inByte = map(inByte, 0, 1023, 0, height);
  }
}

