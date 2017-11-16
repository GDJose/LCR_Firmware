/*
* Learning sequences
* Help The Educational Robot to reach the island programming sequences.
*
*---Blockly---
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
  robot.LCR_End(); 
}
