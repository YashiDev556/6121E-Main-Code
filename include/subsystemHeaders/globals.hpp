#include "main.h"


//MOTORS
//drive

extern pros::Motor driveLeftBack;
extern pros::Motor driveLeftFront;
extern pros::Motor driveRightBack;
extern pros::Motor driveRightFront;

//mogo
extern pros::Motor mogo;


extern pros::Motor intake;
extern pros::Motor lift;

//claw
extern pros::Motor claw;

//CONTROLLER
extern  pros::Controller controller;



//MISCELLANEOUS

extern pros::Imu imu_sensor;

#define clampPneumatics 'A'
