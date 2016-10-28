/**
 * oscP5sendreceive by andreas schlegel
 * example shows how to send and receive osc messages.
 * oscP5 website at http://www.sojamo.de/oscP5
 */

import oscP5.*;
import netP5.*;

//config
int listeningPort = 6001;  

//variables for receiving data
int bno0, bno1, bno2;
int polar0;
int emg0, emg1;

//variables for osc communication
OscP5 oscP5;
NetAddress host;
float pct;

void setup() {
  //size(11520,1080);
  //fullScreen(P2D, SPAN);
  size(10, 10);
  frameRate(25);
  /* start oscP5, listening for incoming messages at port 12000 */
  oscP5 = new OscP5(this, listeningPort);

  /* myRemoteLocation is a NetAddress. a NetAddress takes 2 parameters,
   * an ip address and a port number. myRemoteLocation is used as parameter in
   * oscP5.send() when sending osc packets to another computer, device, 
   * application. usage see below. for testing purposes the listening port
   * and the port of the remote location address are the same, hence you will
   * send messages back to this sketch.
   */
  //host = new NetAddress("localhost",12000);
}


void draw() {
  background(0);
}


/* incoming osc message are forwarded to the oscEvent method. */
void oscEvent(OscMessage theOscMessage) {
  /* print the address pattern and the typetag of the received OscMessage */
  //print("### received an osc message.");


  if (theOscMessage.checkAddrPattern("/bno")) {
    //println("got bno");
    bno0 = theOscMessage.get(0).intValue();
    bno1 = theOscMessage.get(1).intValue();
    bno2 = theOscMessage.get(2).intValue();
  } else if (theOscMessage.checkAddrPattern("/polar")) {
     polar0 = theOscMessage.get(0).intValue();
  } else if (theOscMessage.checkAddrPattern("/emg")) {
    emg0 = theOscMessage.get(0).intValue();
    emg1 = theOscMessage.get(1).intValue();
  }
  
  //print the data
  println("bno: " + bno0 + ", " + bno1 + ", " + bno2);
  println("polar: " + polar0);
  println("emg: " + emg0 + ", " + emg1);




  //print(" addrpattern: "+ theOscMessage.addrPattern());
  //print(" typetag: "+ theOscMessage.typetag());
  //println(" value: "+ theOscMessage.get(0).intValue());
}