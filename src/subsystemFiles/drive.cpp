#define _USE_MATH_DEFINES

#include "main.h"
#include <cmath>
#include <vector>
#include <math.h>
#include <numeric>

//DRIVE CONSTANTS AND VARIABLES

//guages and toggles for setting voltage

bool usePID = true; //true uses straight  drive PID, false uses Square Root Drive

int maxStraightVoltage = 127;  //
int maxTurnVoltage = 87;
int maxArcVoltage = 107;

static double leftTarget = 0.0;
double leftPos = 0.0;
double leftError = leftTarget - leftPos;
std::vector<double> leftPrevErrors(2, leftError);
double leftDerivative = 0.0;
double leftIntegral = 0.0;
double leftPower = 0.0;


static double rightTarget = 0.0;
double rightPos = 0.0;
double rightError = rightTarget - rightPos;
std::vector<double> rightPrevErrors(2, rightError);
double rightDerivative = 0.0;
double rightIntegral = 0.0;
double rightPower = 0.0;



//Vars for multitasking
int driveTaskID = 0;

/* DRIVE TASK ID KEY:
   0 - idle / transitioning
   1 - constant straight drive
   2 - constant turn
   3 - sqrt straight drive
   4 - PID straight drive
   5 - PID turn
   6 - PID arc drive
*/

int driveTaskInches = 0;
int driveTaskDegrees = 0;
int driveTaskRadius = 0;

void setDriveTask(int id, double p1, double p2) {
  driveTaskID = id;
  driveTaskInches = 0;
  driveTaskDegrees = 0;
  driveTaskRadius = 0;

  switch (driveTaskID) {
    case 0:
      break;
    case 1:
      driveTaskInches = p1;
      break;
    case 2:
      driveTaskDegrees = p1;
      break;
    case 3:
      driveTaskInches = p1;
      break;
    case 4:
      driveTaskInches = p1;
      break;
    case 5:
      driveTaskDegrees = p1;
      break;
    case 6:
      driveTaskRadius = p1;
      driveTaskDegrees = p2;
      break;
  }
}

void autonDriveTask(void *parameter) {
  while (true) {
    switch (driveTaskID) {
      case 0:
        controller.set_text(0, 1, "IDLE...");
        break;
      case 1:
        translate(driveTaskInches, maxStraightVoltage);
        break;
      case 2:
        turnPID(driveTaskDegrees);
        break;
      case 3:
        translate(driveTaskInches, maxStraightVoltage); //change later
        break;
      case 4:
        straightPID(driveTaskInches);
        break;
      case 5:
        turnPID(driveTaskDegrees);
        break;
      case 6:
        arcPID(driveTaskRadius, driveTaskDegrees);
        break;
      }
    }
    driveTaskID = 0;
}







//constants for setting voltage
const int BRAKE_TIME = 100; //just trying out a new brake time - original was 50

//weights for straight drive pid
const double STRAIGHT_KP = 0.4;
const double STRAIGHT_KD = 0.0;
const double STRAIGHT_KI = 0.0;

//weights for pid turning
const double TURN_KP = 0.4;
const double TURN_KD = 0.0;
const double TURN_KI = 0.0;

//weights for arc driving pid
const double ARC_KP = 0.4;
const double ARC_KD = 0.0;
const double ARC_KI = 0.0;

//robot measurements
const static double WHEEL_DIAMETER = 4.125;
const static double GEAR_RATIO = 36.0 / 60.0;
const static double TICKS_PER_INCH = 900.0 / (M_PI * WHEEL_DIAMETER * GEAR_RATIO); //900 ticks per revolution

const static double CHASSIS_WIDTH = 12.0; //lenght from wheel to wheel on opposite side
const static double TICKS_PER_DEGREE = (2.5 * CHASSIS_WIDTH) / (WHEEL_DIAMETER * GEAR_RATIO); //only for turning not arc


//field measurement constants
const static double GOAL_RUSH = 67.5;



//HELPER FUNCTIONS
double degreesToTicks(double degrees) {
   return degrees*TICKS_PER_DEGREE;
}

double ticksToDegrees(double ticks) {
   return ticks/TICKS_PER_DEGREE;
}

double inchesToTicks(double inches) {
   return inches*TICKS_PER_INCH;
}

double ticksToInches(double ticks) {
   return ticks/TICKS_PER_INCH;
}


void setDrive(int left, int right)
{
  driveLeftBack = left;
  driveLeftFront = left;
  driveRightBack = right;
  driveRightFront = right;
}


void resetDriveEncoders()
{
  driveLeftBack.tare_position();
  driveLeftFront.tare_position();
  driveRightBack.tare_position();
  driveRightFront.tare_position();
}

double avgDriveEncoderValue()
{
  return (fabs(driveLeftFront.get_position()) +
          fabs(driveLeftBack.get_position()) +
          fabs(driveRightFront.get_position()) +
          fabs(driveRightBack.get_position())) / 4;
}

