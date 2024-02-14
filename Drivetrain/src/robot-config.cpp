#include "vex.h"

#include "robot-config.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

// VEXcode device constructors

// Controller
controller Controller1 = controller(primary);

// Sensors
inertial InertialSensor = inertial(PORT19);
distance LeftDistanceSensor = distance(PORT20);
distance RightDistanceSensor = distance(PORT11);

// Drivetrain calibration
void calibrateDrivetrain() {
  wait(200, msec);
  Brain.Screen.print("Calibrating");
  Brain.Screen.newLine();
  Brain.Screen.print("Inertial Sensor");
  InertialSensor.calibrate();
  while (InertialSensor.isCalibrating()) {
    wait(25, msec);
  }

  // Clears the screen and returns the cursor to row 1, column 1.
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
}

// Local Motors
motor ArmMotorLeft = motor(PORT6, ratio18_1, true);
motor ArmMotorRight = motor(PORT5, ratio18_1, false);

// Global Motors
motor LeftDriveMotor = motor(PORT10, ratio18_1, false);
motor RightDriveMotor = motor(PORT1, ratio18_1, true);
smartdrive Drivetrain = smartdrive(LeftDriveMotor, RightDriveMotor, InertialSensor, 319.19, 320, 40, mm, 1); // magic numbers :)
motor StrafeMotor = motor(PORT9, ratio18_1, true);
motor_group ArmMotors = motor_group(ArmMotorLeft, ArmMotorRight);
motor FlipperMotor = motor(PORT7, ratio18_1, true);
motor BeltMotor = motor(PORT8, ratio18_1, false);

// VEXcode generated functions

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */

void pre_auton(void) {
  // set motors to unique braking setting if applicable
  FlipperMotor.stop(hold);

  calibrateDrivetrain();
}