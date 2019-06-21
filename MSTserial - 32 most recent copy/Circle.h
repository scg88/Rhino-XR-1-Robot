struct CPointXY{
	double X;
	double Y;
};

struct CPointXYZ{
	double X;
	double Y;
	double Z;
};


class Circle{
	private:
	   double Radius;

	public:
	   Circle(float Rad = 1);
	   void    setRadius(float Rad);
	   double  getRadius();
	   double  getArea();
	   double  getCirc();
	   double  getAngleSteps(double UnitStep);
	   double  getAngleFromXY(CPointXY XY);             // Get angle from XY
	   double  getAngleCord(double Cord);			   // Get angle offset by cood.
	   CPointXY getXYAngleHyp(double Angle, double Hyp);// Get XY from angle and hyp.
};
