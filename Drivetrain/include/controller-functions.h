#pragma once

class ControllerFunctions
{
    public:
        static void update();
        static void triangulateTriball();
    private:
        static void intakeTriball();
        static void releaseTriball();
        static void intakeTriball_thread();
        static void releaseTriball_thread();

};