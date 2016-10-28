///////////////////////////
//////////BIG SCREENS 2016 POLAR TX//////////////
///////////////////////////




#include <RFM69.h>
#include <SPI.h> // the RFM69 library uses SPI

#define IS_RFM69HCW   true
#define RFM69_CS      8
#define RFM69_IRQ     7
#define RFM69_IRQN    4  // Pin 7 is IRQ 4!
#define RFM69_RST     4

RFM69 radio = RFM69(RFM69_CS, RFM69_IRQ, IS_RFM69HCW, RFM69_IRQN);


#define myFrequency RF69_915MHZ // or RF69_433MHZ (check your radio)
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
  Serial.begin(9600);
  Serial.println("\nRADIO INITIALIZED");
  Serial.println("Sending sensor values");

  ///////////////////////////

  pinMode(heartPin, INPUT);
  pinMode(ledPin, OUTPUT);

  ///////////////////////////
}

void loop() {

  //delay(50);

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

  if (gotACK) {
    Serial.println("got acknowledgment");
  }
  else {
    Serial.println("failed acknowledgment");
  }
}
