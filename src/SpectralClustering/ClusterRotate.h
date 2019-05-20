#pragma once

#define EIGEN2_SUPPORT

#include <vector>
#include <map>

#include <Eigen/Core>
#include <Eigen/Array>

#include "Evrot.h"

class ClusterRotate
{
public:
	ClusterRotate(int method = 1);
	virtual ~ClusterRotate() { }

	std::vector<std::vector<int> > cluster(Eigen::MatrixXd& X);
	double getMaxQuality() { return mMaxQuality; };

protected:

	int mMethod;
	double mMaxQuality;
};

