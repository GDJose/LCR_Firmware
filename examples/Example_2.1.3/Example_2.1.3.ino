/*
*Sound and leds
*
*Create a combination of lights and sounds. Communicate with your fellow pirates.
*
*---Blockly---
** Led Color
** Delay (seconds) - 0.5
** Led Off
** Sound - G - duration 1000
** Sound - A - duration 1000
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
  robot.LCR_LedColor(255,255,255);
  robot.LCR_Delay(0.5);
  robot.LCR_LedOFF();
  robot.LCR_Sound(G,1000);
  robot.LCR_Sound(A,1000);

}
