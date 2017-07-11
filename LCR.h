

#define PPV 2048		//Number of the encoder pulses in one turn of the wheel
#define PI 3.14159

//Varables to count the pulses from the encoders
extern int countRIGHT;
extern int countLEFT;
//Variables to calculate the number of pulses we need to
//make any movement
extern int stepR;
extern int stepL;



//Functions
void LCR_Init();
void LCR_Move(bool dir = 0, int distance = 0, int rate = 0);
void LCR_Turn(bool dir = 0, int deg = 0, int rate = 0, bool mode = 0);
void LCR_Stop ();
void Encoder1LEFT();
void Encoder1RIGHT();