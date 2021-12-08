#include "main.h"

//HELPER FUNCTIONS
void setDrive(int left, int right);
void reverseDriveMotors();

void resetDriveEncoders();
void resetPIDVars();

double avgDriveEncoderValue();
double leftDriveEncoderValue();
double rightDriveEncoderValue();

bool errorCheck(int d, int max);

//Conversions
double degreesToTicks(double degrees);
double ticksToDegrees(double ticks);
double inchesToTicks(double inches);
double ticksToInches(double ticks);


//DRIVER CONTROL FUNCTIONS
void setDriveMotors();

//AUTONOMOUS CONTROL FUNCTIONS
void translate(int units, int voltage);
void rotate(int degrees);
void straightPID(double inches);
void turnPID(double degrees);
void arcPID(double r_inches, double degrees);
