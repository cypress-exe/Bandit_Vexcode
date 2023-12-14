#include "vex.h"

using namespace vex;


void updateDriveMotors(){
  // Left Up and Down is ROBOT Forward and Back (3)
  // Right Right and Left is ROBOT Turning (1)
  // Left Right and Left is ROBOT Strafe (4)

  // Get inputs
  int driveAxisValue = Controller1.Axis3.position();
  int turningAxisValue = Controller1.Axis1.position();
  int strafeAxisValue = Controller1.Axis4.position();

  // Create variables
  int leftMotorVelocity = 0;
  int rightMotorVelocity = 0;
  int strafeMotorVelocity = 0;


  // Set the speed of the motor only if the value is more than the deadband.

  // Movement Logic
  if (abs(driveAxisValue) > deadband) {
    leftMotorVelocity += driveAxisValue;
    rightMotorVelocity += driveAxisValue;
  }

  if (abs(turningAxisValue) > deadband) {
    // Decide the direction in which we are turning.
    // Turn right if the value is positive, left if the value is negative.
    if (turningAxisValue > 0){
      // Turn right
      leftMotorVelocity += turningAxisValue;
      rightMotorVelocity -= turningAxisValue;
    } else {
      // Turn left
      leftMotorVelocity -= turningAxisValue;
      rightMotorVelocity += turningAxisValue;
    }
  }

  if (abs(strafeAxisValue) > deadband) {
    strafeMotorVelocity += strafeAxisValue;
  }

  // Update the motors to be the computed velocity
  LeftMotor.setVelocity(leftMotorVelocity, percent);
  RightMotor.setVelocity(rightMotorVelocity, percent);
  StrafeMotor.setVelocity(strafeMotorVelocity, percent);


  // Spin the motors in the forward direction.
  LeftMotor.spin(forward);
  RightMotor.spin(forward);
  StrafeMotor.spin(forward);
}

void updateGrabberMotors(){
  // Raise / Lower the arm with the left buttons on the top of the controller (L1, L2)
  // Puller in / Puller out triball with the right buttons on the top of the controller (R1, R2)

  // Get inputs
  bool raiseArm = Controller1.ButtonL1.PRESSED;
  bool lowerArm = Controller1.ButtonL2.PRESSED;

  bool pullerIn = Controller1.ButtonR1.PRESSED;
  bool pullerOut = Controller1.ButtonR2.PRESSED;

  // Create Variables
  int armVelocity = 0;
  int pullerVelocity = 0;

  // Logic
  // Edit the variables to be 1, 0, or -1

  if (raiseArm) armVelocity += 1;
  if (lowerArm) armVelocity += -1;

  if (pullerIn) pullerVelocity += 1;
  if (pullerOut) pullerVelocity += -1;

  // Multiply the speed by the speed in settings
  armVelocity *= armSpeed;
  pullerVelocity *= pullerSpeed;

  // Update the motors to be the computed velocity
  ArmMotors.setVelocity(armVelocity, percent);
  PullerMotor.setVelocity(pullerVelocity, percent);


  // Spin the motors in the forward direction.
  ArmMotors.spin(forward);
  PullerMotor.spin(forward);
}


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  while(true){
    updateDriveMotors();
    updateGrabberMotors();
  }
}
