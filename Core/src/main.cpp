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

  // while (true){
  //   //float robot_heading_degrees = InertialSensor.gyroRate(vex::axisType::zaxis, vex::velocityUnits::dps);

  //   double robot_heading_degrees = InertialSensor.heading(degrees);

  //   Brain.Screen.clearScreen();
  //   Brain.Screen.clearLine();
  //   Brain.Screen.print(robot_heading_degrees);

  //   wait(100, msec);
  // }
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