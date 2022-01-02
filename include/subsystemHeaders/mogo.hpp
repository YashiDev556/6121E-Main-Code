#include "main.h"

//HELPER FUNCTIONS
void initMogo();
double mogoEncoderValue();



//LIFT FUNCTIONS
void setMogo(int power);
void setMogoMotors();
void setMogoAngle(double degrees);

//MULTITASKING FUNCTIONS
void setMogoTask(int id, double p1=0, double p2=0);
void autonMogoTask(void *);
