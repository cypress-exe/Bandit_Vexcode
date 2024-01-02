#include "vex.h"
#include "settings-config.h"

#include "controller-movement.h"

void ControllerMovement::updateDriveMotors(){
  // Left Up and Down is ROBOT Forward and Back (3)
  // Right Right and Left is ROBOT Turning (1)
  // Left Right and Left is ROBOT Strafe (4)

  // Get inputs
  int drive_axis_value = Controller1.Axis3.position();
  int turning_axis_value = Controller1.Axis1.position();
  int stafe_axis_value = Controller1.Axis4.position();

  // Create variables
  int left_motor_velocity = 0;
  int right_motor_velocity = 0;
  int strafe_motor_velocity = 0;


  // Set the speed of the motor only if the value is more than the deadband.

  // Movement Logic
  if (abs(drive_axis_value) > deadband) {
    left_motor_velocity += drive_axis_value;
    right_motor_velocity += drive_axis_value;
  }

  if (abs(turning_axis_value) > deadband) {
    // Decide the direction in which we are turning.
    // Turn right if the value is positive, left if the value is negative.
    if (turning_axis_value > 0){
      // Turn right
      left_motor_velocity += turning_axis_value;
      right_motor_velocity -= turning_axis_value;
    } else {
      // Turn left
      left_motor_velocity -= turning_axis_value;
      right_motor_velocity += turning_axis_value;
    }
  }

  if (abs(stafe_axis_value) > deadband) {
    strafe_motor_velocity += stafe_axis_value;
  }

  // Multiply the speed by the speed in settings
  left_motor_velocity *= movement_speed_multiplier;
  right_motor_velocity *= movement_speed_multiplier;
  strafe_motor_velocity += strafe_speed_multiplier;

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
  // Raise / Lower the arm with the left buttons on the top of the controller (L1, L2)
  // Puller in / Puller out triball with the right buttons on the top of the controller (R1, R2)

  // Get inputs
  bool raise_arm = Controller1.ButtonL1.PRESSED;
  bool lower_arm = Controller1.ButtonL2.PRESSED;

  bool puller_in = Controller1.ButtonR1.PRESSED;
  bool puller_out = Controller1.ButtonR2.PRESSED;

  // Create Variables
  int arm_velocity = 0;
  int puller_velocity = 0;

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
