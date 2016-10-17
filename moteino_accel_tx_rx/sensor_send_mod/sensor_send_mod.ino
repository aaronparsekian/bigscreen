///////////////////////////
///////////////////////////
///////////////////////////

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

///////////////////////////
///////////////////////////
///////////////////////////

#include <RFM69.h>
#include <SPI.h> // the RFM69 library uses SPI
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 bno = Adafruit_BNO055(55);

RFM69 radio;

#define myFrequency RF69_915MHZ // or RF69_433MHZ (check your radio)
int myNetwork = 123; // radios must share the same network (0-255)
int myID = 1; // radios should be given unique ID's (0-254, 255 = BROADCAST)

int hubID = 0; // the receiver for all sensor nodes in this example

// instead of sending a string, we can send a struct
// this struct must be shared between all nodes
typedef struct {
  int sensor0;
  int sensor1;
  int sensor2;
} Packet;

///////////////////////////
///////////////////////////
///////////////////////////


void setup() {

  // setup the radio
  radio.initialize(myFrequency, myID, myNetwork);

  // this example only uses Serial inside setup()
  // because Narcoleptic will stop Serial once used
  Serial.begin(9600);
  Serial.println("\nRADIO INITIALIZED");
  Serial.println("Sending sensor values");

  /* Initialise the sensor */
  if (!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }


}

///////////////////////////
///////////////////////////
///////////////////////////

void loop() {

  sensors_event_t event;
  bno.getEvent(&event);

  delay(10);

  // create new instance of our Packet struct
  Packet packet;
  //  packet.sensor0 = (int)(255 * (float)event.orientation.x);
  //  packet.sensor1 = (int)(255 * (float)event.orientation.y);
  //  packet.sensor2 = (int)(255 * (float)event.orientation.z);
  packet.sensor0 = (int)event.orientation.x;
  packet.sensor1 = (int)event.orientation.y;
  packet.sensor2 = (int)event.orientation.z;
  Serial.println(packet.sensor0);
  Serial.println(packet.sensor1);
  Serial.println(packet.sensor2);


  int numberOfRetries = 3;

  // send reliable packet to the hub
  // notice the & next to packet when sending a struct
  boolean gotACK = radio.sendWithRetry(hubID,  &packet, sizeof(packet), numberOfRetries);

  if (gotACK) {
    Serial.println("got acknowledgment");
  }
  else {
    Serial.println("failed acknowledgment");
  }
  delay(BNO055_SAMPLERATE_DELAY_MS);
}

///////////////////////////
///////////////////////////
///////////////////////////
