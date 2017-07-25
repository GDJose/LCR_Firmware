
#include <Arduino.h>
#include <LCR.h>


//Variables
int countRIGHT =0;
int countLEFT =0;
int stepR = 0;
int stepL = 0;

volatile int finishMove = 1;	//Variable to indicate the movement has been finished

/************************************************************************************************
*	Description:  This function initialize the standard configuration for the LCR		*
*	Arguments: None 									*
*												*
************************************************************************************************/

void LCR::LCR_Init()
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
  pinMode(13,INPUT);  //Modulino Connector 2
  pinMode(4,INPUT);   //Modulino Connector 1
  pinMode(8, OUTPUT);  //Piezzo
  pinMode(A0, INPUT);  //Right Analog sensor
  pinMode(A1, INPUT);  //Left Analog sensor
  pinMode(A2, INPUT);  //IRArray 3
  pinMode(A3, INPUT);  //IRArray 2
  pinMode(A4, INPUT);  //IRArray 1

}
/************************************************************************************************
*	Description:  These functions increase the number of pulses while the wheels are moving *
*				  and update the flag that indicate the movement is ended	*
*	Arguments: None									        *
*												*
************************************************************************************************/
void LCR::Encoder1LEFT()
{
  countLEFT+=1;
  if (countLEFT >= stepL)
	  finishMove = 0;
}

void LCR::Encoder1RIGHT()
{
  countRIGHT+=1;
   if (countRIGHT >= stepR)
	  finishMove = 0;
}

/************************************************************************************************
*	Description:  This function set the value of the speed which the motor will be moved	*
*	Arguments: 									        *
*		- Rate:	Number between 0 and 100 that indicate the % speed which the 		*
*			robot is going to move.							*
*												*
************************************************************************************************/
int LCR::SetRate(int rate)
{
   if (rate > 100)
    {
	rate = 100;
     }
   else if (rate < 0)
    {
	rate = 0;
    }
  return rate;
}

/************************************************************************************************
*	Description:  This function set the value of the distance that the robot will be moved	*
*	Arguments: 									        *
*		- dist:	Number between 0 and 10000 that indicate the % speed which the 		*
*			robot is going to move.							*
*												*
************************************************************************************************/
int LCR::SetDistance(int dist)
{
   if (dist > 10000)
    {
	dist = 10000;
     }
   else if (dist < 0)
    {
	dist = 0;
    }
  return dist;
}

/************************************************************************************************
*	Description:  This function set the value of the degrees that the robot will be turned	*
*	Arguments: 									        *
*		- Rate:	Number between 0 and 100 that indicate the % speed which the 		*
*			robot is going to move.							*
*												*
************************************************************************************************/
int LCR::SetDegrees(int deg)
{
   if (deg > 360)
    {
	deg = 360;
     }
   else if (deg < 10)
    {
	deg = 10;
    }
  return deg;
}

/************************************************************************************************
*	Description:  This function moves forward and backward the robot			*
*	Arguments:										*
*	 	- Dir:		 	FORWARDS = Forwards					*
*					BACKWARDS = Backwards					*
					FORWARD	BACKWARD					*
*		- Distance: 	Distance in mm we want to move the robot			*
*		- Rate:		Number between 0 and 100 that indicate the % speed which the 	*
*				robot is going to move.						*
*	By deffect the values are:	0 -> Forward						*
*					160 -> 16 cm.						*
*					25 -> 25% of the max. speed				*
*	To select the values by deffect is no neccesary put any argument between brackets	*
************************************************************************************************/

void LCR::LCR_Move (String dir, int distance, int rate )
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
  if (dir == "FORWARDS")
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

/********************************************************************************************************
*	Description:  This function turns the robot right and left(using diferent ways(not ready yet)) 	*
*	Arguments: 		       								       	*
*	 	- Dir: 			0 = Turn Right 						       	*
*					1 = Turn Left 					   	       	*
*		- Distance: 	Degrees to turn  							*
*		- Rate:			Number between 0 and 100 that indicate the % speed which the 	*
*						robot is going to move.					*
*		- Mode:			0 = Turn taking like origin the center between the motors	*
*					1 = Using a wheel like centre of the movement (not ready yet)	*
*													*
*	By deffect the values are:	0 -> Right  							*
*					90 -> 90 degrees						*
*					25 -> 25% of the max. speed					*
*					0 -> Turn taking like origin the center between the motors	*
*	To select the values by deffect is no neccesary put any argument between brackets		*
********************************************************************************************************/

