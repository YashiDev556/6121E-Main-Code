#include "main.h"


//toggles
bool reversed = false;

//HELPER FUNCTIONS
void setDrive(int left, int right, bool reverse)
{
  driveLeftBack = left;
  driveLeftFront = left;
  driveRightBack = right;
  driveRightFront = right;

  if(reverse == true)
  {
    driveLeftBack = right*-1;
    driveLeftFront = right*-1;
    driveRightBack = left*-1;
    driveRightFront = left*-1;
  }
}


//DRIVER CONTROL FUNCTIONS
void setDriveMotors()
{
  int leftJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int rightJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);



  if(abs(leftJoystick) < 10)
    leftJoystick = 0;
  if(abs(rightJoystick) < 10)
    rightJoystick = 0;

  if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X))
  {
    reversed = true;
    //controller.clear();
    controller.set_text(1, 4, "-R-----REVERSE----");
  }

  if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_B))
  {
    reversed = false;
    //controller.clear();
    controller.set_text(1, 4, "-D-----DRIVE------");
  }




  setDrive(leftJoystick, rightJoystick, reversed);


}
