#include "main.h"

bool intakeButtonPress = false;


void setIntake(int power)
{
  intake = power;
}



void setIntakeMotors()
{
  if(controller.get_digital(DIGITAL_UP) && !intakeButtonPress) {
    intakeButtonPress = true;
    setIntake(120);
  } else if (controller.get_digital(DIGITAL_UP) && intakeButtonPress) {
    intakeButtonPress = false;
    setIntake(0);
  }
  else
    intakeButtonPress = false;
}