double leftDriveEncoderValue()
{
  // return (fabs(driveLeftFront.get_position()) +
  //         fabs(driveLeftBack.get_position())) / 2;
  return (driveLeftFront.get_position() +
          driveLeftBack.get_position()) / 2;
}

double rightDriveEncoderValue()
{
  // return (fabs(driveRightFront.get_position()) +
  //         fabs(driveRightBack.get_position())) / 2;
  return (driveRightFront.get_position() +
          driveRightBack.get_position()) / 2;
}


bool errorCheck(int d, int max) {

  if (leftPrevErrors.size() < d) {
    return true;
  } else {
    for (unsigned i = leftPrevErrors.size() - d; i < leftPrevErrors.size(); i++) {
      if (fabs(leftPrevErrors.at(i)) > max) {
        return true;
      }
    }
  }

  for (unsigned i = rightPrevErrors.size() - d; i < rightPrevErrors.size(); i++) {
    if (fabs(rightPrevErrors.at(i)) > max) {
      return true;
    }
  }
  return false;

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
  setDrive(leftJoystick, rightJoystick);

}

void reverseDriveMotors() {
  driveLeftBack.set_reversed(!driveLeftBack.is_reversed());
  driveLeftFront.set_reversed(!driveLeftFront.is_reversed());
  driveRightBack.set_reversed(!driveRightBack.is_reversed());
  driveRightFront.set_reversed(!driveRightFront.is_reversed());
}

void resetPIDVars(int left_units, int right_units) {
  resetDriveEncoders();

  leftTarget = left_units;
  leftPos = leftDriveEncoderValue();
  leftError = leftTarget - leftPos;
  leftPrevErrors.assign(2, leftError);
  leftDerivative = 0;
  leftIntegral = accumulate(leftPrevErrors.begin(), leftPrevErrors.end(), -2.0*leftError);
  leftPower = 0;


  rightTarget = right_units;
  rightPos = rightDriveEncoderValue();
  rightError = rightTarget - rightPos;
  rightPrevErrors.assign(2, rightError);
  rightDerivative = 0;
  rightIntegral = accumulate(rightPrevErrors.begin(), rightPrevErrors.end(), -2.0*rightError);
  rightPower = 0;
}

//AUTONOMOUS CONTROL FUNCTIONS

void translate(double units, int voltage)
{
  //define a direction based on units provided
  int direction = abs(units) / units; //either 1 or -1
  units = units * TICKS_PER_INCH;
  //reset the motor encoders
  resetDriveEncoders();
  //drive forward until units are reached
  while(avgDriveEncoderValue() < abs(units))
  {
    setDrive(voltage * direction, voltage * direction);
    pros::delay(10);
  }
  //brief brake
  setDrive(-10 * direction, -10 * direction);
  pros::delay(BRAKE_TIME);
  //set drive back to neutral
  setDrive(0,0);
}

void rotate(int degrees) {
  int dir = abs(degrees)/degrees;

  resetDriveEncoders();

  while(fabs(ticksToDegrees(avgDriveEncoderValue())) < abs(degrees))
  {
    setDrive(maxTurnVoltage*dir, -maxTurnVoltage*dir);
    pros::delay(10);
  }

  //brief brake
  setDrive(-10 * dir, 10 * dir);
  pros::delay(BRAKE_TIME);
  //set drive back to neutral
  setDrive(0,0);

}

void arcPID(double r_inches, double degrees) {
  double left_inches = (degrees * M_PI / 180) * (r_inches + CHASSIS_WIDTH/2);
  double right_inches = (degrees * M_PI / 180) * (r_inches - CHASSIS_WIDTH/2);
  resetPIDVars(left_inches*TICKS_PER_INCH, right_inches*TICKS_PER_INCH);

  int depth = 3;
  int maxError = 10;

  while (errorCheck(depth, maxError)) {
    leftPos = leftDriveEncoderValue();
    rightPos = rightDriveEncoderValue();
    leftError = leftTarget - leftPos;
    rightError = rightTarget - rightPos;
    leftDerivative = leftPrevErrors.at(leftPrevErrors.size()-1) - leftError;
    rightDerivative = rightPrevErrors.at(rightPrevErrors.size()-1) - rightError;
    leftIntegral += leftError;
    rightIntegral += rightError;
    leftPrevErrors.push_back(leftError);
    rightPrevErrors.push_back(rightError);

    leftPower = ARC_KP * leftError + ARC_KI * leftIntegral + ARC_KD * leftDerivative;
    if (leftPower > maxArcVoltage) {
      leftPower = maxArcVoltage;
    } else if (-leftPower > maxArcVoltage) {
      leftPower = -maxArcVoltage;
    }
    rightPower = ARC_KP * rightError + ARC_KI * rightIntegral + ARC_KD * rightDerivative;
    if (rightPower > maxArcVoltage) {
      rightPower = maxArcVoltage;
    } else if (-rightPower > maxArcVoltage) {
      rightPower = -maxArcVoltage;
    }
    setDrive(leftPower, rightPower);
    // controller.clear();
    controller.set_text(0, 1, "ARC: " + std::to_string((int)(leftPower)) + " | " + std::to_string((int)(rightPower)));
    pros::lcd::set_text(1, "Left_E: " + std::to_string((int)(leftError)));
    pros::lcd::set_text(2, "Right_E: " + std::to_string((int)(rightError)));

    pros::delay(10);
  }

  setDrive(0,0);
  pros::delay(BRAKE_TIME);
  //set drive back to neutral
  setDrive(0,0);
}

