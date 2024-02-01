#pragma once

using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor LeftDriveMotor;
extern motor RightDriveMotor;
// extern smartdrive Drivetrain;
extern motor StrafeMotor;
extern motor_group ArmMotors;
extern motor PullerMotor;
extern motor TreadsMotor;

// extern inertial InertialSensor;
extern distance LeftDistanceSensor;
extern distance RightDistanceSensor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);