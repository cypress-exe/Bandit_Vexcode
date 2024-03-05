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

void ControllerFunctions::intakeTriball()
{
    if (!triball_manipulating) thread t2(intakeTriball_thread);
}

void ControllerFunctions::releaseTriball()
{
    if (!triball_manipulating) thread t2(releaseTriball_thread);
}
