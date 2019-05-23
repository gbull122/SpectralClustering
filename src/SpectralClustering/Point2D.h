#pragma once

class Point2D
{
private:
	double xval;
	double yval;

public:
	explicit Point2D(double x=0,double y=0);
	double dist(Point2D other);
	~Point2D(void);
};


