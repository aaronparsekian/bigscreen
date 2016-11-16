////////////EMG 2 TX/////////
///////////Big Screens 2016 Aaron Parsekian////////////////
///////////////////////////
//////917MHz///////

/*

  This sketch demonstrates a simple wireless low-power sensor node,
  sending packets to the receiver on this network.
  To make parsing packets easier, data is sent using the C++ struct.
  This allows both sender and receiver to read and write to the packet
  using the familiar object-dot-variable syntax.

  See the "wiring_rfm69.png" for how to hookup the circuit.

  To complete the example, run the "sensor_receive.ino" sketch
  on another Arduino with an RFm69 connected

  Be sure you have downloaded and installed the library used here:

    RFm69 Library: https://github.com/lowpowerlab/rfm69
    Narcoleptic Library: https://code.google.com/p/narcoleptic/downloads/list

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

int myNetwork = 214; // radios must share the same network (0-255)
int myID = 9; // radios should be given unique ID's (0-254, 255 = BROADCAST)

int hubID = 0; // the receiver for all sensor nodes in this example

// instead of sending a string, we can send a struct
// this struct must be shared between all nodes
typedef struct {
  int sensor0;
  int sensor1;
} Packet;

int led0 = 10;
int led1 = 11;

int sensorValue0;
int sensorValue1;
int outputValue0;
int outputValue1;

void setup() {

  // setup the radio
  radio.initialize(myFrequency, myID, myNetwork);

  // this example only uses Serial inside setup()
  // because Narcoleptic will stop Serial once used
  //Serial.begin(9600);
//  Serial.println("\nRADIO INITIALIZED");
//  Serial.println("Sending sensor values");
}

void loop() {

  // create new instance of our Packet struct
  Packet packet;
  packet.sensor0 = sensorValue0; // read values from the analog pins
  packet.sensor1 = sensorValue1;
  //packet.sensor2 = analogRead(A2);
  int numberOfRetries = 0;

  // send reliable packet to the hub
  // notice the & next to packet when sending a struct
  boolean gotACK = radio.sendWithRetry(hubID,  &packet, sizeof(packet), numberOfRetries);
//
//  if (gotACK) {
//    Serial.println("got acknowledgment");
//  }
//  else {
//    Serial.println("failed acknowledgment");
//  }
  delay(2);
  sensorValue0 = analogRead(A0);
  sensorValue1 = analogRead(A1);

  outputValue0 = map(sensorValue0, 2, 900, 1, 255);
  outputValue1 = map(sensorValue1, 2, 900, 1, 255);

  analogWrite(led1, outputValue0);
  analogWrite(led0, outputValue1);
}
