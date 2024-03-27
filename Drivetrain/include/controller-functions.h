#pragma once

class ControllerFunctions
{
    public:
        static void init();
        static void intakeTriball();
        static void releaseTriball();
        static void launch();
        static void launch_recover();
        static void prepareLaunch();
        static void intakeTriball_thread();
        static void releaseTriball_thread();
        static void launch_thread();
        static void launch_recover_thread();
};