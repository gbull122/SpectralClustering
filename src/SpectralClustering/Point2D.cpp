#include "Point2D.h"
#include <math.h>


Point2D::Point2D(double x, double y)
{
	xval = x;
	yval = y;
}

double Point2D::dist(Point2D other)
{
	double xd = xval - other.xval;
	double yd = yval - other.yval;
	return sqrt(xd * xd + yd * yd);
}

Point2D::~Point2D(void)
{
}