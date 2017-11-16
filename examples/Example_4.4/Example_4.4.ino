/*
*Follow the line with obstacles
*
*Help The Educational Robot to follow the crocodiles route. But remember, when you find the plant, you must need to stop for a minute. 
*The Educational Robot needs this time.
*
*---Blockly---
** if - Button on the - Right == 0
**** Turn - Left
**** Move - Forwards
**** Turn - Right
**** Move - Forwards
**** Turn - Right
**** Move - Forwards
**** Turn - Left
** else
**** Follow line: Threshold - 530 - Speed - 50
*/

#include <LCR.h>

LCR robot;

void setup()
{
  robot.LCR_Init();

}


void loop()
{
  if (robot.LCR_Bumper(0) == 0) {
    robot.LCR_Turn(LEFT,0,0);
    robot.LCR_Move(FORWARDS,0,0);
    robot.LCR_Turn(RIGHT,0,0);
    robot.LCR_Move(FORWARDS,0,0);
    robot.LCR_Turn(RIGHT,0,0);
    robot.LCR_Move(FORWARDS,0,0);
    robot.LCR_Turn(LEFT,0,0);

  } else {
    robot.LCR_LineFollower(530,50);

  }

}
