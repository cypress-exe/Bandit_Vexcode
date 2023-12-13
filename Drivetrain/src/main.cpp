/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Wed Sep 25 2019                                           */
/*    Description:  Tank Drive                                                */
/*    This sample allows you to control the V5 Clawbot using the both         */
/*    joystick. Adjust the deadband value for more accurate movements.        */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller
// LeftMotor            motor         1
// RightMotor           motor         10
// ClawMotor            motor         3
// ArmMotor             motor         8
// ---- END VEXCODE CONFIGURED DEVICES ----

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


  // Spin both motors in the forward direction.
  LeftMotor.spin(forward);
  RightMotor.spin(forward);
}


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  while(true){
    updateDriveMotors();    
  }
}
