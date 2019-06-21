struct PointXY{
	double X;
	double Y;
};

struct PointXYZ{
	double X;
	double Y;
	double Z;
};


class Line{
	private:
	   double Length;

	public:
	   Line(float Length = 1);
	   double  getLineSteps(double UnitStep);            // Get Number of steps
	   double  getAngleFromXY(PointXY Pt1, PointXY Pt2); // Get angle from XY					// Return current length
	   PointXY getNextPt(double Angle, PointXY Start, double Distance);
   	   double  getLength();
   	   void    setLength(PointXY Pt1, PointXY Pt2);      // Set length of line

};
