
#ifndef LCR_h
#define LCR_h

#include "Arduino.h"

#define PPV 2048		//Number of the encoder pulses in one turn of the wheel

// Musical Notes
#define DO  	523
#define DOS 	554
#define RE	587
#define RES	622
#define MI	659
#define FA	698
#define FAS	739
#define SOL	783
#define SOLS	830
#define LA	880
#define LAS	932
#define SI	987

//Varables to count the pulses from the encoders
extern int countRIGHT;
extern int countLEFT;
//Variables to calculate the number of pulses we need to
//make any movement
extern int stepR;
extern int stepL;

class LCR{
	public:

		//Functions
		void LCR_Init();
		static void Encoder1LEFT();
		static void Encoder1RIGHT();
		int SetRate(int rate);
		int SetDistance(int dist);
		int SetDegrees(int deg);
		void LCR_Move(char* dir="FORWARDS", int SetDistance(0), int SetRate(0));
		void LCR_Turn(char* dir = "RIGHT", int SetDeg(10), int SetRate(0), bool mode = 0);
		void LCR_Stop ();
		void LCR_Sound(unsigned int note, unsigned int time = 0);
		void LCR_NoSound();
		void LCR_Delay(float seconds);
		void LCR_LedON();
		void LCR_LedOFF();

		int LCR_LightLED(bool sensor = 0);
		int LCR_LightTrigger(bool sensor = 0, int trig = 512);
		int LCR_LightSensor(bool sensor = 0);
		int LCR_Bumper(bool sensor = 0);
		int LCR_BumperLED(bool sensor = 0);
		void LCR_TestIRArray();
		void LCR_MotorL(int dir, int SetRate(0));
		void LCR_MotorR(int dir, int SetRate(0));
		void LCR_LineFollower(int threshold, int SetRate(0));
		bool LCR_IRArrayDetect(int treshold);
};

#endif
