#include <iostream>  //used for demo cout only remove for final vers
#include <Windows.h>
#include "IBMRobot.h"

          ///////////MOVEXY COMMAND FUNCTION//////////////
//////////////////////////////////////////////////////////////////
void IBMRobot::MoveXY(XYPoint pnt){

	char dataStr [40] = {0};             //Data string to send to IBM
	char chsum   [03] = {0};             //Holds  Cnvrt chksum nibble
	int  checksum     = 0x231;           //Summation hard coded chars
    FloatRec FloatData;                  //Flt pnt chars and sumation

    char roboStr1[] = "T";               //Teaching command character
	char* strPoint1 = roboStr1;
    Robo.sendArray(strPoint1, strlen(roboStr1));
    Sleep(80);
    FloatData = getFloatChars(&pnt.X);   //Cnvrt X val  to IBM string
	strcat(dataStr, "107021");           //70 for X and  21 for float
    strcat(dataStr, FloatData.chrFloat); //Concatinate flt characters
    checksum += FloatData.chrSum;        //Summation X flt characters

    FloatData = getFloatChars(&pnt.Y);   //Cnvrt X val  to IBM string
	strcat(dataStr, "3D7121");           //71 for Y and  21 for float
    strcat(dataStr, FloatData.chrFloat); //Concatinate flt characters
    checksum += FloatData.chrSum;        //Summation Y flt characters

	strcat(dataStr, "3D7321");           //Hard coded  final sequence

    //Numbers  start at  character 48(10) cap letters start at 65(10)
    chsum[0] = (checksum & 0x00F0) / 0x10;//Split nibbles to for csum
    chsum[0] = chsum[0] < 10 ? chsum[0] += 48 : (chsum[0] += 55);
    chsum[1] = (checksum & 0x000F);
	chsum[1] = chsum[1] < 10 ? chsum[1] += 48 : (chsum[1] += 55);
    strcat(dataStr,chsum);
    strcat(dataStr,"\r\n");
    std::cout << dataStr << std::endl;  //Demonstration output
    Robo.sendArray(dataStr, strlen(dataStr));
    Sleep(80);
    //Do it command
	strcpy(dataStr, "T05000000003E3E\r\n"); //04/10/17
	Robo.sendArray(dataStr, strlen(dataStr));
    std::cout << dataStr << std::endl;  //Demonstration output
}

    ///////////GET InteltoIBMFloat FLOAT FUNCTION//////////////
//////////////////////////////////////////////////////////////////
//Converts  post 1980  float to  pre-1980  format  using a  single
//statement (learn this skill in CS_8) Subtract  7f  from exponent
//add the 1  to the  fractional part and shift expoent left by one
//preservingthe sign bit.  All  accomplished  by bitwise and's and
//or's with a shift left by 1.The 0 is returned if the val happens
//to be zero.
unsigned int IBMRobot::InteltoIBMFloat(const void *fltVal)
{
 return(*(unsigned int*)fltVal)?
    ((((*(unsigned int*)fltVal)& 0x007Fffff) | 0x800000)|
      ((*(unsigned int*)fltVal)& 0x80000000))|
   (((((*(unsigned int*)fltVal)& 0xFF800000))- 0x3F000000)<< 1):0;
}

    ///////////GET getFloatChars  FUNCTION//////////////
//////////////////////////////////////////////////////////////////
//Comverts post-1980 floating point value  to pre-1980 form.  this
//function takes in a pntr to a  float and  returns the  post-1980
//float value in a record containing the character conversion of a
//floating point value in pre-1980 form and a sumation of all char
//acters.
FloatRec IBMRobot::getFloatChars(const void *fltVal)
{
   int           intCon ;      //Hold  converted flt in  char form
   int           sum = 0;      //Accumulate   the   character  sum
   unsigned int  mask = 0xf0000000; //Used  to  mask  each  nibble
   unsigned int  divf = 0x10000000; //Used  to shft nibble  to LSB
   char         *chrCon;       //Holds  nibble for  chr conversion
   char          working;      //Used  to  calculate character sum
   std::string   Commandstr;   //Holds  completed   command string
   FloatRec      FloatInfo;    //Structure to  return chr and csum

   intCon = InteltoIBMFloat(fltVal);         //Cnvrt to pre-80 IBM
   chrCon = reinterpret_cast<char*>(intCon); //chr pntr  to intCon

   //Split off each nibble using a bitwise then mult to put nibble
   //in LSB  position. If  less than 10, must  be number so add 48
   //else character so add 55 for capsappend to string.Need to add
   //up digits for check sum.
   for (int i = 1; i < 9; i++)
   {   //obtain check sum value for each digit
	   working = (int(chrCon)& mask) / divf;             //Get each nible from left to right
	   i%2 ? sum += (working * 0x10) : sum += (working); //Add value to sum for chksum calc.
	   //change 1-9, a-f to characters.. div by 10 then add 48 or 55??
	   working = working < 10 ? working+=48 : ((working += 55));
	   Commandstr.append(1,working);                    //Add individulalcharacter to string
	   mask /= 0X10;                                    //Div mask  and divf for next nibble
	   divf /= 0x10;
   }
   FloatInfo.chrSum = sum;                              //Store  character  sum
   strcpy(FloatInfo.chrFloat, Commandstr.c_str());      //Store flt char string
   return FloatInfo;
}


