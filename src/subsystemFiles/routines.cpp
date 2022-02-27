#include "main.h"


void leftWinPoint()
{
  liftAuton(1800, 80);

  straightTrap(5.0, 800);

  pros::delay(1000);

  liftAuton(-400, 80);

  straightTrap(-5.0, 800);
}


void leftRush()
{
  straightTrap(16.5, 100);
  clawAuton(-360, 100);
  straightTrap(-14, 100);
}

void rightWinPoint()
{

  liftAuton(1800, 80);
  straightTrap(3.0, 400);

  turnTrap(3.40);

  straightTrap(4.5, 1000);

  clawAuton(400, 100);

  straightTrap(-3.0, 400);

  liftAuton(-1800, 80);

  straightTrap(6.0, 1000);

  clawAuton(-400, 100);

  straightTrap(-6.0, 400);

}

void rightRush()
{
  straightTrap(12.5, 200);
  pros::delay(200);
  clawAuton(400, 80);
  straightTrap(-9.5,100); //back up

  clawAuton(-400, 100);

  straightTrap(-3.0, 200);

  //Win Point Scoring

  // turnTrap(3.20);

  // liftAuton(1480, 120);

  // straightTrap(6.0, 600);

  // clawAuton(440, 120);

  // pros::delay(1000);

  // straightTrap(-3.0, 200);

  // liftAuton(-1480, 120);

  // clawAuton(-400, 120);

  // straightTrap(6.5, 800);

  // clawAuton(400, 100);

  // straightTrap(-7.0, 200);

}


//supposed to be a 40 point routine for use in skills

void skillsAuton()
{

  mogoAuton(-2200, 120);
  straightTrap(-4.0, 200);

  mogoAuton(1700, 126); //previous was 1700

  straightTrap(3.6, 200);

  pros::delay(1000);

  turnTrap(7.30);

  pros::delay(1000);

  //straightTrap(15, 200);

  pros::delay(1000);


  //clawAuton(-400, 100);

  //liftAuton(1000, 100);

  turnTrap(1.0);

  straightTrap(16, 600);

  pros::delay(1000);


  straightTrap(24, 600);






}
