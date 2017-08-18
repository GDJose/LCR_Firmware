#include <LCR.h>

LCR robot;

void setup()
{
  robot.LCR_Init();

}


void loop()
{
  robot.LCR_Move(FORWARDS,0,0);
  robot.LCR_Turn(LEFT,0,0);
  robot.LCR_Move(FORWARDS,0,0);
  robot.LCR_Turn(RIGHT,0,0);
  robot.LCR_Delay(1);

  robot.LCR_Move(FORWARDS,0,0);
  robot.LCR_Turn(LEFT,0,0);
  robot.LCR_Move(FORWARDS,0,0);
  robot.LCR_Turn(RIGHT,0,0);
  robot.LCR_Delay(1);
  
  robot.LCR_Move(FORWARDS,0,0);
  robot.LCR_Turn(LEFT,0,0);
  robot.LCR_Move(FORWARDS,0,0);
  robot.LCR_Turn(RIGHT,0,0);
 
  robot.LCR_End(); 
}
