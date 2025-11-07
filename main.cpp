/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       sachinbeniwal                                             */
/*    Created:      10/7/2025, 4:08:46 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain Brain;

// define your global instances of motors and other devices here
motor leftMotor = motor(PORT3, true);
motor leftMotor2 = motor(PORT1, false);
motor leftMotor3 = motor(PORT2, true);
motor rightMotor = motor(PORT13, false);
motor rightMotor2 = motor(PORT11, false);
motor rightMotor3 = motor(PORT12, false);
inertial gyro_1 = inertial(PORT15);
motor intake_bottom = motor(PORT19, true);
motor deposition = motor(PORT10, true);
controller cont = controller();
digital_out toungePos = digital_out(Brain.ThreeWirePort.H);
digital_out wingPneumatics = digital_out(Brain.ThreeWirePort.G); // Assuming port G for wing pneumatics

// Speed multiplier - adjust this value to change drive speed
// 1.0 = full speed, 0.5 = half speed, 0.7 = 70% speed, etc.
const double DRIVE_SPEED = 0.2;

//------------------- Motor Control Helper Functions -------------------//

/// @brief Sets the speed and direction for all left-side drive motors.
/// @param dir The direction to spin the motors (forward or reverse).
/// @param speed The speed at which to spin the motors.
/// @param units The units for the speed (e.g., percent, rpm).
void setLeftMotors(directionType dir, double speed, percentUnits units) {
  leftMotor.spin(dir, speed, units);
  leftMotor2.spin(dir, speed, units);
  leftMotor3.spin(dir, speed, units);
}



/// @brief Sets the speed and direction for all right-side drive motors.
/// @param dir The direction to spin the motors (forward or reverse).
/// @param speed The speed at which to spin the motors.
/// @param units The units for the speed (e.g., percent, rpm).
void setRightMotors(directionType dir, double speed, percentUnits units) {
  rightMotor.spin(dir, speed, units);
  rightMotor2.spin(dir, speed, units);
  rightMotor3.spin(dir, speed, units);
}



/// @brief Sets the speed and direction for all drive motors (left and right).
/// @param dir The direction to spin the motors (forward or reverse).
/// @param speed The speed at which to spin the motors.
/// @param units The units for the speed (e.g., percent, rpm).
void setAllMotors(directionType dir, double speed, percentUnits units) {
  setLeftMotors(dir, speed, units);
  setRightMotors(dir, speed, units);
}



/// @brief Stops all drive motors with a specified brake mode.
/// @param mode The brake mode to use (e.g., brake, hold, coast).
void stopAllMotors(brakeType mode = brake) {
  leftMotor.stop(mode);
  leftMotor2.stop(mode);
  leftMotor3.stop(mode);
  rightMotor.stop(mode);
  rightMotor2.stop(mode);
  rightMotor3.stop(mode);
}



//------------------- Driver Control -------------------//


/// @brief Implements split drive control using controller axes.
/// Also controls the tounge position, intake, and deposition mechanisms based on button presses.
void split_Drive() {
    double leftSpeed = (cont.Axis3.position() + cont.Axis1.position()) * DRIVE_SPEED;
    double rightSpeed = (cont.Axis3.position() - cont.Axis1.position()) * DRIVE_SPEED;
    
    setLeftMotors(forward, leftSpeed, pct);
    setRightMotors(forward, rightSpeed, pct);
    if(cont.ButtonA.pressing()) {
        toungePos.set(true);
    } else if(cont.ButtonB.pressing()) {
        toungePos.set(false);
    }

    // Control for wing
    // ButtonX will extend the wing (set to true), rubber bands will retract it when released
    if(cont.ButtonX.pressing()) {
        wingPneumatics.set(true);
    } else {
        wingPneumatics.set(false); // Allow rubber band to retract
    }
    //Control for intake
    //
    if(cont.ButtonL1.pressing()) {
        intake_bottom.spin(forward, 100, pct);
    } else if(cont.ButtonL2.pressing()) {
        intake_bottom.spin(forward, -100, pct);
    } else {
        intake_bottom.stop();
    }
    //COntroll for depo
    if(cont.ButtonR1.pressing()) {
        deposition.spin(forward, 100, pct);
    } else if(cont.ButtonR2.pressing()) {
        deposition.spin(forward, -100, pct);
    } else {
        deposition.stop();
    }
}



/// @brief Main function of the V5 project.
/// Initializes the brain screen and continuously calls the split_Drive function for driver control.
int main() {
    
    Brain.Screen.printAt( 10, 50, "Hello V5" );
   
    while(1) {
        split_Drive();
        // Allow other tasks to run
        this_thread::sleep_for(10);
    }
}
