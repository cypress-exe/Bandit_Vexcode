#include <cmath>

#include "vex.h"
#include "settings-config.h"
#include "overrides.h"

#include "controller-movement.h"

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
  if (std::abs(drive_axis_value) > deadband) {
    left_motor_velocity += drive_axis_value;
    right_motor_velocity += drive_axis_value;
  }


  if (std::abs(turning_axis_value) > deadband) {
    left_motor_velocity += turning_axis_value;
    right_motor_velocity -= turning_axis_value;
  }

  if (std::abs(strafe_axis_value) > deadband) {
    strafe_motor_velocity += strafe_axis_value;
  }


  // Update the motors to be the computed velocity
  LeftMotor.setVelocity(left_motor_velocity, percent);
  RightMotor.setVelocity(right_motor_velocity, percent);
  StrafeMotor.setVelocity(strafe_motor_velocity, percent);


  // Spin the motors in the forward direction.
  LeftMotor.spin(forward);
  RightMotor.spin(forward);
  StrafeMotor.spin(forward);
}

void ControllerMovement::updateArmMotors(){
  if (arm_overrided) return;

  // Get inputs
  bool raise_arm = Controller1.ButtonR1.pressing();
  bool lower_arm = Controller1.ButtonL1.pressing();

  bool puller_in = Controller1.ButtonDown.pressing();
  bool puller_out = Controller1.ButtonUp.pressing();

  // Create Variables
  float arm_velocity = 0;
  float puller_velocity = 0;

  // Logic
  // Edit the variables to be 1, 0, or -1

  if (raise_arm) arm_velocity += 1;
  if (lower_arm) arm_velocity += -1;

  if (puller_in) puller_velocity += 1;
  if (puller_out) puller_velocity += -1;

  // Multiply the speed by the speed in settings
  arm_velocity *= arm_speed_multiplier;
  puller_velocity *= puller_speed_multiplier;

  // Update the motors to be the computed velocity
  ArmMotors.setVelocity(arm_velocity, percent);
  PullerMotor.setVelocity(puller_velocity, percent);


  // Spin the motors in the forward direction.
  ArmMotors.spin(forward);
  PullerMotor.spin(forward);
}

void ControllerMovement::updateLaunchingMotors(){
  // Get inputs
  bool treads_in = Controller1.ButtonB.pressing();
  bool treads_out = Controller1.ButtonX.pressing();

  // Create Variables
  float treads_velocity = 0;

  // Logic
  // Edit the variables to be 1, 0, or -1

  if (treads_in) treads_velocity += 1;
  if (treads_out) treads_velocity += -1;

  // Multiply the speed by the speed in settings
  treads_velocity *= treads_speed_multiplier;

  // Update the motors to be the computed velocity
  TreadsMotor.setVelocity(treads_velocity, percent);

  // Spin the motors in the forward direction.
  TreadsMotor.spin(forward);
}
