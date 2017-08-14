#include <LCR.h>

LCR robot;

void setup()
{
  robot.LCR_Init();
}


void loop()
{
  for (int i=0; i<4; i++)
  { 
   robot.LCR_Move(FORWARDS,80,0);
   robot.LCR_Turn(LEFT,0,0);
   robot.LCR_Delay(0.5);
  } 
 robot.LCR_End(); 
}
