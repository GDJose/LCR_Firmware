
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
  pinMode(A0, INPUT);  //Right Analog sensor
  pinMode(A1, INPUT);  //Left Analog sensor
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

/***************************************************************************************************
*	Description:  This function turns the robot LED ON											   *
*	Arguments:    None		 																	   * 
*																								   *				   
***************************************************************************************************/
void LCR_LedON()
{
	digitalWrite(2, HIGH);
}
/************************************************************************************************
*	Description:  This function turns the robot LED OFF						      				*
*	Arguments: None 																			*				
*	 																							*				   
************************************************************************************************/
void LCR_LedOFF()
{
	digitalWrite(2, LOW);
}

/***************************************************************************************************
*	Description:  With this function you can make sounds with the robot							   *
*	Arguments:  																				   *				
*	 	- Note:	  Musical note that you want reproduce											   *
*					 DO  	523 Hz															       *
*					 DOS 	554 Hz															   	   *
*					 RE		587 Hz															       *
*					 RES	622 Hz															       *
*					 MI		659 Hz															       *	
*					 FA		698 Hz															       *
*					 FAS	739 Hz															       *
*					 SOL	783 Hz															       *
*					 SOLS	830 Hz															       *
*					 LA		880 Hz															       *	
*					 LAS	932 Hz															       *		
*					 SI		987 Hz					   										       * 
*		- Time: Miliseconds we want to reproduce the sound										   *
*	This function works like "tone" Adruino's function											   *						 
***************************************************************************************************/

void LCR_Sound(unsigned int note, unsigned int time)
{
	tone (8,note,time);
}

/************************************************************************************************
*	Description:  Stops the sound							      								*
*	Arguments: None  																			*				
*	 																							*				   
************************************************************************************************/
void LCR_NoSound()
{
	noTone(8);
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

/***************************************************************************************************
*	Description:  This function can read from both light sensors, light up a LED (external and	   * 
*				  connected at digital connector 1) acording with the light level read by the      *
*				  sensor and send the read value to the serial port								   *
*	Arguments:  																				   *				
*	 	- Sensor: 		0 = Right Sensor														   *	
*						1 = Left Semsor														   	   *
*	Return:		  Return the value of the lignt measure											   *
*
*	By deffect read from right sensor
*																								   * 				   
***************************************************************************************************/

int LCR_LightLED(bool sensor)
{
	int measure;
	pinMode(13,OUTPUT);
	
	if (sensor == 0)
	{
	   measure = analogRead(A0);
	   analogWrite(13,map(measure, 0, 1023, 0, 255));
	   Serial.print("Right sensor value=  ");
	   Serial.println(measure);
	   delay(250);
	}
	else 
	{
	   measure = analogRead(A1);
	   analogWrite(13,map(measure, 0, 1023, 0, 255));
	   Serial.print("Left sensor value=  ");
	   Serial.println(measure);
	   delay(250);
	}
  return measure;
}

/***************************************************************************************************
*	Description:  This function can read from both light sensors, turn ON-OFF the LED in function  *
*				  to the read value and one trigger value selected by the usser and send the read  *
*				  value to the serial port														   *
*	Arguments:  																				   *				
*	 	- Sensor: 		0 = Right Sensor														   *	
*						1 = Left Sensor															   *	
*		- Trigger:		Value betwen 0-1024 selected by the user that is the limit betwen ON-OFF   *
*						LED status																   *	
*	Return:		  Return the value of the lignt measure											   *
*																								   *
*	By deffect read from the Right Sensor and set the trigger at 512							   *
*																								   * 				   
***************************************************************************************************/

int LCR_LightTrigger(bool sensor, int trig)
{
	int measure;
	
	if (sensor == 0)
	{
	   measure = analogRead(A0);
	   if (trig > measure)
	   {
		 digitalWrite(2, LOW);
	   }
	   else
	   {
		 digitalWrite(2, HIGH);
	   }
	   Serial.print("Right sensor value=  ");
	   Serial.println(measure);
	   delay(250);
	}
	else 
	{
	   measure = analogRead(A1);
	   if (trig > measure)
	   {
		 digitalWrite(2, LOW);
	   }
	   else
	   {
		 digitalWrite(2, HIGH);
	   }
	   Serial.print("Left sensor value=  ");
	   Serial.println(measure);
	   delay(250);
	}
  return measure;
}
/***************************************************************************************************
*	Description:  This function can read from both light sensors								   *
*	Arguments:  																				   *				
*	 	- Sensor: 		0 = Right Sensor														   *	
*						1 = Left Sensor															   *	
																								   *	
*	Return:		  Return the value of the lignt measure											   *
*																								   *
*	By deffect read from the Right Sensor and set the trigger at 512							   *
*																								   * 				   
***************************************************************************************************/

int LCR_LightSensor(bool sensor)
{
	int measure;
	measure = analogRead(sensor);
	return measure;
}


#endif
