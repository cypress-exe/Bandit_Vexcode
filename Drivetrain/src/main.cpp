#include "vex.h"

#include "controller-movement.h"
#include "controller-functions.h"


using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // Main Loop
  // Nothing happens without it being called directly or indirectly through this loop
  while(true){
    // Controller Movement
    ControllerMovement::updateDriveMotors();
    ControllerMovement::updateArmMotors();
    ControllerMovement::updateLaunchingMotors();

    // Brain.Screen.print(LeftDistanceSensor.objectDistance(inches));
    // Brain.Screen.newLine();

    // Controller Functions
    ControllerFunctions::update();
    // ControllerFunctions::alignRobotToTriball();
  }
}