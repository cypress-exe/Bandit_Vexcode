#include "vex.h"

#include "controller-movement.h"
#include "controller-functions.h"


using namespace vex;

competition Competition;

void autonomous(void){

}

void drivercontrol(void){
  while(true){
    // Controller Movement
    ControllerMovement::updateDriveMotors();
    ControllerMovement::updateArmMotors();
    ControllerMovement::updateBeltMotor();
    
    // Controller Functions
    ControllerFunctions::update();
    // ControllerFunctions::alignRobotToTriball();
  }
}

int main() {
  // Set up callbacks for autonomous and driver control periods
  Competition.autonomous(autonomous);
  Competition.drivercontrol(drivercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  drivercontrol();

  // Main Loop
  // Nothing happens without it being called directly or indirectly through this loop
}