#include "pch.h"
#include "../SpectralClustering/PointList.h"

TEST(PointListTest, AddPoint)
{
	int expectedCount = 2;
	PointList pointList;

	Point2D point1(1,2);
	Point2D point2(3,4);

	pointList.Add(point1);
	pointList.Add(point2);

	int actualCount = pointList.Count();

	EXPECT_EQ(expectedCount, actualCount);
}

TEST(PointListTest, Nearest1)
{
	PointList pointList;

	Point2D point1(1, 2);
	Point2D point2(3, 4);
	Point2D point3(13, 14);

	Point2D expectedPoint = point1;

	pointList.Add(point1);
	pointList.Add(point2);
	pointList.Add(point3);

	Point2D actualPoint = pointList.GetNearestPoint(2, point2);

	EXPECT_EQ(expectedPoint.X(), actualPoint.X());
	EXPECT_EQ(expectedPoint.Y(), actualPoint.Y());
}

TEST(PointListTest, Nearest2)
{
	PointList pointList;

	Point2D point1(1, 2);
	Point2D point2(3, 4);
	Point2D point3(13, 14);

	Point2D expectedPoint = point3;

	pointList.Add(point1);
	pointList.Add(point2);
	pointList.Add(point3);

	Point2D actualPoint = pointList.GetNearestPoint(3, point2);

	EXPECT_EQ(expectedPoint.X(), actualPoint.X());
	EXPECT_EQ(expectedPoint.Y(), actualPoint.Y());
}


TEST(PointListTest, Nearest3)
{
	PointList pointList;

	Point2D point1(1, 2);
	Point2D point2(3, 4);
	Point2D point3(13, 14);
	Point2D point4(2.5, 4.5);

	Point2D expectedPoint = point2;

	pointList.Add(point1);
	pointList.Add(point2); 
	pointList.Add(point3);
	pointList.Add(point4);

	Point2D actualPoint = pointList.GetNearestPoint(2, point4);

	EXPECT_EQ(expectedPoint.X(), actualPoint.X());
	EXPECT_EQ(expectedPoint.Y(), actualPoint.Y());
}