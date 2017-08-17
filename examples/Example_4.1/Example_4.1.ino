#include <LCR.h>

LCR robot;

void setup()
{
  robot.LCR_Init();

}


void loop()
{
  robot.LCR_Turn(LEFT,180,0);
  robot.LCR_Delay(1);
  robot.LCR_Turn(RIGHT,270,0);
  robot.LCR_Turn(LEFT,270,0);
  robot.LCR_Delay(1);

}
