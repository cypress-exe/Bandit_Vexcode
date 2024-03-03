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
    wait(1, seconds);
    
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


void triangulate_triball_thread()
{
    StrafeMotor.stop(brake);

    // We have to find the sensor to use. It's janky, but we'll use the strafe_motor_override and whether it's positive or negative
    distance sensor = NULL;
    // if (strafe_motor_overriden > 0){
    //     sensor = RightDistanceSensor;
    // } else {
    //     sensor = LeftDistanceSensor;
    // }

    // Stop once the triball is the correct distance away from the sensor.
    int msecs_waiting = 0;
    float triball_distance = 0;
    while(triball_distance < triball_alignment_maximum_distance && msecs_waiting < 500) { // 1/2 second timeout
        // Update Triball Distance
        triball_distance = sensor.objectDistance(inches);
        wait(1, msec);
        msecs_waiting += 1;
    }

    // Stop
    strafe_motor_overriden = 0;
    // Diagnostic Data
    if (msecs_waiting >= 500)
    {
        Brain.Screen.print("Triball Triangulation Failed... Canceled.");
        Brain.Screen.newLine();
    }

    // Reset braking after 1/2 second
    wait(500, msec);
    StrafeMotor.stop(coast);

    strafe_motor_overriden = false;

    Brain.Screen.clearScreen();
    Brain.Screen.clearLine();
}

void ControllerFunctions::triangulateTriball(){
    // Get the info from the distance sensors

    Brain.Screen.print("Triangulating triball... Bypassed...");
    return;

    Brain.Screen.clearScreen();
    Brain.Screen.clearLine();

    Brain.Screen.print("Triangulating triball...");

    float left_distance = LeftDistanceSensor.objectDistance(inches);
    float right_distance = RightDistanceSensor.objectDistance(inches);

    strafe_motor_overriden = true;

    // Check to see if we should correct
    if (left_distance < triball_alignment_minimum_distance)
    {
        // Move left
        StrafeMotor.setVelocity(-triball_adjustment_speed, percent);
        Brain.Screen.print("Triball Alignment: Left");
        Brain.Screen.newLine();
        // thread t1(stopStrafingMotor_thread);

    } else if (right_distance < triball_alignment_minimum_distance)
    {
        // Move right
        StrafeMotor.setVelocity(triball_adjustment_speed, percent);
        Brain.Screen.print("Triball Alignment: Right");
        Brain.Screen.newLine();
        thread t1(triangulate_triball_thread);
    } else 
    {
        Brain.Screen.print("Unable to Locate Triball...");
    }
}