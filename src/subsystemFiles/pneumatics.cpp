#include "main.h"


pros::ADIDigitalOut backClamp('A');

bool isBackClamped = false;

bool backClampButtonPress = false;




void setBackClamp(bool state)
{
  backClampButtonPress = state;
  if(isBackClamped)
    backClamp.set_value(HIGH);
  else
    backClamp.set_value(LOW);
}

void backClampOP()
{
  if(controller.get_digital(DIGITAL_LEFT) && !backClampButtonPress) {
    backClampButtonPress = true;
    backClamp.set_value(LOW);
  } else if (controller.get_digital(DIGITAL_RIGHT) && !backClampButtonPress) {
    backClampButtonPress = true;
    backClamp.set_value(HIGH);
  }
  else
    backClampButtonPress = false;
}
