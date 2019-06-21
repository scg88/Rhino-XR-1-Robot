#pragma once

#ifndef KINAMATH_H
#define KINAMATH_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

struct XYPair
{
	double X;
	double Y;
};

struct AnglePair
{
	double Angle1;
	double Angle2;
};

class KinaMath
{
private:
	double Len1, // Lengh arm1 i picked english
		Len2; // Lengh arm2
	AnglePair Angle1_2; // Angle pair for return
	void setAngle2(XYPair XYPoint);
	void setAngle1(XYPair XYPoint);
public:
	KinaMath(double L1, double L2) { Len1 = L1; Len2 = L2; }
	AnglePair getAnglePair(XYPair XYPoint);
};
#endif