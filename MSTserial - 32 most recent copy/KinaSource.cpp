#include "stdafx.h"
#include "KinaMath.h"
#include<cmath>


void KinaMath::setAngle2(XYPair XYPoint)
{

	//Angle1_2.Angle2 = acos(((pow(XYPoint.X, 2.0) + pow(XYPoint.Y, 2.0)) - ((Len1*Len1) - (Len2*Len2))) / (2 * (Len1*Len2)));
	Angle1_2.Angle2 = atan((XYPoint.X / XYPoint.Y));
	//Angle1_2.Angle2 = acos(1);
	Angle1_2.Angle2 = (Angle1_2.Angle2 * 180) / M_PI;
}


void KinaMath::setAngle1(XYPair XYPoint)
{
	Angle1_2.Angle1 = asin((Len2 * sin(Angle1_2.Angle2)) / (sqrt(pow(XYPoint.X, 2.0) + (pow(XYPoint.Y, 2.0))))) + atan((XYPoint.Y / XYPoint.X));
	//Angle1_2.Angle1 = acos(0);
	Angle1_2.Angle1 = (Angle1_2.Angle1 * 180) / M_PI;

}

AnglePair KinaMath::getAnglePair(XYPair XYPoint)
{
	setAngle2(XYPoint);
	setAngle1(XYPoint);

	AnglePair Temp = { Angle1_2.Angle2, Angle1_2.Angle1 };

	return Temp;
}