void LCR::LCR_Turn (String dir, int deg, int rate, bool mode )
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
    if (dir == "RIGHT")
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
*	Description:  This function stops the robot and reset all the variables that use to     *
*		      make movements								*
*	Arguments: None										*
*												*
************************************************************************************************/
void LCR::LCR_Stop ()
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
*	Description:  This function turns the robot LED ON					   *
*	Arguments:    None									   *
*												   *
***************************************************************************************************/
void LCR::LCR_LedON()
{
	digitalWrite(2, HIGH);
}
/************************************************************************************************
*	Description:  This function turns the robot LED OFF       				*
*	Arguments: None										*
*												*
************************************************************************************************/
void LCR::LCR_LedOFF()
{
	digitalWrite(2, LOW);
}

/***************************************************************************************************
*	Description:  With this function you can make sounds with the robot			   *
*	Arguments: 										   *
*	 	- Note:	  Musical note that you want reproduce					   *
*					 DO  	523 Hz						   *
*					 DOS 	554 Hz					   	   *
*					 RE	587 Hz						   *
*					 RES	622 Hz  					   *
*					 MI	659 Hz 						   *
*					 FA	698 Hz						   *
*					 FAS	739 Hz 						   *
*					 SOL	783 Hz						   *
*					 SOLS	830 Hz						   *
*					 LA	880 Hz						   *
*					 LAS	932 Hz						   *
*					 SI	987 Hz 						   *
*		- Time: Miliseconds we want to reproduce the sound 				   *
*	This function works like "tone" Adruino's	function				   *
***************************************************************************************************/

void LCR::LCR_Sound(unsigned int note, unsigned int time)
{
	tone (8,note,time);
}

/************************************************************************************************
*	Description:  Stops the sound 								*
*	Arguments: None 									*
*												*
************************************************************************************************/
void LCR::LCR_NoSound()
{
	noTone(8);
}

/************************************************************************************************
*	Description:  This function delays the robot		      				*
*	Arguments: 										*
*		- Seconds: Number of senconds we want delay					*
*												*
************************************************************************************************/
void LCR::LCR_Delay(float seconds)
{
	delay(seconds*1000);
}



/***************************************************************************************************
*	Description:  This function can read from both light sensors, light up a LED (external and *
*		      connected at digital connector 1) acording with the light level read by the  *
*		      sensor and send the read value to the serial port				   *
*	Arguments: 										   *
*	 	- Sensor: 		0 = Right Sensor					   *
*					1 = Left Semsor					   	   *
*	Return:		  Return the value of the lignt measure					   *
*												   *
*	By deffect read from right sensor							   *
***************************************************************************************************/

int LCR::LCR_LightLED(bool sensor)
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

/********************************************************************************************************
*	Description:  This function can read from both light sensors, turn ON-OFF the LED in function   *
*		      to the read value and one trigger value selected by the usser and send the read   *
*		      value to the serial port			  					*
*	Arguments: 											*
*	 	- Sensor: 		0 = Right Sensor						*
*					1 = Left Sensor							*
*		- Trigger:		Value betwen 0-1024 selected by the user that is the limit 	*
					betwen ON-OFF LED status					*
*	Return:		  Return the value of the lignt measure						*
*													*
*	By deffect read from the Right Sensor and set the trigger at 512				*
*													*
********************************************************************************************************/

int LCR::LCR_LightTrigger(bool sensor, int trig)
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
*	Description:  This function can read from both light sensors				   *
*	Arguments: 										   *
*	 	- Sensor: 		0 = Right Sensor					   *
*					1 = Left Sensor						   *
												   *
*	Return:		  Return the value of the lignt measure					   *
*												   *
***************************************************************************************************/

int LCR::LCR_LightSensor(bool sensor)
{
	int measure;
	measure = analogRead(sensor);
	return measure;
}

/***************************************************************************************************
*	Description:  This function can read from both bumpers or any digital sensor		   *
*	Arguments: 										   *
*	 	- Sensor: 		0 = Right Bumper					   *
*					1 = Left Bumper						   *
												   *
*	Return:		  Return the value of the lignt measure					   *
*												   *
*	By deffect read from the Right Bumper							   *
*												   *
***************************************************************************************************/

int LCR::LCR_Bumper(bool sensor)
{
	int measure;
	if (sensor == 0)
	{
	  measure = digitalRead(13);
	}
	else
	{
		measure = digitalRead(4);
	}
	return measure;
}

