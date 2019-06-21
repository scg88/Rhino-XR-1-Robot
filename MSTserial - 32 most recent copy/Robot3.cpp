#include<iostream>
#include<windows.h>
#include<string.h>
#include"Tserial.h"
using namespace std;

//

class robot{
   private:
     Tserial handle1;
     char   joint_to_move;
     double upper_bound;
     double lower_bound;
     double angluar_position;

     int  switchstatus(  );
	 int  motorstatus(   );
     bool home();
   public:
	 robot( Tserial hand ); // make this home
	 int move();
};


int main()
{
	Tserial robot;
	char test1[20];
	char wait1;
	char responce;
	int  mask = 2; // binary 0000 0010 for Port D

	robot.connect("COM5",9600, spEVEN);
    //cout << "Serial Handle: " << switchstatus('d', &robot) << endl;
    //cout << "Motor Status : " <<  motorstatus('d', &robot) << endl;
    while(1)
    {
  	  		Sleep(5);

	  		 robot << "D+1" ;
             //cout << "Motor Status : " <<  motorstatus('d', &robot) << endl;


	  		robot << "I";
	  		Sleep(5);
	  		robot >> wait1;
		    wait1 -= 32;
		    //wait1 = (robot.getChar() - 32);
	        cout  << "Responce: " << int(wait1)   << endl;

	        if (int(wait1) & mask )
	          cout << "Switch Opened" << endl;
	        else
	          cout << "Switch Closed" << endl;



			system("pause");
    }
	return 0;
}


  int robot::switchstatus(   )
	 {
	   	handle1 << joint_to_move;
	   	Sleep(5);
	 	return handle1.getChar() - 32;
     }

	int robot::motorstatus(   )
	{
		char status[2];
		status[0] = joint_to_move ;
		status[1] = '?';
	    handle1 << status;// << '?';
	    Sleep(5);
		return handle1.getChar() - 32;
	}