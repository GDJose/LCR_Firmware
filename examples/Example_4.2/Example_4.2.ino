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
