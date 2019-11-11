#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Empty.h>
#include <std_msgs/String.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *drive = AFMS.getMotor(1); //getMotor(port#)
Adafruit_DCMotor *servo = AFMS.getMotor(2); //getMotor(port#)

ros::NodeHandle  nh;

std_msgs::String stat;

std_msgs::Int16 throt;


int PWMValue;
int arduinoThrottle;
int ms;
int runTime;



void forwardMsg( const std_msgs::Int16& forwardTime)
{
  runTime = forwardTime.data;
  forward(runTime);
}

void leftMsg( const std_msgs::Int16& leftTime)
{
  runTime = leftTime.data;
  left(runTime);
}

void rightMsg( const std_msgs::Int16& rightTime)
{
  runTime = rightTime.data;
  right(runTime);
}

void reverseMsg( const std_msgs::Int16& reverseTime)
{
  runTime = reverseTime.data;
  reverse(runTime);
}

void stopMsg( const std_msgs::Empty& stopCommand)//this doesn't work, it fails to stop thruster movement, so play it safe and don't run thrusters for long while testing
{
  drive->run(RELEASE);
  servo->run(RELEASE);

  Status_Update("stopped thrusters");
}

void throttleMsg( const std_msgs::Int16& throttleValue)
{
  arduinoThrottle = throttleValue.data;
  throttle(arduinoThrottle);
}


ros::Publisher statusUpdate("status", &stat);//here is where all of the ROS topics are defined as either a subscriber or publisher. Each has a ROS name (forward, left, etc.) and an Arduino name (sub 1, sub 2, etc.)

ros::Publisher throttleUpdate("throttleStatus", &throt);

ros::Subscriber<std_msgs::Int16> sub1("forward", &forwardMsg ); //<std_msgs::Int16> defines datatype, you need to include each datatype library you use globally (very top of this tab).

ros::Subscriber<std_msgs::Int16> sub2("left", &leftMsg );

ros::Subscriber<std_msgs::Int16> sub3("right", &rightMsg );

ros::Subscriber<std_msgs::Int16> sub4("reverse", &reverseMsg );

ros::Subscriber<std_msgs::Empty> sub5("stop", &stopMsg );

ros::Subscriber<std_msgs::Int16> sub6("throttleControl", &throttleMsg);



void setup()
{
  nh.initNode();
  nh.subscribe(sub1);
  nh.subscribe(sub2);
  nh.subscribe(sub3);
  nh.subscribe(sub4);
  nh.subscribe(sub5);
  nh.subscribe(sub6);
  
  nh.advertise(statusUpdate);
  nh.advertise(throttleUpdate);

  AFMS.begin(); //starts motor shield

  servo->setSpeed(100); //speed servo will run (no need to change)

  drive->setSpeed(100); //speed drive motor will run


}

void loop()
{
  nh.spinOnce();
  delay(10);
}
