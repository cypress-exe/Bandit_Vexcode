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
  // ControllerFunctions::intakeTriball_thread();
  // Drivetrain.turnFor(90, degrees);
  // Drivetrain.driveFor(50, mm);
  // ControllerFunctions::releaseTriball_thread();
}

void drivercontrol(void){
  Brain.Screen.clearScreen();
  Brain.Screen.clearLine();
  Brain.Screen.print("Driver Control...");

  while(true){
    // Controller Movement
    ControllerMovement::updateDriveMotors();
    ControllerMovement::updateArmMotors();
    ControllerMovement::updateBeltMotor();
    
    // Controller Functions
    ControllerFunctions::update();
  }
}

int main() {
  // Set up callbacks for autonomous and driver control periods
  Competition.autonomous(autonomous);
  Competition.drivercontrol(drivercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Main Loop
  // Nothing happens without it being called directly or indirectly through this loop
}