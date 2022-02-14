#include "main.h"

bool powerCompensate = false;

static const int UP_MOGO_THRESH = -1000;
static const int DOWN_MOGO_THRESH = -2050;
static const int MOGO_ERROR_BUFFER = 50;

static bool mogoPos = true; //true for up

//lift functions
void setMogo(int power)
{
  mogo = power;
}

void setMogoMotors()
{

  controller.set_text(1, 2, "MOGOPOS: " + std::to_string(mogo.get_position()));

  //bottom puts down, upper picks up
  int mogoPower;
  // mogoPower = 40 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2));

  if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_B))
    powerCompensate = !powerCompensate;

  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) > 0) {
    mogoPos = true;
  } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) > 0) {
    mogoPos = false;
  }



  // if(powerCompensate)
  //   controller.set_text(0, 7, "C");
  // else
  //   controller.set_text(0, 7, "N");


  // if(abs(mogoPower) < 127 && !powerCompensate)
  //   mogoPower = 0;
  // else if(abs(mogoPower) < 127 && powerCompensate)
  //   mogoPower = 20;

  if (mogoPos) {
    if (fabs(mogo.get_position() - UP_MOGO_THRESH) < MOGO_ERROR_BUFFER) {
      mogoPower = 0;
    } else if (mogo.get_position() > UP_MOGO_THRESH) {
      mogoPower = -60;
    } else {
      mogoPower = 110;
    }
  } else {
    if (fabs(mogo.get_position() - DOWN_MOGO_THRESH) < MOGO_ERROR_BUFFER) {
      mogoPower = 0;
    } else if (mogo.get_position() > DOWN_MOGO_THRESH) {
      mogoPower = -90;
    } else {
      mogoPower = 10;
    }
  }

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
