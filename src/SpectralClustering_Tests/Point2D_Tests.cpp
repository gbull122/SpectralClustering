#include "pch.h"
#include "../SpectralClustering/Point2D.h"

TEST(Point2DTest, DistanceZero) 
{

	double expectedDistance = 0;

	Point2D  point1(2,2);
	Point2D  point2(2, 2);

	double actualDistance = point1.dist(point2);

  EXPECT_EQ(expectedDistance, actualDistance);
}

TEST(Point2DTest, DistanceOne)
{
	double expectedDistance = 1;

	Point2D  point1(2, 2);
	Point2D  point2(3, 2);

	double actualDistance = point1.dist(point2);

	EXPECT_EQ(expectedDistance, actualDistance);
}

TEST(Point2DTest, DistanceRootTwo)
{
	double expectedDistance = sqrt(2.0);

	Point2D  point1(2, 2);
	Point2D  point2(3, 3);

	double actualDistance = point1.dist(point2);

	EXPECT_EQ(expectedDistance, actualDistance);
}