#include <LCR.h>

LCR robot;

void setup()
{
  robot.LCR_Init();

}


void loop()
{
  if (robot.LCR_Bumper(0)== 0) {
    robot.LCR_LedColor(255,255,255);
    robot.LCR_Delay(0.5);
    robot.LCR_LedOFF();
    robot.LCR_Delay(0.5);

  } else {
    robot.LCR_Sound(C,500);
    robot.LCR_Delay(0.5);
    robot.LCR_NoSound();
    robot.LCR_Delay(1);

  }

}
