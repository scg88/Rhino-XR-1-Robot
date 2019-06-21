#ifndef IBMROBOT_H
#define IBMROBOT_H
#include "baseRobot.h"
#include "tserial.h"

//Driver class for IBM robot pre-1980 floating convert
//required to compose command message. Constructor req
//commport in C-String format. MoveXY takes in  struct
//cord point pair to command robot arm.
class IBMRobot : public baseRobot
{
   private:
     Tserial Robo;     //Open serial communication port
     FloatRec getFloatChars(const void *fltVal);
     unsigned int InteltoIBMFloat(const void *fltVal);
   public:
     IBMRobot(char *ComPort){Robo.connect(ComPort,4800, spEVEN);}
	 void  MoveXY(XYPoint); //Virtual function to be overriden
};

#endif IBMROBOT_H