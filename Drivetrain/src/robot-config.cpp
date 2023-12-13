#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

// VEXcode device constructors

// Local Motors
motor ArmMotorLeft = motor(PORT7, ratio18_1, false);
motor ArmMotorRight = motor(PORT8, ratio18_1, true);

// Global Motors
controller Controller1 = controller(primary);
motor LeftMotor = motor(PORT1, ratio18_1, false);
motor RightMotor = motor(PORT10, ratio18_1, true);
motor StrafeMotor = motor(PORT3, ratio18_1, false);
motor ClawMotor = motor(PORT3, ratio18_1, false);
motor_group ArmMotors = motor_group(ArmMotorLeft, ArmMotorRight);

// VEXcode generated functions

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // nothing to initialize
}