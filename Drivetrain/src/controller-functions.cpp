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
    if (!arm_overrided)
    {
        // Triball Intake
        if(Controller1.ButtonR2.PRESSED)
        {
            triballIntake();
        }
    }
}

void ControllerFunctions::grabTriball()
{
    // Stop all other processes from messing with the arm
    arm_overrided = true;

    // Raise the arm
    ArmMotors.setVelocity(25, percent);
    wait(250, msec);
    ArmMotors.setVelocity(0, percent);

    // Move to triball
    triangulateTriball();

    // Use the flipper to try to grab it
    FlipperMotor.setVelocity(-50, percent);
    wait(2000, msec);

    // Bring the arm down a bit
    ArmMotors.setVelocity(-10, percent);
    
    wait(500, msec);
    ArmMotors.setVelocity(0, percent);
    FlipperMotor.setVelocity(0, percent);

    // Resume other processes
    arm_overrided = false;

}

void ControllerFunctions::triballIntake()
{
    thread t2(grabTriball);
}

void stopStrafingMotor()
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
        thread t1(stopStrafingMotor);

    } else if (right_distance < triball_alignment_minimum_distance)
    {
        // Move right
        strafe_motor_override = triball_adjustment_speed;
        Brain.Screen.print("Triball Alignment: Right");
        Brain.Screen.newLine();
        thread t1(stopStrafingMotor);
    }
}