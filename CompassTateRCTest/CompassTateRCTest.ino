
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

// Compass navigation
int targetHeading;              // where we want to go to reach current waypoint
int currentHeading;             // where we are actually facing now
int headingError;               // signed (+/-) difference between targetHeading and currentHeading
float headingDegrees;
#define HEADING_TOLERANCE 5     // tolerance +/- (in degrees) within which we don't attempt to turn to intercept targetHeading

void setup() {
  // put your setup code here, to run once:
  mag.begin();
  Serial.begin(9600);
  Serial.println("Compass heading");
}

void loop() {

  currentHeading = readCompass();
  Serial.println(headingDegrees); //this is the current heading (in degrees) of TateRC. Use this to create an autonomous function that compares it to an input direction
  delay(10);
  compassAllign(headingDegrees);
}


int readCompass(void)
{
  sensors_event_t event;
  mag.getEvent(&event);
  float heading = atan2(event.magnetic.y, event.magnetic.x);

  float headingDegrees = heading * 180 / M_PI;

  return ((int)headingDegrees);
}
