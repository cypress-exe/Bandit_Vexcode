#pragma once

class ControllerMovement
{
    public:
        static void initDriveMotors();
        static void initArmMotors();
        static void initBeltMotor();
    private:
        static void updateDriveMotors();
        static void updateArmMotors();
        static void updateBeltMotor();
};