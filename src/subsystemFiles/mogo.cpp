#include "main.h"

bool powerCompensate = false;


//lift functions
void setMogo(int power)
{
  mogo = power;
}

void setMogoMotors()
{

  //bottom puts down, upper picks up
  int mogoPower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2));

  if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_B))
    powerCompensate = !powerCompensate;



  // if(powerCompensate)
  //   controller.set_text(0, 7, "C");
  // else
  //   controller.set_text(0, 7, "N");


  if(abs(mogoPower) < 127 && !powerCompensate)
    mogoPower = 0;
  else if(abs(mogoPower) < 127 && powerCompensate)
    mogoPower = 20;

  setMogo(mogoPower);


}


void resetMogoEncoders()
{
  mogo.tare_position();
}


double mogoEncoderValue()
{
  return (fabs(mogo.get_position()));
}


void mogoAuton(int units, int voltage) 
{
//define a direction based on units provided
  int direction = abs(units) / units; //either 1 or -1

  //reset the motor encoders
  resetMogoEncoders();



  //drive forward until units are reached
  while(mogoEncoderValue() < abs(units))
  {
    setMogo(voltage * direction);
    pros::delay(10);
  }
  //brief brake
  setMogo(-10 * direction);
  pros::delay(20);
  //set drive back to neutral
  setMogo(0);
}



