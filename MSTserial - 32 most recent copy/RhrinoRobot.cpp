#include "RhrinoRobot.h"
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <strstream>
#include <string>
#include <iomanip>
using namespace std;

bool RhrinoRobot::switchstatus(char mot)
{
	char mask = pow(2, mot - 'C');
	Sleep(5);
	handle1 << "I"; //Send Inquery command
	Sleep(5);
	return (handle1.getChar() - 32) & mask;
}

int RhrinoRobot::motorstatus(char mot)
{
	char status[3]; //Created a 3 element character array
	status[0] = mot;//List the motor servo
	status[1] = '?';//Send question 
	Sleep(5);
	handle1 << status;// << '?';
	Sleep(5);
	return handle1.getChar() - 32;
}

bool RhrinoRobot::home()
{
	bool switchstatusjj;
	int motorcount;
	//HOME FUNCTION//////////////////////////////////////////////////////////
	while (switchstatus('E')) // loops until user sends motor E to home
	{

		handle1 << "E-5";
		switchstatusjj = switchstatus('E');
		cout << "Switch Status: " << switchstatusjj;
		while (motorcount = motorstatus('E'))
			cout << "Motor Status : " << motorcount << endl;
	}
	system("pause");

	while (switchstatus('D')) // loops until user sends motor D to home
	{

		handle1 << "D+5";
		switchstatusjj = switchstatus('D');
		cout << "Switch Status: " << switchstatusjj;
		while (motorcount = motorstatus('D'))
			cout << "Motor Status : " << motorcount << endl;
	}
	system("pause");
	return 0;
	//////////////////////////////////////////////////////////////////////////
	//	}
}

// Move to Function////////
int RhrinoRobot::move(AnglePair moveto , AnglePair from) // input a pair of angles to move to
{
	strstream temp;
	float moveAngle2; // holds converted value (servo Ticks to destination angle)
	float moveAngle1;
	float TotalMove1; // hold total incruments reqired for destination (by count of 5)
	float TotalMove2;
	int result2;
												// 750 = home
	moveAngle2 = ((from.Angle2 - moveto.Angle2 )/ (0.12));// Convert angles to movement (servo moves in incruments of .12 deg total 750)
	moveAngle1 = ((from.Angle1 - moveto.Angle1) / (0.12));// Convert angles to servo ticks (servo moves in incruments of .12 deg total 750)
	
	moveAngle2 = roundf(moveAngle2, 0);//Round off converted values
	moveAngle1 = roundf(moveAngle1, 0);//Round off converted Values

	cout << "Servo counts to (Destination Angle1): " << moveAngle1 << endl;
	cout << "Servo counts to (Destination Angle2): " << moveAngle2 << endl;
	
	moveAngle2 = moveAngle2 / 5;       // devide by five for incrumentation
	TotalMove2 = roundf(moveAngle2, 0);//Round off converted values

	moveAngle1 = moveAngle1 / 5;       // devide by five for incrumentation
	TotalMove1 = roundf(moveAngle1, 0);//Round off converted values

	cout << TotalMove1 << " incruments of 5 to reach Destination Angle1" << endl;
	cout << TotalMove2 << " incruments of 5 to reach Destination Angle2" << endl;

	while (TotalMove1 != 0)
	{
		if (TotalMove1 > 0)
		{

			handle1 << "E+5 ";  // E Motor First
			cout << TotalMove1 << " ";
			TotalMove1 -= 1;
			system("pause");
		}

		if (TotalMove1 < 0)
		{

			handle1 << "E-5 ";  // E Motor First
			cout << TotalMove1 << " ";
			TotalMove1 += 1;
			system("pause");
		}
	}
	cout << endl;

	while (TotalMove2 != 0)
	{
		if (TotalMove2 > 0)
		{
			handle1 << "D+5 ";  // D Motor Second
			cout << TotalMove2 << " ";
			TotalMove2 -= 1; // counts down total movement in incruments of five
			system("pause");
		}
		if (TotalMove2 < 0)
		{
			handle1 << "D-5 ";  // D Motor Second
			cout << TotalMove2 << " ";
			TotalMove2 += 1; // counts down total movement in incruments of five
			system("pause");
		}

	}


	return 0;
}