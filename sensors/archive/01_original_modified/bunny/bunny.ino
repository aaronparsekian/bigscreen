//big screens
//nyu itp fall 2016
//by lisa jamhoury, aaron parsekian
//runs on arduino uno
//arduino ide 1.6.5
//done on a macbook pro os sierra
//october 2016
//based on code from adafruit
//https://learn.adafruit.com/adafruit-bno055-absolute-orientation-sensor/processing-test


//import libraries
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>


/*
This driver uses the Adafruit_Sensor library,
provides a common 'type' for sensor data

You should assign a unique ID to this sensor for use with the Adafruit Sensor API 
so that you can identify this particular sensor in any data logs.
To assign a unique ID, provide an appropriate value in the constructor below
(12345 is used by default in this example).

Connections:
Connect SCL to analog 5
Connect SDA to analog 4
Connect VDD to 3.3-5V DC
Connect GROUND to common ground

*/

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 bno = Adafruit_BNO055(55);

//Displays some basic information on this sensor from the unified
//sensor API sensor_t type (see Adafruit_Sensor for more information)

void displaySensorDetails(void)
{
  sensor_t sensor;
  //bno.getSensor(&sensor);
//  Serial.println("------------------------------------");
//  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
//  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
//  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
//  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" xxx");
//  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" xxx");
//  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" xxx");
//  Serial.println("------------------------------------");
//  Serial.println("");
  delay(500);
}



void setup()
{
  Serial.begin(9600);
  Serial.println("*"); Serial.println("");

  /* Initialise the sensor */
  if (!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }

  delay(1000);

 // displaySensorDetails();
}

void loop()
{
  /* Get a new sensor event */
  sensors_event_t event;
  bno.getEvent(&event);

  /* Board layout:
         +----------+
         |         *| RST   PITCH  ROLL  HEADING
     ADR |*        *| SCL
     INT |*        *| SDA     ^            /->
     PS1 |*        *| GND     |            |
     PS0 |*        *| 3VO     Y    Z-->    \-X
         |         *| VIN
         +----------+
  */

  /* The processing sketch expects data as roll, pitch, heading */
  //Serial.print(F("Orientation: "));
  Serial.print((float)event.orientation.x);
  Serial.print(", ");
  //Serial.print(F(" "));
  Serial.print((float)event.orientation.y);
  Serial.print(", ");
  //Serial.print(F(" "));
  Serial.println((float)event.orientation.z);
  //Serial.println(F(""));


  delay(BNO055_SAMPLERATE_DELAY_MS);
}
