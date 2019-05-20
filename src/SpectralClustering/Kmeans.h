#pragma once

#define EIGEN2_SUPPORT

#include <vector>
#include <map>
#include <iostream>
#include <Eigen/Core>

class Kmeans
{
public:
	Kmeans();
	~Kmeans();

	static std::vector<std::vector<int>> cluster(Eigen::MatrixXd& data, int ncentres);
};

