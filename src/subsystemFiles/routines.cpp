#include "main.h"


void autonChoice(void *parameter) {
  multiTest();
}

void multiTest() {
  setDriveTask(4, 12.0);
  pros::delay(20);
  setMogoTask(1, 45.0);
  pros::delay(1500);
  setDriveTask(5, -90);
  pros::delay(1000);
  setDriveTask(4, -18.0);
  setMogoTask(1, 15.0);
  pros::delay(1000);
  setMogoTask(1, 90);
  pros::delay(20000);

  setMogoTask(0);
  setDriveTask(0);
}

void driveTest() {
  straightPID(26.0);
  turnPID(-90.0);
  straightPID(24.0);
  turnPID(-180.0);
  //arcPID(12.0, 135.0);
  //arcPID(-9.0, -135.0);
  //turnPID(-180.0);
  //straightPID(-24.0);
}

void redLeftCorner()
{

}

void redRightCorner()
{

}

void blueLeftCorner()
{

}

void blueRightCorner()
{

}
