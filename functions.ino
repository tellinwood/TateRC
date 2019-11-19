void Status_Update(char statUpdate[255])
{
  stat.data = statUpdate;
  statusUpdate.publish(&stat);
}

void Throttle_Update(int throtUpdate)
{
  throt.data = throtUpdate;
  throttleUpdate.publish(&throt);
}

void Compass_Update(int compUpdate)
{
  comp.data = compUpdate;
  compassUpdate.publish(&comp);
}


void forward(int runTime)
{
  Status_Update("forward command received");
  ms = runTime * 1000;

  drive->run(FORWARD);
  delay(ms);
  drive->run(RELEASE);

  Status_Update("driven forward");
}

void left(int runTime)
{
  Status_Update("left command received");

  servo->run(FORWARD);
  delay(100);
  drive->run(FORWARD);
  delay(ms);
  drive->run(RELEASE);
  delay(100);
  servo->run(BACKWARD);
  delay(175);
  servo->run(RELEASE);

  Status_Update("steered left");
}

void right(int runTime)
{
  Status_Update("right command received");
  ms = runTime * 1000;

  servo->run(BACKWARD);
  delay(100);
  drive->run(FORWARD);
  delay(ms);
  drive->run(RELEASE);
  delay(100);
  servo->run(FORWARD);
  delay(175);
  servo->run(RELEASE);


  Status_Update("steered right");
}


void reverse(int runTime)
{
  Status_Update("reverse command received");
  ms = runTime * 1000;

  drive->run(BACKWARD);
  delay(ms);
  drive->run(RELEASE);

  Status_Update("driven in reverse");
}

void compassAllign(int newDirection)
{
  Status_Update("new direction received");
  Throttle_Update(newDirection);
  delay(500);
  Throttle_Update(currentHeading);

  newDirectionTolerance = 10;

  newDirectionLowerLimit = (newDirection - (newDirectionTolerance / 2));

  newDirectionUpperLimit = (newDirection + (newDirectionTolerance / 2));

  delay(500);
  Throttle_Update(newDirectionLowerLimit);
  delay(500);
  Throttle_Update(newDirectionUpperLimit);
  delay(500);

  while (currentHeading < newDirectionLowerLimit or currentHeading > newDirectionUpperLimit)
  {
    Status_Update("gimme a sec");
    servo->run(FORWARD);
    delay(100);
    drive->run(FORWARD);
    delay(1000);
  }

  Status_Update("arrived at new heading");
  drive->run(RELEASE);
  delay(10);
  servo->run(RELEASE);
}

void throttle(int arduinoThrottle)
{
  Status_Update("throttle command received");

  delay(1000);

  if (arduinoThrottle > 0 && arduinoThrottle < 255)
  {
    PWMValue = arduinoThrottle;
    drive->setSpeed(PWMValue);
    Status_Update("throttle adjusted");

    Throttle_Update(PWMValue);
  }
  else if (arduinoThrottle < 0)
  {
    PWMValue = 100;
    drive->setSpeed(PWMValue);
    Status_Update("throttle cannot be below 0, Throttle reset to 100");

    Throttle_Update(PWMValue);
  }
  else if (arduinoThrottle > 255)
  {
    PWMValue = 100;
    drive->setSpeed(PWMValue);
    Status_Update("throttle cannot be above 255, Throttle reset to 100");

    Throttle_Update(PWMValue);
  }

}
