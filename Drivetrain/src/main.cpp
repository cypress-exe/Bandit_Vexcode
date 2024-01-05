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

    // Controller Functions
    ControllerFunctions::update();
  }
}