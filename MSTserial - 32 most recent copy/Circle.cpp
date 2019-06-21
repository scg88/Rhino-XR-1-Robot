
#define _USE_MATH_DEFINES
#include <math.h>
#include "Circle.h"

Circle::Circle(float Rad){ Radius = Rad;}
double Circle::getRadius(){return Radius;}
void   Circle::setRadius(float Rad){ Radius = Rad;}
double Circle::getArea(){return 2 * pow(M_PI, 2.0);}
double Circle::getCirc(){return 2 * M_PI * Radius;}

double Circle::getAngleFromXY(CPointXY XY)
{
   double Rads = atan(XY.Y/XY.X);
   return (180/M_PI) * Rads;
}

double Circle::getAngleCord(double Cord)
{
    return (180/M_PI) * (cos(2* pow(Radius,2.0) - pow(Cord,2.0)));
}

double  Circle::getAngleSteps(double UnitStep)
{
	double circ = getCirc();
	return 360 / (circ / UnitStep);

}

CPointXY Circle::getXYAngleHyp(double Angle, double Hyp)
{
	CPointXY ReturnXY;
    ReturnXY.X = (Hyp * cos( Angle * (M_PI  / 180 )));
	ReturnXY.Y = (Hyp * sin( Angle * (M_PI  / 180 )));
	return ReturnXY;
}












