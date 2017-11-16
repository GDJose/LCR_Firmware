/*
* Loops
* Do it faster! Use loops.
*
*---Blockly---
** count - i from 0 to 4
**** Move - Forward
**** Turn - Left
**** Move - Forward
**** Turn - Right
**** Delay (seconds) - 1
** End 
*/
#include <LCR.h>

LCR robot;

void setup()
{
  robot.LCR_Init();
}


void loop()
{
  for (int i=0; i<4; i++)
  { 
   robot.LCR_Move(FORWARDS,0,0);
   robot.LCR_Turn(LEFT,0,0);
   robot.LCR_Move(FORWARDS,0,0);
   robot.LCR_Turn(RIGHT,0,0);
   robot.LCR_Delay(1);
  } 
 robot.LCR_End(); 
}
