#include "main.h"



//lift functions
void setLift(int power)
{
  lift = power;
}

void setLiftMotors()
{
  int liftPower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2));
  setLift(liftPower);
}


void resetLiftEncoders()
{
  lift.tare_position();
}


double liftEncoderValue()
{
  return (fabs(lift.get_position()));
}


void liftAuton(int units, int voltage) 
{
//define a direction based on units provided
  int direction = abs(units) / units; //either 1 or -1

  //reset the motor encoders
  resetLiftEncoders();



  //drive forward until units are reached
  while(liftEncoderValue() < abs(units))
  {
    setLift(voltage * direction);
    pros::delay(10);
  }
  //brief brake
  setLift(-10 * direction);
  pros::delay(20);
  //set drive back to neutral
  setLift(0);
}
