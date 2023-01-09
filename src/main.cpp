/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Ryan Spelde                                               */
/*    Created:      12/8/2022, 4:21:27 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

bool speldeMode = false;

// main peripherals
brain myBrain = brain();
controller myController = controller();

// motors
motor leftDriveMotor = motor(PORT2, ratio18_1, false);
motor rightDriveMotor = motor(PORT12, ratio18_1, true);
motor flyWheel = motor(PORT5, ratio36_1, false);
motor intake = motor(PORT10, ratio6_1, false);

void toggleSpeldeMode() {
  myController.rumble("..");
  speldeMode = !speldeMode;

  myController.Screen.clearScreen();
  myController.Screen.setCursor(0, 0);
  myController.Screen.print("Spelde Mode: " + (speldeMode && "Activated" || "Deactivated"));
};

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {

  myController.ButtonX.pressed(toggleSpeldeMode);

  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    // drive
    if (speldeMode) {

      int x = -myController.Axis4.value();
      int y = myController.Axis3.value();

      int v = (100 - abs(x)) * (y / 100) + y;
      int w = (100 - abs(y)) * (x / 100) * (x / 100) + x;

      int r = (v + w) / 2;
      int l = (v - w) / 2;

      leftDriveMotor.spin(forward, l, percent);
      rightDriveMotor.spin(forward, r, percent);

    } else {
      leftDriveMotor.spin(forward, myController.Axis3.value(), percent);
      rightDriveMotor.spin(forward, myController.Axis2.value(), percent);
    }

    // flywheel
    flyWheel.spin(forward, myController.ButtonA.pressing() && 100 || 0, percent);

    // intake
    if (myController.ButtonR1.pressing()) {
      intake.spin(forward, 100, percent);
    } else if (myController.ButtonR2.pressing()) {
      intake.spin(forward, -100, percent);
    } else {
      intake.stop();
    }

    wait(10, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
