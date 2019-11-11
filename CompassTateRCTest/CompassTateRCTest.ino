
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

// Compass navigation
int targetHeading;              // where we want to go to reach current waypoint
int currentHeading;             // where we are actually facing now
int headingError;               // signed (+/-) difference between targetHeading and currentHeading
float headingDegrees;
int newDirection; // desired direction sent via ROS
int newDirectionUpperLimit; // upper tolerance for degrees (TateRC will not try to adjust to exactly newDirection, but instead to within these limits)
int newDirectionLowerLimit; // lower tolerance for degrees
int newDirectionTolerance; // tolerance, which can be set globally (degree span between newDirectionUpperLimit and newDirectionLowerLimit)


void setup() {
  // put your setup code here, to run once:
  mag.begin();
  Serial.begin(9600);
  Serial.println("Compass heading");
  newDirectionTolerance = 10
  
}

void compassAllignMsg( const std_msgs::Int8& ROSNewDirection)
{
  newDirection = ROSNewDirection.data;
  compassAllign(newDirection);
}

ros::Subscriber<std_msgs::Int8> sub1("compassAllign", &compassAllignMsg ); //<std_msgs::Int8> defines datatype, you need to include each datatype library you use globally (very top of this tab).

void loop() {

  currentHeading = readCompass();
  Serial.println(headingDegrees); //this is the current heading (in degrees) of TateRC. Use this to create an autonomous function that compares it to an input direction
}


int readCompass(void)
{
  sensors_event_t event;
  mag.getEvent(&event);
  float heading = atan2(event.magnetic.y, event.magnetic.x);

  float headingDegrees = heading * 180 / M_PI; //headingDegrees is the current heading of TateRC

  return ((int)headingDegrees);
}
