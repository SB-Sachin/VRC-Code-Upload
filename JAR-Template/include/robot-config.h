using namespace vex;

extern brain Brain;

//To set up a motor called LeftFront here, you'd use
//extern motor LeftFront;

//Add your devices below, and don't forget to do the same in robot-config.cpp:

extern motor LeftFront = motor(PORT1, ratio6_1, true );
extern motor LeftMiddle = motor(PORT2, ratio6_1, true);
extern motor LeftBack = motor(PORT3, ratio6_1, true);
extern motor rightFront = motor(PORT10, ratio6_1, false);
extern motor rightMiddle = motor(PORT9, ratio6_1, false);
extern motor rightBack = motor(PORT8, ratio6_1, false);  
extern motor intake = motor(PORT13, ratio6_1, true);
extern motor deposition = motor(PORT12, ratio6_1, true);
extern digital_out toungePos = digital_out(Brain.ThreeWirePort.C);
extern digital_out wingPneumatics = digital_out(Brain.ThreeWirePort.B);
extern digital_out midgoalScorer = digital_out(Brain.ThreeWirePort.A);

void  vexcodeInit( void );
