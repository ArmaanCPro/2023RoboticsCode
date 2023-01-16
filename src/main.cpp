/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Armaan Chahal                                    */
/*    Created:      Thu Nov 10 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// ExpansionMotor       motor         9               
// LeftDrive            motor_group   1, 2            
// RightDrive           motor_group   3, 4            
// IntakeMotors         motor_group   10, 20          
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "Drive.h"

using namespace vex;

// A global instance of competition
competition Competition;

DS::Drive drive(LeftDrive, RightDrive);

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
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

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

void autonomous(void)
{
  /*drive.SpinFor(0.5, seconds); // Slightly move forward

  drive.TurnFor(0.4, seconds, false); // Turn to the right

  drive.SpinFor(0.6, seconds); // Move toward the roller

  drive.SpinFor(0.4, seconds, true); // Turn to the left and face forward

  drive.SpinFor(0.5, seconds, true, true); // Reverse slightly

  IntakeMotors.spinFor(forward, 0.1, seconds); // Spin the roller*/
  IntakeMotors.spinFor(forward, 0.1, seconds);
}

void usercontrol(void) 
{
  // User control code here, inside the loop
  while (1)
  {
    //Go forward/backward if left joystick is pushed forward/backward
    if (Controller1.Axis3.position(pct) != 0)
    {
      drive.Spin(Controller1.Axis3.position(pct), percent);
    }

    //Turn left/right if right joystick is pushed left/right
    else if(Controller1.Axis1.position(pct) != 0)
    {
      drive.Turn(Controller1.Axis1.position(pct), percent, false);
    }

    //Stop each of the motors
    else
    {
      LeftDrive.stop(hold);
      RightDrive.stop(hold);
    }

    if (Controller1.ButtonL2.pressing())
    {
      IntakeMotors.spin(forward, 90, pct);
      wait(25, msec);
    }

    else if (Controller1.ButtonR2.pressing())
    {
      IntakeMotors.spin(reverse, 90, pct);
      wait(25, msec);
    }

    else
    {
      IntakeMotors.stop(hold);
    }

    if (Controller1.ButtonA.pressing())
    {
      ExpansionMotor.spinFor(forward, 1000, msec);
      wait(200, msec);
    }
    else
    {
      ExpansionMotor.stop(hold);
    }
  }
}

int main() 
{
  // Set up callbacks for autonomous and driver control periods.  
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) 
  {
    wait(100, msec);
  }
}