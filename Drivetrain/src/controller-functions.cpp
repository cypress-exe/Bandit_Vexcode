#include "cmath"
#include <thread>

#include "vex.h"

#include "overrides.h"
#include "controller-functions.h"
#include "settings-config.h"

using namespace vex;

// Called every update frame
void ControllerFunctions::update()
{
    // No triball operations if the arm is in use
    if (!tribal_manipulating)
    {
        // Triball Intake
        if(Controller1.ButtonR2.PRESSED)
        {
            intakeTriball();
        }
        // Triball Release
        if(Controller1.ButtonL2.PRESSED)
        {
            releaseTriball();
        }
    }
}

void ControllerFunctions::intakeTriball_thread()
{
    // Stop all other processes from messing with the arm
    tribal_manipulating = true;

    // Raise the arm
    ArmMotors.setVelocity(25, percent);
    BeltMotor.setVelocity(100, percent);
    wait(250, msec);
    ArmMotors.setVelocity(0, percent);

    // Move to triball
    triangulateTriball();

    // Use the flipper to try to grab it
    FlipperMotor.setVelocity(60, percent);
    wait(1000, msec);

    // Bring the arm down a bit
    ArmMotors.setVelocity(-10, percent);
    
    wait(500, msec);
    ArmMotors.setVelocity(0, percent);
    FlipperMotor.setVelocity(0, percent);
    BeltMotor.setVelocity(0, percent);

    // Resume other processes
    tribal_manipulating = false;
}

void ControllerFunctions::releaseTriball_thread()
{
    // Stop all other processes from messing with the arm
    tribal_manipulating = true;

    // Raise the arm
    ArmMotors.setVelocity(25, percent);
    BeltMotor.setVelocity(-100, percent);
    wait(250, msec);
    ArmMotors.setVelocity(0, percent);

    // Use the flipper to try to grab it
    FlipperMotor.setVelocity(-50, percent);
    wait(500, msec);

    // Bring the arm down a bit
    ArmMotors.setVelocity(-10, percent);
    
    wait(500, msec);
    ArmMotors.setVelocity(0, percent);
    FlipperMotor.setVelocity(0, percent);
    BeltMotor.setVelocity(0, percent);

    // Resume other processes
    tribal_manipulating = false;
}

void ControllerFunctions::intakeTriball()
{
    thread t2(intakeTriball_thread);
}

void ControllerFunctions::releaseTriball()
{
    thread t2(releaseTriball_thread);
}

void stopStrafingMotor_thread()
{
    StrafeMotor.stop(brake);

    // We have to find the sensor to use. It's janky, but we'll use the strafe_motor_override and whether it's positive or negative
    distance sensor = NULL;
    if (strafe_motor_override > 0){
        sensor = RightDistanceSensor;
    } else {
        sensor = LeftDistanceSensor;
    }

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
    strafe_motor_override = 0;
    // Diagnostic Data
    if (msecs_waiting >= 500)
    {
        Brain.Screen.print("Triball Triangulation Failed... Canceled.");
        Brain.Screen.newLine();
    }

    // Reset braking after 1/2 second
    wait(500, msec);
    StrafeMotor.stop(coast);

    Brain.Screen.clearScreen();
    Brain.Screen.clearLine();
}

void ControllerFunctions::triangulateTriball(){
    // Get the info from the distance sensors

    Brain.Screen.clearScreen();
    Brain.Screen.clearLine();

    Brain.Screen.print("Triangulating triball...");

    float left_distance = LeftDistanceSensor.objectDistance(inches);
    float right_distance = RightDistanceSensor.objectDistance(inches);

    strafe_motor_override = 0;

    // Check to see if we should correct
    if (left_distance < triball_alignment_minimum_distance)
    {
        // Move left
        strafe_motor_override = 1 - triball_adjustment_speed;
        Brain.Screen.print("Triball Alignment: Left");
        Brain.Screen.newLine();
        thread t1(stopStrafingMotor_thread);

    } else if (right_distance < triball_alignment_minimum_distance)
    {
        // Move right
        strafe_motor_override = triball_adjustment_speed;
        Brain.Screen.print("Triball Alignment: Right");
        Brain.Screen.newLine();
        thread t1(stopStrafingMotor_thread);
    } else 
    {
        Brain.Screen.print("Unable to Locate Triball...");
    }
}