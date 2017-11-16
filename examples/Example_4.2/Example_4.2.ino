/*
*IRArray with 3 sensors. Learning ranges.
*
*Then, you will need to learn how the IRArray sensor works.
*
*---Blockly---
** if - IR sensor - 1 - Threshold - 530
**** Sound - C - duration - 1000
**** Delay (seconds) - 1
** else if - IR sensor - 2 - Threshold - 530
**** Sound - F - duration - 1000
**** Delay (seconds) - 1
** else if - IR sensor - 3 - Threshold - 530
**** Sound - A - duration - 1000
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
  if (robot.LCR_IRArrayDetect(1,530)) {
    robot.LCR_Sound(C,1000);
    robot.LCR_Delay(1);

  } else if (robot.LCR_IRArrayDetect(2,530)) {
    robot.LCR_Sound(F,1000);
    robot.LCR_Delay(1);
  } else if (robot.LCR_IRArrayDetect(3,530)) {
    robot.LCR_Sound(A,1000);
    robot.LCR_Delay(1);
  }

}
