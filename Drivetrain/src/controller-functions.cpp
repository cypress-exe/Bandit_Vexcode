#include "vex.h"
#include "overrides.h"

#include "controller-functions.h"

// Called every update frame
void ControllerFunctions::update()
{
    // No triball operations if the arm is in use
    if (!arm_overrided)
    {
        // Triball Intake
        if(Controller1.ButtonR2.pressing())
        {
            triballIntake();
        }
    }
}

void ControllerFunctions::triballIntake()
{
    // Stop all other processes from messing with the arm
    arm_overrided = true;

    // Move the arm up
    // Pull the puller in
    // Move the arm down a little
    // Stop the puller
}