/********************************************************************************************************
*	Description:  This function can read from both bumpers and light up the LED acording with the   *
*		      status of the bumper 	  						        *
*	Arguments: 											*
*	 	- Sensor: 		0 = Right Bumper						*
*					1 = Left Bumper							*
*													*
*	Return:		  Return the value of the lignt measure						*
*													*
*	By deffect read from the Right Bumper 								*
*							   					       	*
********************************************************************************************************/

int LCR::LCR_BumperLED(bool sensor)
{
	int measure;
	if (sensor == 0)
	{
	  measure = digitalRead(13);
	  digitalWrite(2, measure);
	}
	else
	{
	  measure = digitalRead(4);
	  digitalWrite(2, measure);
	}
	return measure;
}

/********************************************************************************************************
*	Description:  This function read the value of the IRArray sensors and send it to the seriial   	*
*		      port						       			       	*
*	Arguments: None 										*
*													*
********************************************************************************************************/
void LCR::LCR_TestIRArray()
{
  Serial.println("Sensor Izda   |   Sensor Centro   |   Sensor Dcha   |");
  Serial.println("----------------------------------------------------|");
    Serial.print("     ");
    Serial.print(analogRead(A4));
    Serial.print("      |        ");
    Serial.print(analogRead(A3));
    Serial.print("        |         ");
  Serial.print(analogRead(A2));
  Serial.println("     |");
  Serial.println("----------------------------------------------------|");
}

/***************************************************************************************************
*	Description:  This function return 1 when any of the 3 IR sensors read bigger values than  *
*		      threshold, if read lower, return 0					   *
*	Arguments:  None									   *
*												   *
***************************************************************************************************/
bool LCR::LCR_IRArrayDetect(int threshold)
{
	int measure;
	int s1, s2, s3;
	measure = analogRead(A4);
	s1 = measure > threshold ? 1 : 0;
	measure = analogRead(A3);
	s2 = measure > threshold ? 1 : 0;
	measure = analogRead(A2);
	s3 = measure > threshold ? 1 : 0;

	return s1|s2|s3;
}
/***************************************************************************************************
*	Description: This funcction moves separately the Left motor   			           *
*	Arguments: 										   *
*		- Dir: Set the movement direction of the motor					   *
*				!=1 && != 2  -->  Motor Stop					   *
*				1 	     -->  Motor Forward					   *
*				2            -->  Motor Backward 				   *
*		- Rate: Number between 0 and 100 that indicate the % speed which the  		   *
*			robot is going to move.							   *
*				 				  				   *
***************************************************************************************************/
void LCR::LCR_MotorL(String dir, int rate)
{
	if (rate == 0) rate = 25;
	rate = map (rate, 100, 0, 0,230);

	if (dir == "FORWARDS")
	{
	 digitalWrite(9, HIGH);
     analogWrite (3, rate);
	}
	else if (dir == "BACKWARDS")
	{
	 digitalWrite(3, HIGH);
     analogWrite (9, rate);
	}
	else
	{
	 digitalWrite(9, HIGH);
     digitalWrite(3, HIGH);
	}
}

/***************************************************************************************************
*	Description: This funcction moves separately the Right motor				   *
*	Arguments: 										   *
*		- Dir: Set the movement direction of the motor					   *
*				!=1 && != 2  -->  Motor Stop					   *
*				1 	     -->  Motor Forward					   *
*				2            -->  Motor Backward				   *
*		- Rate: Number between 0 and 100 that indicate the % speed which the  		   *
*			robot is going to move.							   *
*				 				   				   *		***************************************************************************************************/
void LCR::LCR_MotorR(String dir, int rate)
{
	if (rate == 0) rate = 25;
	rate = map (rate, 100, 0, 0,230);

	if (dir == "FORWARDS")
	{
	 digitalWrite(5, HIGH);
     analogWrite (6, rate+3);
	}
	else if (dir == "BACKWARDS")
	{
	 digitalWrite(6, HIGH);
     analogWrite (5, rate);
	}
	else
	{
	 digitalWrite(5, HIGH);
     digitalWrite(6, HIGH);
	}
}

/***************************************************************************************************
*	Description:     									   *
*	Arguments: 										   *
*												   *
***************************************************************************************************/
void LCR::LCR_LineFollower(int threshold, int rate)
{
  int measure;
  if (rate == 0) rate = 25;
	rate = map (rate, 100, 0, 0,230);

  measure = analogRead(A4);
  if (measure > threshold)
  {
	  LCR_MotorL(1);
  }
  else
  {
	  LCR_MotorL(0);
  }
  measure = analogRead(A2);
  if (measure > threshold)
  {
	  LCR_MotorR(1);
  }
  else
  {
	 LCR_MotorR(0);
  }
}
