#include "settings-config.h"

// Deadband stops the motors when Axis values are close to zero.
const int deadband = 5;

// Speed of the movement of the robot (not strafing)
const int movement_speed_multiplier = 1;

// Speed of the strafe movement of the robot
const int strafe_speed_multiplier = 1;

// Speed of the arm going up and down.
const int arm_speed_multiplier = 1;

// Speed of the puller mechanism
const int puller_speed_multiplier = 1;