#include <LCR.h>

LCR robot;

void setup()
{
  robot.LCR_Init();

}


void loop()
{
  if (robot.LCR_Bumper(0) == 0) {
    robot.LCR_Turn(LEFT,0,0);
    robot.LCR_Move(FORWARDS,0,0);
    robot.LCR_Turn(RIGHT,0,0);
    robot.LCR_Move(FORWARDS,0,0);
    robot.LCR_Turn(RIGHT,0,0);
    robot.LCR_Move(FORWARDS,0,0);
    robot.LCR_Turn(LEFT,0,0);

  } else {
    robot.LCR_LineFollower(530,50);

  }

}
