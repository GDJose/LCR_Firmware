#include <LCR.h>

LCR robot;

void setup()
{
  robot.LCR_Init();

}


void loop()
{
  if (robot.LCR_IRArrayDetect(1,500)) {
    robot.LCR_LedOFF();
    if (robot.LCR_Bumper(1) == 1 && robot.LCR_Bumper(0) == 1) {
      robot.LCR_MotorR(FORWARDS,50);
      robot.LCR_MotorL(FORWARDS,50);

    } else if (robot.LCR_Bumper(1) == 0 && robot.LCR_Bumper(0) == 1) {
      robot.LCR_MotorR(BACKWARDS,50);
      robot.LCR_MotorL(FORWARDS,50);
    } else if (robot.LCR_Bumper(1) == 1 && robot.LCR_Bumper(0) == 0) {
      robot.LCR_MotorR(FORWARDS,50);
    } else {
      robot.LCR_Stop();

    }

  } else {
    robot.LCR_LedON();
    robot.LCR_Move(BACKWARDS,50,25);

  }

}
