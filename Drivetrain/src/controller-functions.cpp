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
}

void ControllerFunctions::triballIntake()
{
    // Stop all other processes from messing with the arm
    // arm_overrided = true;

    // Move the arm up
    // Pull the puller in
    // Move the arm down a little
    // Stop the puller

    Brain.Screen.clearScreen();
    Brain.Screen.clearLine();

    float average = 0;
    int data_points = 0;
    for (int i = 0; i < 10; i++){
        float correction = triangulateTriball();
        if (correction != 0)
        {
            average += correction;
            data_points++;
        }
        // Brain.Screen.print(correction);
        // Brain.Screen.newLine();
    }

    average /= data_points;

    // float average = triangulateTriball();

    Brain.Screen.print(average);
}

float ControllerFunctions::triangulateTriball(){
    // Get the info from the distance sensors
    float left_distance = LeftDistanceSensor.objectDistance(inches);
    float right_distance = RightDistanceSensor.objectDistance(inches);

    // If one of the sensors is detecting something that is over 10 inches, throw out the result.
    // It's probably false
    if (left_distance > 10) return 0;
    if (right_distance > 10) return 0;

    // 2 / sqrt(3) = 1.1547
    float correction = ( 9 - left_distance * 1.1547) - (9 - right_distance * 1.1547);
    // float correction = (9 - left_distance) - (9 - right_distance);


    // If we are told to correct for over 10 inches, it's not within range.
    if (std::abs(correction) > 10) return 0;

    // Don't correct if we're within triball_alignment_accuracy inches
    if (std::abs(correction) <= triball_alignment_accuracy) return 0;

    // Add speed multiplier
    correction *= triball_alignment_speed_multiplier;

    // Return correction
    return correction;
}