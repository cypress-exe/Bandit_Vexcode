#pragma once

class ControllerFunctions
{
    public:
        static void init();
        static void intakeTriball();
        static void releaseTriball();
        static void launch();
        static void intakeTriball_thread();
        static void releaseTriball_thread();
        static void launch_thread();
};