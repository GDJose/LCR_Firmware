/*
*Sound and leds
*
*Create a combination of lights and sounds. Communicate with your fellow pirates.
*
*---Blockly---
** Sound - G - duration 1000
** Sound - A - duration 1000
** Sound - E - duration 1000
** Sound - F - duration 1000
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
  robot.LCR_Sound(G,1000);
  robot.LCR_Sound(A,1000);
  robot.LCR_Sound(E,1000);
  robot.LCR_Sound(F,1000);
  robot.LCR_Sound(G,1000);
  robot.LCR_Sound(A,1000);
  robot.LCR_End();

}
