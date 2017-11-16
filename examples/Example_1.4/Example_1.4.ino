/*
*Degrees and distances.
*
*Help The Educational Robot to draw all the animals that he love. But you have a condition, you can only use straight lines:) 
*Are you ready?
*
*---Blockly---
** count - i from 0 to 4
**** Move - Forward - 80
**** Turn - Left - 45
**** Delay (seconds) - 0.5
** End 
*/
#include <LCR.h>

int i;

LCR robot;

void setup()
{
  robot.LCR_Init();

}


void loop()
{
  for (i = 1; i <= 4; i++) {
    robot.LCR_Move(FORWARDS,80,0);
    robot.LCR_Turn(LEFT,45,0);
    robot.LCR_Delay(0.5);
  }
  robot.LCR_End();

}
