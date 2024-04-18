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
  // Left Joystick controls robot position (up = up, down = down, left = left, right = right)
  // Right Joystick controls robot absolute orientation. (up = forward, down = backward, etc...)

  // Get inputs
  float forward_backward_axis_value = (float)Controller1.Axis3.position();
  float left_right_axis_value = (float)Controller1.Axis4.position();
  float turning_x_axis_value = (float)Controller1.Axis1.position();
  float turning_y_axis_value = (float)Controller1.Axis2.position();

  // Deadband --> Ignore really small values
  forward_backward_axis_value = (std::abs(forward_backward_axis_value) > drive_deadband ? forward_backward_axis_value : 0 );
  left_right_axis_value = (std::abs(left_right_axis_value) > drive_deadband ? left_right_axis_value : 0 );
  turning_x_axis_value = (std::abs(turning_x_axis_value) > turning_deadband ? turning_x_axis_value : 0 );
  turning_y_axis_value = (std::abs(turning_y_axis_value) > turning_deadband ? turning_y_axis_value : 0 );

  // Multiply the inputs by the speed in settings
  forward_backward_axis_value *= movement_speed_multiplier;
  left_right_axis_value *= movement_speed_multiplier;

  // Default Motor Velocities
  float left_motor_velocity = 0;
  float right_motor_velocity = 0;
  float strafe_motor_velocity = 0;

  // Get robot heading from Inertia Sensor
  float robot_heading_degrees = InertialSensor.heading(degrees);

  // Convert to radians
  double robot_heading_radians = robot_heading_degrees * (M_PI / 180);

  Brain.Screen.newLine();
  Brain.Screen.print(robot_heading_degrees);


  // Movement
  left_motor_velocity += forward_backward_axis_value * cos(robot_heading_radians) + left_right_axis_value * sin(robot_heading_radians);
  right_motor_velocity += forward_backward_axis_value * cos(robot_heading_radians) + left_right_axis_value * sin(robot_heading_radians);
  strafe_motor_velocity += left_right_axis_value * cos(robot_heading_radians) - forward_backward_axis_value * sin(robot_heading_radians);


  // Turning to align to joystick.
  // Convert turning axis values into radians. Axis values are in [-100, 100] and radians are in [-2pi, 2pi]
  double target_x_radians = (turning_x_axis_value / 50) * M_PI;
  double target_y_radians = (turning_y_axis_value / 50) * M_PI;

  // Calculate target heading
  double target_heading_radians = atan(target_y_radians, target_x_radians);

  // Orient target heading to be up = 0. Subtract 1/2 pi.
  target_heading_radians -= 0.5 * M_PI;

  print(target_heading_radians * (180 / M_PI));

  // Calculate heading error
  float heading_error_radians = target_heading_radians - robot_heading_radians;

  // Determine if heading error is big enough to act
  if (std::abs(heading_error_radians) > robot_heading_correction_deadband_radians)
  {
    // Multiply error by speed in settings
    float turning_value = turning_speed_multiplier * heading_error_radians; 

    // left_motor_velocity += turning_value;
    // right_motor_velocity -= turning_value;
  }

  // left_motor_velocity = 0;
  // right_motor_velocity = 0;
  // strafe_motor_velocity = 0;

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