#pragma once

using namespace vex;

extern brain Brain;

// VEXcode devices
extern inertial InertialSensor;
extern distance LeftDistanceSensor;
extern distance RightDistanceSensor;

extern controller Controller1;
extern motor LeftDriveMotor;
extern motor RightDriveMotor;
extern smartdrive Drivetrain;
extern motor StrafeMotor;
extern motor_group ArmMotors;
extern motor FlipperMotor;
extern motor BeltMotor;


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void pre_auton(void);