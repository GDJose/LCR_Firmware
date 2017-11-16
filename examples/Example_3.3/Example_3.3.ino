/*
*IRArray
*
*Learn how the IRArray works and help The Educational Robot to detect the ravine. 
*If you are too close, go backwards!
*
*---Blockly---
** if - IR sensors over threshold 550
**** Led Color
**** No Sound
** else
**** Led off
**** Sound - C - duration - 100
**** Delay (seconds) - 0.1
**** Sound - G# - duration - 100
**** Delay (seconds) - 0.1
*/

#include <LCR.h>

LCR robot;

void setup()
{
  robot.LCR_Init();

}


void loop()
{
  if (robot.LCR_IRArrayDetect(0,550)) 
  {
    robot.LCR_LedColor(255,255,255);
    robot.LCR_NoSound();
  } 
  else 
  {
    robot.LCR_LedOFF();
    robot.LCR_Sound(C,100);
    robot.LCR_Delay(0.1);
    robot.LCR_Sound(GS,100);
    robot.LCR_Delay(0.1);
  }
}
