#include "main.h"

//lift functions
void setClaw(int power)
{
  claw = power;
}

void setClawMotors()
{
  int clawPower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_A));
  setClaw(clawPower);
}



void resetClawEncoders()
{
  claw.tare_position();
}


double clawEncoderValue()
{
  return (fabs(claw.get_position()));
}


void clawAuton(int units, int voltage) 
{
//define a direction based on units provided
  int direction = abs(units) / units; //either 1 or -1

  //reset the motor encoders
  resetClawEncoders();



  //drive forward until units are reached
  while(clawEncoderValue() < abs(units))
  {
    setClaw(voltage * direction);
    pros::delay(10);
  }
  //brief brake
  setClaw(-10 * direction);
  pros::delay(20);
  //set drive back to neutral
  setClaw(0);
}
