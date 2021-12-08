#include "main.h"




//lift functions
void setMogo(int power)
{
  mogoLeft = power;
  mogoRight = power;
}

void setMogoMotors()
{

  //bottom puts down, upper picks up
  int mogoPower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1));
  setMogo(mogoPower);

}
