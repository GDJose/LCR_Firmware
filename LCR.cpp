
#ifndef LCR_h
#define LCR_h

#include "arduino.h"
#include "LCR.h"

//Variables
int countRIGHT =0;
int countLEFT =0;
int stepR = 0;
int stepL = 0;
volatile int finishMove = 1;	//Variable to indicate the movement has been finished

/************************************************************************************************
*	Description:  This function initialize the standard configuration for the LCR				*
*	Arguments: None 																			*				
*	 																							*				   
************************************************************************************************/

void LCR_Init()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);  //LED pin
  pinMode(19, OUTPUT); //Enable Motors 
  digitalWrite(19,HIGH); //In this prototype we need this pin HIGH all the time
  pinMode(3, OUTPUT);  //PWM Backward LEFT Motor
  pinMode(9, OUTPUT);  //PWM Forward LEFT Motor
  pinMode(5, OUTPUT);  //PWM Backward RIGHT Motor
  pinMode(6, OUTPUT);  //PWM Forward RIGHT Motor
  attachInterrupt(digitalPinToInterrupt(7),Encoder1LEFT, RISING);  // Encoder A Motor LEFT
 // attachInterrupt(digitalPinToInterrupt(10),Encoder1RIGHTT, RISING); //Encoder B motor LEFT
  attachInterrupt(digitalPinToInterrupt(11),Encoder1RIGHT, RISING); //Encoder A motor RIGHT
 // attachInterrupt(digitalPinToInterrupt(12),Encoder1RIGHT, RISING); //Encoder B motor RIGHT
  pinMode(13,OUTPUT);  //Modulino Connector 2
  pinMode(4,OUTPUT);   //Modulino Connector 1
  pinMode(8, OUTPUT);  //Piezzo
}

/************************************************************************************************
*	Description:  This function moves forward and backward the robot							*
*	Arguments:  																				*				
*	 	- Dir:		 	0 = Forward																*	
*						1 = Backward															*
*		- Distance: 	Distance in mm we want to move the robot								*
*		- Rate:			Number between 0 and 100 that indicate the % speed which the 			*	
*						robot is going to move. 												*
*	By deffect the values are:	0 -> Forward													*
*							  160 -> 16 cm.														*
*							   25 -> 25% of the max. speed										*
*	To select the values by deffect is no neccesary put any argument between brackets			*				   
************************************************************************************************/

void LCR_Move ( bool dir, int distance, int rate )
{
  //Select the values by deffect
  if (rate == 0)
  {
    rate = 25;
    }

  if (distance == 0)
  {
    distance = 160;
    }
  
  //Calculate the number of pulses that we need to move the spefied distance
  rate = map (rate, 100, 0, 0,230);
  stepR = PPV*distance/191.6;
  stepL = stepR;
  
  //Move forward
  if (dir == 0)
  {
    digitalWrite(9, HIGH);
    analogWrite (3, rate);
    digitalWrite(5, HIGH);
    analogWrite (6, rate+3);
  }
  //Move backward
  else 
  {
    digitalWrite(3, HIGH);
    analogWrite (9, rate);
    digitalWrite(6, HIGH);
    analogWrite (5, rate+3); 
  }
  while(finishMove); //Wait until the movement is finished
  LCR_Stop();		 //Stop the robot
}

/***************************************************************************************************
*	Description:  This function turns the robot right and left(using diferent ways(not ready yet)) *
*	Arguments:  																				   *				
*	 	- Dir: 			0 = Turn Right															   *	
*						1 = Turn Left														   	   *
*		- Distance: 	Degrees to turn								   							   *
*		- Rate:			Number between 0 and 100 that indicate the % speed which the 			   *	
*						robot is going to move. 												   *
*		- Mode:			0 = Turn taking like origin the center between the motors				   *
*						1 = Using a wheel like centre of the movement (not ready yet			   *
*																								   *
*	By deffect the values are:	0 -> Right   													   *
*							   90 -> 90 degrees													   *
*							   25 -> 25% of the max. speed										   *
*							    0 -> Turn taking like origin the center between the motors		   *
*	To select the values by deffect is no neccesary put any argument between brackets			   * 				   
***************************************************************************************************/

void LCR_Turn ( bool dir, int deg, int rate, bool mode )
{
  int dist;		//Distance that in mm that should move every wheel during th turn
  
  //Select the values by deffect
  if (rate == 0)
  {
    rate = 25;
    }

  if (deg == 0)
  {
    deg = 90;
    }
  
  //Calculate the speed to turn
  rate = map (rate, 100, 0, 0,230);
  //Turn taking like origin the center between the motors	
  if (mode == 0)
  {
	dist = (2*PI*70)/(360/deg);
	stepR = PPV*dist/191.6;
	stepL = stepR;  
    if (dir == 0)
    {
      digitalWrite(9, HIGH);
      analogWrite (3, rate);
      digitalWrite(6, HIGH);
      analogWrite (5, rate+3);
    }
    else 
    {
      digitalWrite(3, HIGH);
      analogWrite (9, rate);
      digitalWrite(5, HIGH);
      analogWrite (6, rate+3); 
    } 
  }
   //Turn taking like origin one wheel	
  /* else 
  { 
    if (dir == 0)
    {
	  dist = (2*PI*140)/(360/deg);
	  stepL = PPV*dist/191.6; 
      digitalWrite(9, HIGH);
      analogWrite (3, rate);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
    }
    else 
    {
	  dist = (2*PI*140)/(360/deg);
	  stepR = PPV*dist/191.6; 
      digitalWrite(3, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(5, HIGH);
      analogWrite (6, rate+3); 
	  Serial.println(dist);
	  Serial.println(stepR);
	  Serial.println(finishMove);
    } 
  } */
  while(finishMove);		//Wait until the turn finishes
  LCR_Stop();				//Stop the robot
}

/***************************************************************************************************
*	Description:  This function turns the robot LED ON											   *
*	Arguments:    None		 																	   * 
*																								   *				   
***************************************************************************************************/
LCR_LedON()
{
	digitalWrite(2, HIGH);
}
/************************************************************************************************
*	Description:  This function turns the robot LED OFF						      				*
*	Arguments: None 																			*				
*	 																							*				   
************************************************************************************************/
LCR_LedOFF()
{
	digitalWrite(2, LOW);
}

/************************************************************************************************
*	Description:  This function stops the robot and reset all the variables that use to	        *
*				  make movements																*
*	Arguments: None 																			*				
*	 																							*				   
************************************************************************************************/
void LCR_Stop ()
{
 digitalWrite(3, HIGH);
 digitalWrite(9, HIGH);
 digitalWrite(5, HIGH);
 digitalWrite(6, HIGH);
 
 //Reset step counters
 countLEFT = 0;
 countRIGHT = 0;
 finishMove = 1;
}

/************************************************************************************************
*	Description:  This function delays the robot							      				*
*	Arguments:  																			    *
*		- Seconds: Number of senconds we want delay												*				
*	 																							*				   
************************************************************************************************/
void LCR_Delay(float seconds)
{
	delay(seconds*1000);
}

/************************************************************************************************
*	Description:  These functions increase the number of pulses while the wheels are moving 	*
*				  and update the flag that indicate the movement is ended						*
*	Arguments:  None																		    *										
*	 																							*				   
************************************************************************************************/
void Encoder1LEFT()
{
  countLEFT+=1;
  if (countLEFT >= stepL) 
	  finishMove = 0;
}

void Encoder1RIGHT()
{ 
  countRIGHT+=1;
   if (countRIGHT >= stepR) 
	  finishMove = 0;
}

#endif
