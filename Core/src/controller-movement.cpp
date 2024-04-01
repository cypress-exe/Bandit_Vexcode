#include <cmath>

#include "vex.h"
#include "settings-config.h"
#include "overrides.h"

#include "controller-movement.h"

void ControllerMovement::initDriveMotors(){
  // setup the callbacks...
  Controller1.Axis1.changed(updateDriveMotors);
  Controller1.Axis3.changed(updateDriveMotors);
  Controller1.Axis4.changed(updateDriveMotors);
}

void ControllerMovement::initArmMotors(){
  // setup the callbacks...
  Controller1.ButtonL1.pressed(updateArmMotors);
  Controller1.ButtonR1.pressed(updateArmMotors);
  Controller1.ButtonDown.pressed(updateArmMotors);
  Controller1.ButtonUp.pressed(updateArmMotors);

  Controller1.ButtonL1.released(updateArmMotors);
  Controller1.ButtonR1.released(updateArmMotors);
  Controller1.ButtonDown.released(updateArmMotors);
  Controller1.ButtonUp.released(updateArmMotors);

  // Update the motors to be the computed velocity
  ArmMotors.setVelocity(arm_speed, percent);
  NetMotor.setVelocity(net_speed, percent);
}

void ControllerMovement::initBeltMotor(){
  // setup the callbacks...
  Controller1.ButtonLeft.pressed(updateBeltMotor);
  Controller1.ButtonRight.pressed(updateBeltMotor);

  Controller1.ButtonLeft.released(updateBeltMotor);
  Controller1.ButtonRight.released(updateBeltMotor);

  // Update the motors to be the computed velocity
  BeltMotor.setVelocity(belt_speed, percent);
}

void ControllerMovement::updateDriveMotors(){
  // Left Up and Down is ROBOT Forward and Back (3)
  // Right Right and Left is ROBOT Turning (1)
  // Left Right and Left is ROBOT Strafe (4)

  // Get inputs
  float drive_axis_value = (float)Controller1.Axis3.position();
  float turning_axis_value = (float)Controller1.Axis1.position();
  float strafe_axis_value = (float)Controller1.Axis4.position();

  // Create variables
  float left_motor_velocity = 0;
  float right_motor_velocity = 0;
  float strafe_motor_velocity = 0;

  // Multiply the inputs by the speed in settings
  drive_axis_value *= movement_speed_multiplier;
  turning_axis_value *= turning_speed_multiplier;
  strafe_axis_value *= strafe_speed_multiplier;


  // Set the speed of the motor only if the value is more than the deadband.

  // Movement Logic
  if (std::abs(drive_axis_value) > drive_deadband) {
    left_motor_velocity += drive_axis_value;
    right_motor_velocity += drive_axis_value;
  }

  if (std::abs(turning_axis_value) > turning_deadband) {
    left_motor_velocity += turning_axis_value;
    right_motor_velocity -= turning_axis_value;
  }

  if ((std::abs(strafe_axis_value) > strafe_deadband) && (!strafe_motor_overriden)) {
    strafe_motor_velocity += strafe_axis_value;
  }

  // Update the motors to be the computed velocity
  LeftDriveMotor.setVelocity(left_motor_velocity, percent);
  RightDriveMotor.setVelocity(right_motor_velocity, percent);
  StrafeMotor.setVelocity(strafe_motor_velocity, percent);


  // Spin the motors in the forward direction.
  LeftDriveMotor.spin(forward);
  RightDriveMotor.spin(forward);
  StrafeMotor.spin(forward);
}

void ControllerMovement::updateArmMotors(){
  if (triball_manipulating) return;

  // Get inputs
  bool raise_arm = Controller1.ButtonR1.pressing();
  bool lower_arm = Controller1.ButtonL1.pressing();

  bool net_down = Controller1.ButtonDown.pressing();
  bool net_up = Controller1.ButtonUp.pressing();

  // Create Variables
  int arm_velocity = 0;
  int net_velocity = 0;

  // Logic
  // Edit the variables to be 1, 0, or -1

  if (raise_arm) arm_velocity += 1;
  if (lower_arm) arm_velocity += -1;

  if (net_down) net_velocity += 1;
  if (net_up) net_velocity += -1;

  // Update the motors to reflect the variables
  switch (arm_velocity) {
    case 1:
      ArmMotors.spin(forward);
      break;
    case 0:
      ArmMotors.stop();
      break;
    case -1:
      ArmMotors.spin(reverse);
      break;
  }

  switch (net_velocity) {
    case 1:
      NetMotor.spin(forward);
      break;
    case 0:
      NetMotor.stop();
      break;
    case -1:
      NetMotor.spin(reverse);
      break;
  }
}

void ControllerMovement::updateBeltMotor(){
  if (triball_manipulating) return;
  
  // Get inputs
  bool belt_in = Controller1.ButtonLeft.pressing();
  bool belt_out = Controller1.ButtonRight.pressing();

  // Create Variables
  int belt_velocity = 0;

  // Logic
  // Edit the variables to be 1, 0, or -1

  if (belt_in) belt_velocity += 1;
  if (belt_out) belt_velocity += -1;

  // Update the motors to reflect the variables
  switch (belt_velocity) {
    case 1:
      BeltMotor.spin(forward);
      break;
    case 0:
      BeltMotor.stop();
      break;
    case -1:
      BeltMotor.spin(reverse);
      break;
  }
}