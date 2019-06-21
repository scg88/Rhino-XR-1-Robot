//Common  record  used to  hold X,Y coordinate pair for
//use by MoveXY method;
struct XYPoint
{
	float X;
	float Y;
};

//Common record used to  hold  character representation
//of pre-1980 floating point  number required to create
//IBM robot move command and sumation of all characters
struct FloatRec{
	char chrFloat[9];   //Char representation  of float
	int  chrSum;        //Integer  summation  of  chars
};

class baseRobot
{
   private:

   public:
	 virtual void  MoveXY(XYPoint)  = 0;
};