
#ifndef LCR_h
#define LCR_h

#include "Arduino.h"

#define PPV 2048		//Number of the encoder pulses in one turn of the wheel

// Musical Notes
#define C  	523
#define CS	554
#define D	587
#define DS	622
#define E	659
#define F	698
#define FS	739
#define G	783
#define GS	830
#define A	880
#define AS	932
#define B	987

//Movement direcction
#define FORWARDS 1
#define BACKWARDS 0
#define STOP 2
#define RIGHT	 1
#define LEFT	 0

//Defines for the NEO^PIXEL LEDs
#define PIN            2
#define NUMPIXELS      1

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
		void LCR_Move(int dir= FORWARDS, int distance=0, int rate=0);
		void LCR_Turn(int dir = RIGHT, int deg=0, int rate=0);
		void LCR_Stop();
		void LCR_Sound(unsigned int note, unsigned int time = 0);
		void LCR_NoSound();
		void LCR_Delay(float seconds);
		void LCR_LedColor(uint8_t r, uint8_t g, uint8_t b);
		void LCR_End();
		
		int LCR_LightLED(bool sensor = 0);
		int LCR_LightTrigger(bool sensor = 0, int trig = 512);
		int LCR_LightSensor(bool sensor = 0);
		int LCR_Bumper(bool sensor = 0);
		int LCR_BumperLED(bool sensor = 0);
		void LCR_TestIRArray();
		void LCR_MotorL(int dir, int rate = 0);
		void LCR_MotorR(int dir, int rate = 0);
		void LCR_LineFollower(int threshold, int rate = 0);
		bool LCR_IRArrayDetect(int threshold, int sensor = 0);
};

#endif
