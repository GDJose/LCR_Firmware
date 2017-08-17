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
    robot.LCR_LedON();
    robot.LCR_Delay(0.5);
    robot.LCR_LedOFF();
    robot.LCR_Delay(1);
  }

}
