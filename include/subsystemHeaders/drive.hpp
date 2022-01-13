#include "main.h"

//HELPER FUNCTIONS
void setDrive(int left, int right);
void reverseDriveMotors();

void resetDriveEncoders();
void resetPIDVars();

double avgDriveEncoderValue();
double leftDriveEncoderValue();
double rightDriveEncoderValue();

void setDriveTask(int id, double p1=0, double p2=0);
void autonDriveTask(void *);

bool errorCheck(int d, int max);

//Conversions
double degreesToTicks(double degrees);
double ticksToDegrees(double ticks);
double inchesToTicks(double inches);
double ticksToInches(double ticks);


//DRIVER CONTROL FUNCTIONS
void setDriveMotors();

//AUTONOMOUS CONTROL FUNCTIONS
void translate(double units, int voltage);
void rotate(int degrees);
void straightPID(double inches);
void turnPID(double degrees);
void arcPID(double r_inches, double degrees);
void straightTrap(double inches);
