#include "cmath"
#include <thread>

#include "vex.h"

#include "overrides.h"
#include "controller-functions.h"
#include "settings-config.h"

using namespace vex;

// Called every update frame
void ControllerFunctions::init()
{
    // Setup callbacks
    Controller1.ButtonR2.pressed(intakeTriball);
    Controller1.ButtonL2.pressed(releaseTriball);
    Controller1.ButtonA.pressed(launch);
}


void ControllerFunctions::intakeTriball()
{
    if (!triball_manipulating) thread t1(intakeTriball_thread);
}

void ControllerFunctions::releaseTriball()
{
    if (!triball_manipulating) thread t1(releaseTriball_thread);
}

void ControllerFunctions::launch()
{
    if (!triball_manipulating) thread t1(launch_thread);   
}

void ControllerFunctions::intakeTriball_thread()
{
    // Stop all other processes from messing with the arm
    triball_manipulating = true;

    // Start the Belt
    BeltMotor.spin(forward);

    // Bring the net down & arm up
    NetMotor.spinFor(forward, 430, degrees, false);
    ArmMotors.spinFor(forward, 205, degrees, false);

    // Wait for 1 second
    wait(1500, msec);
    
    // Stop the belt
    BeltMotor.stop();

    // Resume other processes
    triball_manipulating = false;
}

void ControllerFunctions::releaseTriball_thread()
{
    // Stop all other processes from messing with the arm
    triball_manipulating = true;

    // Bring the net up
    NetMotor.spinFor(reverse, 430, degrees, false);

    // Start the Belt
    BeltMotor.spin(reverse);

    // Wait for 1 second
    wait(1, seconds);
    
    // Stop the belt
    BeltMotor.stop();

    // Put the arm down again
    ArmMotors.spinFor(reverse, 205, degrees, false);

    // Resume other processes
    triball_manipulating = false;
}


void ControllerFunctions::launch_thread()
{
    // Stop all other processes from messing with the arm
    triball_manipulating = true;

    // Configure arm speed to be quicker
    ArmMotors.setVelocity(100, percent);

    // Move net
    NetMotor.spinFor(forward, 50, degrees, false);

    // Move arm
    ArmMotors.spinFor(forward, 400, degrees, true);

    // Reset speed
    ArmMotors.setVelocity(arm_speed, percent);

    // Resume other processes
    triball_manipulating = false;
}