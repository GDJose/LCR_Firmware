#include <LCR.h>

LCR robot;

void setup()
{
  robot.LCR_Init();

}


void loop()
{
  if (robot.LCR_LightSensor(0) < 512) {
    robot.LCR_Turn(RIGHT,0,0);

  } else if (robot.LCR_LightSensor(1) < 512) {
    robot.LCR_Turn(LEFT,0,0);
  } else if (robot.LCR_LightSensor(0) > 512) {
    robot.LCR_Move(FORWARDS,0,0);
  } else if (robot.LCR_LightSensor(1) > 512) {
    robot.LCR_Move(BACKWARDS,0,0);
  }

}
