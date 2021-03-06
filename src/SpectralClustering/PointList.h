#pragma once

#include <map>
#include <utility>
#include "Point2D.h"
#include <iostream>

class PointList
{
private:
	std::map<int, Point2D> points;

public:
	PointList(void);
	~PointList(void);
	int Count();
	Point2D GetPoint(int index);
	Point2D GetNearestPoint(int k, Point2D aPoint);
	void Add(Point2D aPoint);
};

