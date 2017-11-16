/*
*Remote control with bumpers
*
*Try to control the car by using two bumpers and programming statements.
*
*---Blockly---
** if - Button on the - Left = 1 AND Button on the - Right = 1
**** Move right motor - Forwards - speed - 50
**** Move left motor - Forwards - speed - 50
** else if - Button on the - Left = 0 AND Button on the - Right = 1
**** Move right motor - Backwards - speed - 50
**** Move left motor - Forwards - speed - 50
** else if - Button on the - Left = 0 AND Button on the - Right = 0
**** Move right motor - Forwards - speed - 50
**** Move left motor - Backwards - speed - 50
** else
**** Stop
*/
#include <LCR.h>

LCR robot;

void setup()
{
  robot.LCR_Init();

}


void loop()
{
  
  if (robot.LCR_Bumper(1)== 1 && robot.LCR_Bumper(0)== 1) 
  {
    robot.LCR_MotorR(FORWARDS,50);
    robot.LCR_MotorL(FORWARDS,50);
  } 
  else if (robot.LCR_Bumper(1)== 0 && robot.LCR_Bumper(0) == 1) 
  {
    robot.LCR_MotorR(BACKWARDS,50);
    robot.LCR_MotorL(FORWARDS,50);
  } 
  else if (robot.LCR_Bumper(1)== 1 && robot.LCR_Bumper(0) == 0) 
  {
    robot.LCR_MotorR(FORWARDS,50);
    robot.LCR_MotorL(BACKWARDS,50);
  } 
  else 
  {
    robot.LCR_Stop();
  }

}
