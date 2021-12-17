#include "main.h"

// //robot measurements
// const static double WHEEL_DIAMETER = 4.125;
// const static double GEAR_RATIO = 36.0 / 60.0;
// const static double TICKS_PER_INCH = 900.0 / (M_PI * WHEEL_DIAMETER * GEAR_RATIO); //900 ticks per revolution
//
// const static double CHASSIS_WIDTH = 12.0; //lenght from wheel to wheel on opposite side
// const static double TICKS_PER_DEGREE = (2.5 * CHASSIS_WIDTH) / (WHEEL_DIAMETER * GEAR_RATIO); //only for turning not arc
//
//
// //field measurement constants
// const static double GOAL_RUSH = 67.5;


/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_right_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "This is an example of auton selection....");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Team_6121E - Project: Bleeding Edge");

	controller.clear();

//pros::lcd::register_btn0_cb(on_right_button); means left button
//pros::lcd::register_btn1_cb(on_right_button); means center button
//pros::lcd::register_btn2_cb(on_right_button); means right button

	pros::lcd::register_btn2_cb(on_right_button);

	driveLeftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	driveLeftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	driveRightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	driveRightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);



	//make sure to delete or comment out this "autonomous()" line during competition
	//also make sure to add gyro functionality

	autonomous();





}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */

 //basically the competition initialize function is for an autonomous selector
 //probably can do this with the bumper switches or software buttons

void competition_initialize() {




}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */





void autonomous() {

	//redLeftCorner();
	//redRightCorner();
	//blueLeftCorner();
	//blueRightCorner();

	driveTest();

}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	//controller.clear();
	// controller.set_text(1, 4, "-D-----DRIVE------");
	while(true)
	{

		//control the drive
		setDriveMotors();

		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
			reverseDriveMotors();
		}
		//control mogo lift
		// setMogoMotors();
		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			setMogoAngle(45);

		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			setMogoAngle(0);
		}

		//control lift
		pros::delay(10);
	}


}
