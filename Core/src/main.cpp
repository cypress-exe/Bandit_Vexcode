#include "vex.h"

#include "controller-movement.h"
#include "controller-functions.h"


using namespace vex;

competition Competition;

void autonomous(void){
  Brain.Screen.clearScreen();
  Brain.Screen.clearLine();
  Brain.Screen.print("Autonomous...");

  Drivetrain.driveFor(750, mm);
}

void drivercontrol(void){
  Brain.Screen.clearScreen();
  Brain.Screen.clearLine();
  Brain.Screen.print("Driver Control...");

  // Controller Movement
  ControllerMovement::initDriveMotors();
  ControllerMovement::initArmMotors();
  ControllerMovement::initBeltMotor();
  
  ControllerFunctions::init();
}

int main() {
  // Set up callbacks for autonomous and driver control periods
  Competition.autonomous(autonomous);
  Competition.drivercontrol(drivercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}