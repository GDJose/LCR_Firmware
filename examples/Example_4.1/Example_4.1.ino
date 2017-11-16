/*
*Different ways to turn
*
*To do this tour, you will need to learn all the ways that exist to turn the robot.
*
*---Blockly---
** if - IR sensors over threshold 550
**** Led Color
**** No Sound
** else
**** Turn - left -angle - 180
**** Delay (seconds) - 1
**** Turn - right -angle - 270
**** Turn - left -angle - 270
**** Delay (seconds) - 1
*/
#include <LCR.h>

LCR robot;

void setup()
{
  robot.LCR_Init();

}


void loop()
{
  robot.LCR_Turn(LEFT,180,0);
  robot.LCR_Delay(1);
  robot.LCR_Turn(RIGHT,270,0);
  robot.LCR_Turn(LEFT,270,0);
  robot.LCR_Delay(1);

}