void turnPID(double degrees) {
  resetPIDVars(degrees*TICKS_PER_DEGREE, -degrees*TICKS_PER_DEGREE);

  int depth = 3;
  int maxError = 10;

  while (errorCheck(depth, maxError)) {
    leftPos = leftDriveEncoderValue();
    rightPos = rightDriveEncoderValue();
    leftError = leftTarget - leftPos;
    rightError = rightTarget - rightPos;
    leftDerivative = leftPrevErrors.at(leftPrevErrors.size()-1) - leftError;
    rightDerivative = rightPrevErrors.at(rightPrevErrors.size()-1) - rightError;
    leftIntegral += leftError;
    rightIntegral += rightError;
    leftPrevErrors.push_back(leftError);
    rightPrevErrors.push_back(rightError);

    leftPower = TURN_KP * leftError + TURN_KI * leftIntegral + TURN_KD * leftDerivative;
    if (leftPower > maxTurnVoltage) {
      leftPower = maxTurnVoltage;
    } else if (-leftPower > maxTurnVoltage) {
      leftPower = -maxTurnVoltage;
    }
    rightPower = TURN_KP * rightError + TURN_KI * rightIntegral + TURN_KD * rightDerivative;
    if (rightPower > maxTurnVoltage) {
      rightPower = maxTurnVoltage;
    } else if (-rightPower > maxTurnVoltage) {
      rightPower = -maxTurnVoltage;
    }
    setDrive(leftPower, rightPower);
    // controller.clear();
    controller.set_text(0, 1, "TRN: " + std::to_string((int)(leftPower)) + " | " + std::to_string((int)(rightPower)));
    pros::lcd::set_text(1, "Left_E: " + std::to_string((int)(leftError)));
    pros::lcd::set_text(2, "Right_E: " + std::to_string((int)(rightError)));

    pros::delay(10);
  }

  setDrive(0,0);
  pros::delay(BRAKE_TIME);
  //set drive back to neutral
  setDrive(0,0);
}

void straightPID(double inches) {
  resetPIDVars(inches*TICKS_PER_INCH, inches*TICKS_PER_INCH);

  int depth = 3;
  int maxError = 10;

  while (errorCheck(depth, maxError)) {
    leftPos = leftDriveEncoderValue();
    rightPos = rightDriveEncoderValue();
    leftError = leftTarget - leftPos;
    rightError = rightTarget - rightPos;
    leftDerivative = leftPrevErrors.at(leftPrevErrors.size()-1) - leftError;
    rightDerivative = rightPrevErrors.at(rightPrevErrors.size()-1) - rightError;
    leftIntegral += leftError;
    rightIntegral += rightError;
    leftPrevErrors.push_back(leftError);
    rightPrevErrors.push_back(rightError);

    leftPower = STRAIGHT_KP * leftError + STRAIGHT_KI * leftIntegral + STRAIGHT_KD * leftDerivative;
    if (leftPower > maxStraightVoltage) {
      leftPower = maxStraightVoltage;
    } else if (-leftPower > maxStraightVoltage) {
      leftPower = -maxStraightVoltage;
    }
    rightPower = STRAIGHT_KP * rightError + STRAIGHT_KI * rightIntegral + STRAIGHT_KD * rightDerivative;
    if (rightPower > maxStraightVoltage) {
      rightPower = maxStraightVoltage;
    } else if (-rightPower > maxStraightVoltage) {
      rightPower = -maxStraightVoltage;
    }
    setDrive(leftPower, rightPower);
    // controller.clear();
    controller.set_text(0, 1, "STR: " + std::to_string((int)(leftPower)) + " | " + std::to_string((int)(rightPower)));
    pros::lcd::set_text(1, "Left_E: " + std::to_string((int)(leftError)));
    pros::lcd::set_text(2, "Right_E: " + std::to_string((int)(rightError)));

    pros::delay(10);
  }

  setDrive(0,0);
  pros::delay(BRAKE_TIME);
  //set drive back to neutral
  setDrive(0,0);
}
