#include "tserial.h"
#include "KinaMath.h"

template<class fltval>
fltval roundf(fltval fltin, int pos)
{
	strstream temp;   							 //Create a character stream
	temp << fixed << setprecision(pos) << fltin; //Store rounded value
	return atof(temp.str());			         //Convert to a floating type
}



class RhrinoRobot {
private:
	Tserial handle1;
public:
	RhrinoRobot(char* ComPort) { handle1.connect(ComPort, 9600, spEVEN); };
	bool switchstatus(char mot); //Temp public
	int motorstatus(char mot); //Tenp public
	bool home(); //To incorporate motor and switch status to home arm
	int move(AnglePair , AnglePair); //ASSUMES THE ROBOT IS AT HOME
	void operator << (char *ptr) { handle1 << ptr; };
};