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
