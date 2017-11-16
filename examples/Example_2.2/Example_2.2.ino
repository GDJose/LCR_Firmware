/*
*Read the light sensor
*
*The Educational Robot wants to use a light sensor to fix the problem. Help him to know how it works.
*
*---Blockly---
** Light sensor on the - Right - turn in leds when value is - 512
*/
#include <LCR.h>

LCR robot;

void setup()
{
  robot.LCR_Init();

}


void loop()
{
  robot.LCR_LightTrigger(0,512);

}
