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

void toggleSpeldeMode() {
  speldeMode = !speldeMode;
};

// main peripherals
brain myBrain = brain();
controller myController = controller();

// motors
motor leftDriveMotor = motor(PORT11, ratio18_1, false);
motor rightDriveMotor = motor(PORT12, ratio18_1, true);
motor flyWheel = motor(PORT5, ratio36_1, false);
motor intake = motor(PORT16, ratio6_1, false);

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
      leftDriveMotor.spin(forward, myController.Axis3.value() * myController.Axis4.value() * 0.5, percent);
      rightDriveMotor.spin(forward, myController.Axis3.value() * myController.Axis4.value() * 0.5, percent);
    } else {
      leftDriveMotor.spin(forward, myController.Axis3.value(), percent);
      rightDriveMotor.spin(forward, myController.Axis2.value(), percent);
    }

    // flywheel
    flyWheel.spin(forward, myController.ButtonA.pressing() && 100 || 0, percent);

    // intake
    if (myController.ButtonR1.pressing()) {
      intake.spin(forward, 50, percent);
    } else if (myController.ButtonR2.pressing()) {
      intake.spin(forward, -50, percent);
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
