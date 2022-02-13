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
  straightTrap(14.5, 400);

  clawAuton(390, 60);

  straightTrap(-11, 200);

  clawAuton(-390, 100);

  straightTrap(-3.0, 200);

  turnTrap(4.2);

  liftAuton(1480, 80);

  straightTrap(4.0, 600);

  clawAuton(440, 120);

  straightTrap(-3.0, 200);
}

void rightWinPoint()
{
  
  liftAuton(1800, 80);
  straightTrap(3.0, 400);
  
  turnTrap(3.40);
  
  straightTrap(4.5, 400);

  liftAuton(-400, 80);

  straightTrap(-3.0, 400);

  liftAuton(-1400, 80);

  straightTrap(5.0, 400);

  clawAuton(400, 100);

  straightTrap(-8.0, 400);

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




void skillsAuton()
{
  straightTrap(4.0, 600);

  clawAuton(400, 100);

  straightTrap(-4.0, 600);

  clawAuton(-400, 100);

  straightTrap(-1.5, 200);

  turnTrap(-4.0);

  straightTrap(14.5, 600);

  clawAuton(400, 100);



  liftAuton(400, 80);

  clawAuton(40, 100);

  liftAuton(400, 100);

  clawAuton(40, 100);

  liftAuton(800, 80);
}




