////////////Polar TX/////////
///////////Big Screens 2016 Aaron Parsekian////////////////
///////////////////////////
//////915MHz///////
//Antenna is 3.07" (3-1/16")  / 7.8cm

/*
  This sketch demonstrates a simple wireless hub
  listening for sensor packets from other nodes on this network.
  To make parsing packets easier, data is sent using the C++ struct.
  This allows both sender and receiver to read and write to the packet
  using the familiar object-dot-variable syntax.

  See the "wiring_rfm69.png" for how to hookup the circuit.

  To complete the example, run the "sensor_send.ino" sketch,
  or the "sensor_send_lowpower.ino" sketch
  on another Arduino with an RFm69 connected

  Be sure you have downloaded and installed the library used here:

    RFm69 Library: https://github.com/lowpowerlab/rfm69

  Created 24 March 2015
  By Andy Sigler

*/

#include <RFM69.h>
#include <SPI.h> // the RFM69 library uses SPI

/* for Feather 32u4 */
#define IS_RFM69HCW   true
#define RFM69_CS      8
#define RFM69_IRQ     7
#define RFM69_IRQN    4  // Pin 7 is IRQ 4!
#define RFM69_RST     4

#define myFrequency RF69_915MHZ // or RF69_433MHZ (check your radio)
RFM69 radio = RFM69(RFM69_CS, RFM69_IRQ, IS_RFM69HCW, RFM69_IRQN);

int myNetwork = 113; // radios must share the same network (0-255)
int myID = 8; // radios should be given unique ID's (0-254, 255 = BROADCAST)


int hubID = 7; // the receiver for all sensor nodes in this example

// instead of sending a string, we can send a struct
// this struct must be shared between all nodes
typedef struct {
  int sensor0;
  int sensor1;
  int sensor2;
  int sensor3;
} Packet;

///////////////////////////
int heartPin = 6;
int ledPin = 13;
int heartBeat = 0;

///////////////////////////

void setup() {


  // setup the radio
  radio.initialize(myFrequency, myID, myNetwork);

  // this example only uses Serial inside setup()
  // because Narcoleptic will stop Serial once used
 // Serial.begin(9600);
 // Serial.println("\nRADIO INITIALIZED");
 // Serial.println("Sending sensor values");

  ///////////////////////////

  pinMode(heartPin, INPUT);
  pinMode(ledPin, OUTPUT);

  ///////////////////////////
}

void loop() {


  heartBeat = digitalRead(heartPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (heartBeat == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }

  Packet packet;
  packet.sensor0 = heartBeat;
  packet.sensor1 = heartBeat;
  packet.sensor2 = heartBeat;
  packet.sensor3 = heartBeat;

  int numberOfRetries = 0;

  // send reliable packet to the hub
  // notice the & next to packet when sending a struct
  boolean gotACK = radio.sendWithRetry(hubID,  &packet, sizeof(packet), numberOfRetries);
  delay(2);
//  if (gotACK) {
//    Serial.println("got acknowledgment");
//  }
//  else {
//    Serial.println("failed acknowledgment");
//  }
}
