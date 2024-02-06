#include "cmath"

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

    strafe_motor_override = 0;
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

void ControllerFunctions::triangulateTriball(){
    // Get the info from the distance sensors
    float left_distance = LeftDistanceSensor.objectDistance(inches);
    float right_distance = RightDistanceSensor.objectDistance(inches);

    strafe_motor_override = 0;

    // Check to see if we should correct
    if (left_distance < triball_adjustment_distance)
    {
        // Move left
        strafe_motor_override += triball_adjustment_distance;
        Brain.Screen.print("Left");
    }
    if (right_distance < triball_adjustment_distance)
    {
        // Move right
        strafe_motor_override -= triball_alignment_distance;
        Brain.Screen.print("Right");
    }
}