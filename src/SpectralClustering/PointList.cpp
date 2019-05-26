#include "PointList.h"


PointList::PointList(void)
{
}


PointList::~PointList(void)
{
}

int PointList::Count()
{
	return points.size();
}

void PointList::Add(Point2D aPoint)
{
	int count = points.size();
	points[count] = aPoint;
}

Point2D PointList::GetPoint(int index)
{
	return points.at(index);
}

Point2D PointList::GetNearestPoint(int k, Point2D aPoint)
{
	std::map<double, int> distances;
	for (std::map<int, Point2D>::iterator ii = points.begin(); ii != points.end(); ++ii)
	{
		double dist = aPoint.dist((*ii).second);
		distances[dist] = (*ii).first;
	}
	std::map<double, int>::iterator itr;
	//get the kth item
	int d;
	if (k - 1 < distances.size())
	{
		itr = distances.begin();
		std::advance(itr, k -1);
		d = itr->second;
	}
	return points[d];
}
