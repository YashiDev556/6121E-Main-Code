#include "main.h"


const double ratio = 7.0;

//lift functions
void setMogo(int power) {
  mogoLeft = power;
  mogoRight = power;
}

void setMogoMotors() {

  //bottom puts down, upper picks up
  int mogoPower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1));
  setMogo(mogoPower);

}

void initMogo() {
  mogoLeft.tare_position();
  mogoRight.tare_position();


}

double mogoEncoderValue() {
  return mogoLeft.get_position();
}

void setMogoAngle(double deg) {
  double target = 900 * (90 - deg) / 360;
  int dir = fabs(mogoEncoderValue() - target) / (target - mogoEncoderValue());

  const int mV = 127;

  if (dir > 0) {
    while (mogoEncoderValue() <= target) {
      setMogo(mV);
      pros::delay(10);
    }

    setMogo(-10);
    pros::delay(20);
    setMogo(0);

  } else if (dir < 0) {
    while (mogoEncoderValue() >= target) {
      setMogo(-mV);
      pros::delay(10);
    }

    setMogo(10);
    pros::delay(20);
    setMogo(0);

  }

}
