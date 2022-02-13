#include "main.h"

static const int UP_THRESH = -30;
static const int DOWN_THRESH = -505;
static const int CLAW_ERROR_BUFFER = 20;

static bool clampDown = false; //false for open



//lift functions
void setClaw(int power)
{
  claw = power;
}

void setClawMotors()
{
  controller.set_text(0, 1, "CLAWPOS: " + std::to_string(claw.get_position()));
  pros::lcd::set_text(1, "CLAWPOS: " + std::to_string(claw.get_position()));

  // int clawPower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_A));
  // if (clawPower > 0) {
  //   if (claw.get_position() < UP_THRESH) {
  //     setClaw(clawPower);
  //   } else {
  //     setClaw(-10);
  //   }
  // } else if (clawPower < 0) {
  //   if (claw.get_position() > DOWN_THRESH) {
  //     setClaw(clawPower);
  //   } else {
  //     setClaw(10);
  //   }
  // } else {
  //   setClaw(0);
  // }

  int clawPower;
  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) > 0) {
    clampDown = false;
  } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) > 0) {
    clampDown = true;
  }

  if (clampDown) {
    if (fabs(claw.get_position() - DOWN_THRESH) < CLAW_ERROR_BUFFER) {
      setClaw(0);
    } else if (claw.get_position() > DOWN_THRESH) {
      setClaw(-60);
    } else {
      setClaw(10);
    }
  } else {
    if (fabs(claw.get_position() - UP_THRESH) < CLAW_ERROR_BUFFER) {
      setClaw(0);
    } else if (claw.get_position() > UP_THRESH) {
      setClaw(-40);
    } else {
      setClaw(60);
    }
  }





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