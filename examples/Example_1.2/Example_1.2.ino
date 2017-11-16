/*
* Sequences and delay
* It would be advisable to collect part of the resources that have fallen out of the boat. 
* Could you help him?
*
*---Blockly---
** Move - Forward
** Turn - Left
** Move - Forward
** Turn - Right
** Delay (seconds) - 1
** Move - Forward
** Turn - Left
** Move - Forward
** Turn - Right
** Delay (seconds) - 1
** Move - Forward
** Turn - Left
** Move - Forward
** Turn - Right
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
  robot.LCR_Move(FORWARDS,0,0);
  robot.LCR_Turn(LEFT,0,0);
  robot.LCR_Move(FORWARDS,0,0);
  robot.LCR_Turn(RIGHT,0,0);
  robot.LCR_Delay(1);

  robot.LCR_Move(FORWARDS,0,0);
  robot.LCR_Turn(LEFT,0,0);
  robot.LCR_Move(FORWARDS,0,0);
  robot.LCR_Turn(RIGHT,0,0);
  robot.LCR_Delay(1);
  
  robot.LCR_Move(FORWARDS,0,0);
  robot.LCR_Turn(LEFT,0,0);
  robot.LCR_Move(FORWARDS,0,0);
  robot.LCR_Turn(RIGHT,0,0);
 
  robot.LCR_End(); 
}
