#include "main.h"




//lift functions
void setIntake(int power)
{
  conveyor = power;
}

void setIntakeMotors()
{
  int intakePower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2));
  setIntake(intakePower);
}
