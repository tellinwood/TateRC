#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/String.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *drive = AFMS.getMotor(1); //getMotor(port#)
Adafruit_DCMotor *servo = AFMS.getMotor(2); //getMotor(port#)

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

ros::NodeHandle  nh;

std_msgs::String stat;

std_msgs::Int16 comp;

int ms;
int runTime;

// Compass navigation
int targetHeading;              // where we want to go to reach current waypoint
int currentHeading;             // where we are actually facing now
float headingDegrees;
int newDirection; // desired direction sent via ROS
int newDirectionUpperLimit; // upper tolerance for degrees (TateRC will not try to adjust to exactly newDirection, but instead to within these limits)
int newDirectionLowerLimit; // lower tolerance for degrees
int newDirectionTolerance; // tolerance, which can be set globally (degree span between newDirectionUpperLimit and newDirectionLowerLimit)
float heading;



void compassAllignMsg( const std_msgs::Int16& ROSNewDirection)
{
  newDirection = ROSNewDirection.data;
  compassAllign(newDirection);
}



ros::Publisher statusUpdate("status", &stat);//here is where all of the ROS topics are defined as either a subscriber or publisher. Each has a ROS name (forward, left, etc.) and an Arduino name (sub 1, sub 2, etc.)

ros::Publisher compassUpdate("compassStatus", &comp);

ros::Subscriber<std_msgs::Int16> sub1("compassAllign", &compassAllignMsg );


void setup()
{
  nh.initNode();

  nh.subscribe(sub1);

  nh.advertise(statusUpdate);
  nh.advertise(compassUpdate);

  AFMS.begin(); //starts motor shield

  servo->setSpeed(100); //speed servo will run (no need to change)

  drive->setSpeed(120); //speed drive motor will run

  mag.begin(); //starts compass sensor


}



void loop()
{
  nh.spinOnce();
  delay(10);  
}
