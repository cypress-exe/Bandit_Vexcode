#include "settings-config.h"

// Deadband stops the motors when Axis values are close to zero.
const int deadband = 5;

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