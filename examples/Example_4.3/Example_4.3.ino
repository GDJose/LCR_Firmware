/*
*Follow the line.
*
*You can start to make the crocodiles trip.
*
*---Blockly---
** Follow line: Threshold - 530 - Speed - 50
*/

#include <LCR.h>

LCR robot;

void setup()
{
  robot.LCR_Init();

}


void loop()
{
  robot.LCR_LineFollower(530,50);

}
