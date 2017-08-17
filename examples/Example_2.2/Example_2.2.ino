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
