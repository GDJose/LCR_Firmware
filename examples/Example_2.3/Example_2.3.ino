/*
*Conditionals
*
*Check the sensor to make sure that it works properly.
*
*---Blockly---
** if - Light sensor on the - Right > 512
****Sound - G - duration - 1000
****Sound - A - duration - 1000
****Led Color
****Delay - 0.5
****Led Off
*/
#include <LCR.h>

LCR robot;

void setup()
{
  robot.LCR_Init();

}


void loop()
{
  if (robot.LCR_LightSensor(0) > 512) {
    robot.LCR_Sound(G,1000);
    robot.LCR_Sound(A,1000);
    robot.LCR_LedColor(255,255,255);
    robot.LCR_Delay(0.5);
    robot.LCR_LedOFF();

  }

}
