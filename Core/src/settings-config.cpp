#include "settings-config.h"

// Deadband stops the motors when Axis values are close to zero.
const int drive_deadband = 5;
const int turning_deadband = 5;
const float robot_heading_correction_deadband_radians = 0.08; // Almost 5 degrees

// Robot Alignment To Triball
const float triball_adjustment_speed = 15;
const float triball_alignment_minimum_distance = 5;
const float triball_alignment_maximum_distance = 6;

// Speed of the movement of the robot
const float movement_speed_multiplier = 1;

// Speed of the turning of the robot
const float turning_speed_multiplier = 0.5;

// Speed of the arm going up and down.
const float arm_speed = 25;

// Speed of the net mechanism
const float net_speed = 25;

// Speed of the belt
const float belt_speed = 50;