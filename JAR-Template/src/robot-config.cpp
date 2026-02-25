#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen.
brain  Brain;

//The motor constructor takes motors as (port, ratio, reversed), so for example
//motor LeftFront = motor(PORT1, ratio6_1, false);

//Add your devices below, and don't forget to do the same in robot-config.h:

motor LeftFront = motor(PORT1, ratio6_1, true );
motor LeftMiddle = motor(PORT2, ratio6_1, true);
motor LeftBack = motor(PORT3, ratio6_1, true);
motor rightFront = motor(PORT10, ratio6_1, false);
motor rightMiddle = motor(PORT9, ratio6_1, false);
motor rightBack = motor(PORT8, ratio6_1, false);  
motor intake = motor(PORT13, ratio6_1, true);
motor deposition = motor(PORT12, ratio6_1, true);
digital_out toungePos = digital_out(Brain.ThreeWirePort.C);
digital_out wingPneumatics = digital_out(Brain.ThreeWirePort.B);
digital_out midgoalScorer = digital_out(Brain.ThreeWirePort.A);
void vexcodeInit( void ) {
  // nothing to initialize
} 
