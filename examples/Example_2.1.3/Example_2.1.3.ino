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
