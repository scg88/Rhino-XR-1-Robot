#include<iostream>
#include<string.h>
#include<iomanip>
#include <Windows.h>
#include "KinaMath.h"
#include "RhrinoRobot.h"
#include "line.h"
#include "IBMRobot.h"
#include <string>
#include "Circle.h"
using namespace std;




int main()
{
	RhrinoRobot robot("COM1");
	IBMRobot BigYellow("COM1"); //Instance  of  sample IBMRobot Provided
	//int motorcount;
	//bool switchstatus;
	char test[20]; // Elements for RhinoRobot
	char choice;
	int input;
	choice = 'Y';
	PointXY Ptret; // Elements for line.h
	double angle;
	double distance;
	double unitmove = 0;
	double inc = .1;
	int    steps;
	Line LineTest;
	XYPoint  movePnt; //Hold  X,Y point for traversal for IBMRobot

	KinaMath Robot1(9.0, 9.0);
	XYPair Pair1;     //Home Point
	Pair1.Y = 9;	  //Structure syntax
	Pair1.X = 9;

	XYPair Pair2;     //Destination point (example point for moveto function / line function)
	Pair2.Y = 8;     // 750 is the max number of movements between 90 deg.
	Pair2.X = 8; 

	AnglePair AnglePair1; // get angle pairs for both points
	AnglePair AnglePair2;
	AnglePair1 = Robot1.getAnglePair(Pair1); //home angle (Returned in degrees)
	AnglePair2 = Robot1.getAnglePair(Pair2); //Destination Angle


	//Main Menu Loop///////////////////////////////////////////////////
	do
	{	
		system("CLS");
		cout << "Enter a Numbered Option to use the Robot: " << endl << endl;
		cout << "1) Move a Motor on the Robot" << endl;
		cout << "2) Home the Robot" << endl;
		cout << "3) Move the Robot to a Destination point" << endl;
		cout << "4) Draw a Line with the Robot" << endl;
		cout << "5) Draw a Circle with the Robot" << endl;
		cout << "6) Use IBM Yellow robot " << endl;
		cout << "0) Exit the Program" << endl;
		cout << endl << "Input: ";

		cin >> input;
		
		//Option 1: Function for moving a Motor/////
		if (input == 1)      
		{
			while (choice != 'N')
			{
				cout << "\n Enter 'Y' to move a motor, or enter 'N' to Exit" << endl;
				cout << "Input: ";
				cin >> choice;
				switch (choice)
				{
				case 'Y':
					cout << "Motor input: ";
					cin >> test;
					robot << test;
				}

			}
			choice = 'Y'; //reset choice
		}

		//Option 2: Robot Homing Funciton/////////
		if (input == 2)
		{
			robot.home();
		}
		
		//Option 3: Move Robot to Given Point/////
		if (input == 3)
		{
			cout << "Enter a new destination point (X Y):"<< endl;
			cout << "X: " ;
			cin >> input;
			Pair2.X = input;

			cout << "Y: ";
			cin >> input;
			Pair2.Y = input;

			AnglePair2 = Robot1.getAnglePair(Pair2); //Destination Angle
			cout << "Home Point  :" << "(" << Pair1.X << " " << Pair1.Y << ")" << endl;  // (X,Y)
			cout << "Home Angle 1: " << AnglePair1.Angle1 << endl;
			cout << "Home Angle 2: " << AnglePair1.Angle2 << endl << endl;

			cout << "Destination Point  :" << "(" << Pair2.X << " " << Pair2.Y << ")" << endl;
			cout << "Destination Angle 1: " << AnglePair2.Angle1 << endl;
			cout << "Destination Angle 2: " << AnglePair2.Angle2 << endl << endl;
			robot.move(AnglePair2, AnglePair1);  //(moveto Angle , from Angle)
			system("pause");
		}

		//Option 4: Robot Line Function///////////
		if (input == 4)
		{
			//robot.home();
			PointXY LinePair1;    //starting point for line
			LinePair1.X = Pair1.X;
			LinePair1.Y = Pair1.Y;
			PointXY LinePair2;    //Endpoint for Line
			LinePair2.X = Pair2.X;
			LinePair2.Y = Pair2.Y;

			LineTest.setLength(LinePair1, LinePair2);             // Memeber functions for line.h
			angle = LineTest.getAngleFromXY(LinePair1, LinePair2);
			distance = LineTest.getLength();
			steps = LineTest.getLineSteps(inc);

			cout << endl << "Line function: " << endl;
			cout << "    Length: " << distance << endl;
			cout << "    Angle : " << angle << endl;
			cout << "Unit Steps: " << steps << endl << endl;

			for (int i = 0; i < steps; i++)
			{
				Ptret = LineTest.getNextPt(angle, LinePair1,        //Nest point
					unitmove += (distance > unitmove ? inc : -inc));
				Pair2.X = Ptret.X; // set destination to result of next point
				Pair2.Y = Ptret.Y;
				AnglePair2 = Robot1.getAnglePair(Pair2); //new Destination Angle

				cout << "Moving To: ";
				cout << fixed << setprecision(2) << showpoint
					<< "            (X: " << setw(6) << Ptret.X << " "
					<< " Y: " << setw(6) << Ptret.Y << ")" << endl;

				cout << "Current Point  :" << "(" << Pair1.X << " " << Pair1.Y << ")" << endl;  // (X,Y)
				cout << "Current Angle 1: " << AnglePair1.Angle1 << endl;
				cout << "Current Angle 2: " << AnglePair1.Angle2 << endl << endl;

				cout << "Destination Point  :" << "(" << Pair2.X << " " << Pair2.Y << ")" << endl;
				cout << "Destination Angle 1: " << AnglePair2.Angle1 << endl;
				cout << "Destination Angle 2: " << AnglePair2.Angle2 << endl << endl;


				robot.move(AnglePair2, AnglePair1);      //(moveto Angle , from Angle)
				Pair1 = Pair2;
				AnglePair1 = AnglePair2; // set destination as new home angle pair
			}
			// Just move to last point
			Ptret = LineTest.getNextPt(angle, LinePair1,        //Nest point
				unitmove += (distance > unitmove ? inc : -inc));
			Pair2.X = LinePair2.X; // set destination to result of next point
			Pair2.Y = LinePair2.Y;
			AnglePair2 = Robot1.getAnglePair(Pair2); //new Destination Angle

			cout << "Moving To: ";
			cout << fixed << setprecision(2) << showpoint
				<< "            (X: " << setw(6) << Ptret.X << " "
				<< " Y: " << setw(6) << Ptret.Y << ")" << endl;

			cout << "Current Point  :" << "(" << Pair1.X << " " << Pair1.Y << ")" << endl;  // (X,Y)
			cout << "Current Angle 1: " << AnglePair1.Angle1 << endl;
			cout << "Current Angle 2: " << AnglePair1.Angle2 << endl << endl;

			cout << "Destination Point  :" << "(" << Pair2.X << " " << Pair2.Y << ")" << endl;
			cout << "Destination Angle 1: " << AnglePair2.Angle1 << endl;
			cout << "Destination Angle 2: " << AnglePair2.Angle2 << endl << endl;

			robot.move(AnglePair2, AnglePair1);      //(moveto Angle , from Angle)
			system("pause");
		}

		//option 5 Draw a circle  
////////------------WARNING: Arcs past the reach of the robot --------------- //////
		if (input == 5)
		{
			double difference;
			Circle Test(11.5);  //Set Radius from last class
			CPointXY Point1 = { 8.81, 7.39 };//{11.5, 0};
			//CPointXY Point1 = { 9, 9 };//{11.5, 0};
			CPointXY Point2 = { 11.5, 0 };
			Pair2.Y = Point1.Y;	  //move to initial circle position
			Pair2.X = Point1.X;
			AnglePair2 = Robot1.getAnglePair(Pair2); //home angle (Returned in degrees)

			cout << endl <<"Home Point  :" << "(" << Pair1.X << " " << Pair1.Y << ")" << endl;  // (X,Y)
			cout << "Destination Point  :" << "(" << Pair2.X << " " << Pair2.Y << ")" << endl << endl;
			robot.move(AnglePair2, AnglePair1);      //(moveto Angle , from Angle)
			
			AnglePair1 = AnglePair2;
			Pair1.Y = Pair2.Y;	  //new home
			Pair1.X = Pair2.X;

			cout << "  Circ:" << Test.getCirc() << endl;
			cout << Test.getAngleFromXY(Point1)
				<< " Initial Position  X:" << Point1.X << " Y:" << Point1.Y << endl;

			cout << "Unit steps  the circ: " << Test.getAngleSteps(.5) << endl;
			cout << "Circ around the circ: " << Test.getCirc() << endl << endl;
			cout << "Angle        X         Y" << endl;
			for (float x = Test.getAngleFromXY(Point1); x < 181; x += Test.getAngleSteps(.5))
			{
				
				Point2 = Test.getXYAngleHyp(x, Test.getRadius());
				if (x < 10)
					cout << fixed << " " << setprecision(2) << x;
				else
					cout << fixed << " " << setprecision(2) << x;
				cout << fixed << " " << setprecision(2) << setw(8) << right
					<< Point2.X << "  " << setw(8) << right << Point2.Y << endl;
				
				Pair2.Y = Point2.Y;	  //set new destination point
				Pair2.X = Point2.X;
				AnglePair2 = Robot1.getAnglePair(Pair2); //Destination angle (Returned in degrees)
				
				if (Pair2.X < 0) // break once 
				{
					break;
				}

				cout << endl << "Home Point  :" << "(" << Pair1.X << " " << Pair1.Y << ")" << endl;  // (X,Y)
		
				cout << "Destination Point  :" << "(" << Pair2.X << " " << Pair2.Y << ")" << endl << endl;
			
				
				robot.move(AnglePair2, AnglePair1);
				AnglePair1 = AnglePair2; // new home
				Pair1.Y = Pair2.Y;	  
				Pair1.X = Pair2.X;
			
				cout << endl;
				system("pause");
				
			}
			cout << "        X         Y" << endl;

			Point2 = { 11.5, 0 };
			cout << Test.getAngleFromXY(Point2)
				<< " Final Position  X:" << Point2.X << " Y:" << Point2.Y << endl;

			system("pause");

		}

		//Option 6: Input for IBM Yellow Bot /////
		if (input == 6)
		{
			while (1){
				double x, y; // Convert to mm
				// Enter a point within the robots working range of current robot
				std::cout << "Enter x,y point" << endl;
				std::cout << "x = "; std::cin >> movePnt.X;
				std::cout << "y = "; std::cin >> movePnt.Y;
				BigYellow.MoveXY(movePnt);//Working call to IBM robotic test unit
				//LittleGry.MoveXY(movePnt);//Example of your Rhino robot test call
				system("pause");
			}
		}
		
	} while (input != 0);
	
	//robot.home();
	system("pause");
	
	return 0;
}


