
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include "Line.h"
using namespace std;

Line::Line(float Len){ Length = Len;}
double Line::getLength(){return Length;}
void   Line::setLength(PointXY Pt1, PointXY Pt2) //see page 153
{
      double XLen;
      double YLen;
      if((Pt1.X <= 0 && Pt2.X  < 0) && (Pt1.Y <= 0 && Pt2.Y  < 0) ||
         (Pt1.X  < 0 && Pt2.X <= 0) && (Pt1.Y  < 0 && Pt2.Y <= 0))
	  {
	  	     XLen = abs(Pt2.X -  Pt1.X);
	  	     YLen = abs(Pt2.Y -  Pt1.Y);
	  	     Length = (sqrt(pow((XLen),2) + pow((YLen),2)));
	  	     if(abs(Pt2.Y) > abs(Pt1.Y)  && abs(Pt2.X) > abs(Pt1.X)) Length = -Length;
	  }
      else
      if((Pt1.X >= 0 && Pt2.X >  0) && (Pt1.Y <= 0 && Pt2.Y <  0) ||
         (Pt1.X >  0 && Pt2.X >= 0) && (Pt1.Y <  0 && Pt2.Y <= 0))
	  {
	     XLen = abs(Pt2.X -  Pt1.X);
	     YLen = abs(Pt1.Y -  Pt2.Y);
	     Length = (sqrt(pow((XLen),2) + pow((YLen),2)));
	     if(abs(Pt2.Y) > abs(Pt1.Y)  && abs(Pt2.X) > abs(Pt1.X)) Length = -Length;
	  }
      else
     {
      if(Pt1.X < 0)
		  if(Pt2.X < 0)
		    XLen =  Pt1.X -  Pt2.X;
	      else
	        XLen = -Pt1.X +  Pt2.X;
	  else
		  if(Pt2.X < 0)
		    XLen =  Pt1.X + -Pt2.X;
		  else
	        XLen =  Pt1.X -  Pt2.X;

	  if(Pt1.Y < 0) //neg
	  	  if(Pt2.Y < 0)
	  	    YLen =  Pt1.Y +  Pt2.Y;
	  	  else
	  	    YLen = -Pt1.Y -  Pt2.Y;
      else
	  	  if(Pt2.Y < 0)
	  	    YLen =  Pt1.Y + -Pt2.Y;
	  	  else
	  	    YLen =  Pt1.Y -  Pt2.Y;
	  Length = sqrt(pow((XLen),2) + pow((YLen),2));
	  if(abs(Pt2.Y) < abs(Pt1.Y)  && abs(Pt2.X) < abs(Pt1.X)) Length = -Length;
   }
}

PointXY Line::getNextPt(double Angle, PointXY Start, double Dist)
{
   PointXY ReturnXY;
   ReturnXY.Y = (Dist * cos( Angle * (M_PI  / 180 )))+ Start.Y;
   ReturnXY.X = (Dist * sin( Angle * (M_PI  / 180 )))+ Start.X;
   return ReturnXY;
}

double Line::getAngleFromXY(PointXY Pt1, PointXY Pt2)
{
   double Rads = atan((Pt2.X-Pt1.X) / (Pt2.Y-Pt1.Y));
   return (180/M_PI) * Rads;
}

double  Line::getLineSteps(double UnitStep)
{
	 return abs(int(Length / UnitStep));
}













