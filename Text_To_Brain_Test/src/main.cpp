/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Wed Sep 25 2019                                           */
/*    Description:  Printing Text                                             */
/*                                                                            */
/*    When the program is started, "Hello", "Welcome!" and "Goodbye!" will    */
/*    each display on their own row on the Brain's screen before all being    */
/*    erased.                                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Brain.Screen.print("Hello");
  wait(1, seconds);
  Brain.Screen.newLine();
  Brain.Screen.print("Welcome!");
  wait(1, seconds);
  Brain.Screen.newLine();
  Brain.Screen.print("Goodbye!");
  wait(1, seconds);
  Brain.Screen.clearScreen();
}
