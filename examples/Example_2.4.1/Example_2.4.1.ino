/*
*Reach the treasure
*
*Help the pirate to find the treasure, during the day. 
*
*---Blockly---
** if - Light sensor on the - Right < 512
**** Turn - Right
** else if - Light sensor on the - Left < 512
**** Turn - Left
** else if - Light sensor on the - Right > 512
**** Move - Forwards
** else if - Light sensor on the - Left > 512
**** Move - Backwards
*/
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
