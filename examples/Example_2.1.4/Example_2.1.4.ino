#include <LCR.h>

int i;

LCR robot;

void setup()
{
  robot.LCR_Init();

}


void loop()
{
  for (i = 0; i <= 4; i++) {
    robot.LCR_LedColor(255,255,255);
    robot.LCR_Delay(0.5);
    robot.LCR_LedOFF();
    robot.LCR_Delay(1);
  }
  robot.LCR_End();
}
