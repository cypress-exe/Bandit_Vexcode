#include "cmath"
#include <thread>

#include "vex.h"
#include "overrides.h"

#include "controller-functions.h"
#include "settings-config.h"

// Called every update frame
void ControllerFunctions::update()
{
    // No triball operations if the arm is in use
    if (!arm_overrided)
    {
        // Triball Intake
        if(Controller1.ButtonR2.PRESSED)
        {
            triballIntake();
        }
    }
}

void ControllerFunctions::triballIntake()
{
    // Stop all other processes from messing with the arm
    // arm_overrided = true;

    // Move the arm up
    // Pull the puller in
    // Move the arm down a little
    // Stop the puller

    triangulateTriball();
}

void stopStrafingMotor()
{
    distance sensor = RightDistanceSensor;

    // Stop once the triball is the correct distance away from the sensor.
    int msecs_waiting = 0;
    
    while(sensor.objectDistance(inches) < triball_alignment_maximum_distance && msecs_waiting < 1000) { // 1 second timeout
        wait(5, msec);
        msecs_waiting += 5;

        Brain.Screen.print(sensor.objectDistance(inches));
        Brain.Screen.newLine();
    }
    strafe_motor_override = 0;

    // Brake immediately
    StrafeMotor.stop(brake);

    if (msecs_waiting >= 1000)
    {
        Brain.Screen.print("Triball Triangulation Failed... Canceled.");
        Brain.Screen.newLine();
    }
}

void ControllerFunctions::triangulateTriball(){
    // Get the info from the distance sensors
    float left_distance = LeftDistanceSensor.objectDistance(inches);
    float right_distance = RightDistanceSensor.objectDistance(inches);

    strafe_motor_override = 0;

    // Check to see if we should correct
    if (left_distance < triball_alignment_minimum_distance)
    {
        // Move left
        strafe_motor_override = 1-triball_adjustment_speed;
        Brain.Screen.print("Left");
        thread tl(stopStrafingMotor);
    }
    if (right_distance < triball_alignment_minimum_distance)
    {
        // Move right
        strafe_motor_override = triball_adjustment_speed;
        Brain.Screen.print("Right");
        thread tl(stopStrafingMotor);
    }
}