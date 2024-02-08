#include "settings-config.h"

// Deadband stops the motors when Axis values are close to zero.
const int drive_deadband = 5;
const int turning_deadband = 5;
const int strafe_deadband = 10;

// Robot Alignment To Triball
const float triball_adjustment_speed = 30;
const float triball_alignment_minimum_distance = 5;
const float triball_alignment_maximum_distance = 6;

// Speed of the movement of the robot (not strafing)
const float movement_speed_multiplier = 1;

// Speed of the turning of the robot
const float turning_speed_multiplier = 0.5;

// Speed of the strafe movement of the robot
const float strafe_speed_multiplier = 0.7;

// Speed of the arm going up and down.
const float arm_speed_multiplier = 25;

// Speed of the puller mechanism
const float puller_speed_multiplier = 50;

// Speed of the treads
const float treads_speed_multiplier = 50;