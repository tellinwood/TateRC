void compassAllign(int newDirection)
{
  Status_Update("new direction received");

  newDirectionLowerLimit = (newDirection - (newDirectionTolerance / 2);
  newDirectionUpperLimit = (newDirection + (newDirectionTolerance / 2);

  if (headingDegrees < newDirectionLowerLimit && headingDegrees > newDirectionUpperLimit)
  {
    Status_Update("gimme a sec")
     //drive in a circle (pseudo code)
  }
  else if (headingDegrees > newDirectionLowerLimit && headingDegrees < newDirectionUpperLimit)
  {
    Status_Update("arrived at new heading");
    //stop motors (whatever drive and servo RELEASE) fix this pseudo code
  }
}
