void Status_Update(char statUpdate[255])
{
  stat.data = statUpdate;
  statusUpdate.publish(&stat);
}

void Compass_Update(int compUpdate)
{
  comp.data = compUpdate;
  compassUpdate.publish(&comp);
}

int readCompass()
{
  sensors_event_t event;
  mag.getEvent(&event);

  float Pi = 3.14159;

  //Calculate the angle of the vector y, x
  float heading = (atan2(event.magnetic.y, event.magnetic.x) * 180) / Pi;

  //Normalize to 0 - 360
  if (heading < 0)
  {
    heading = 360 + heading;
  }
  delay(500);
  return (heading);
}

void compassAllign(int newDirection)
{
  Status_Update("new direction received");
  Status_Update(newDirection);
  delay(100);

  readCompass();
  heading = currentHeading;
  
  Status_Update(currentHeading);
  delay(100);

  newDirectionTolerance = 10;

  newDirectionLowerLimit = (newDirection - (newDirectionTolerance / 2));

  newDirectionUpperLimit = (newDirection + (newDirectionTolerance / 2));

  while (currentHeading < newDirectionLowerLimit or currentHeading > newDirectionUpperLimit)
  {
    Status_Update("gimme a sec");
    servo->run(FORWARD);
    drive->run(FORWARD);
  }

  drive->run(RELEASE);
  servo->run(RELEASE);

  Status_Update("arrived at new heading");
}
