#pragma once

#define EIGEN2_SUPPORT

#include <vector>
#include <Eigen/Core>

#include "ClusterRotate.h"
#include "Kmeans.h"

#include <Eigen/QR>

class SpectralClustering
{
public:
	SpectralClustering(Eigen::MatrixXd& data, int numDims);
	virtual ~SpectralClustering();

	std::vector<std::vector<int> > clusterRotate();

	std::vector<std::vector<int> > clusterKmeans(int numClusters);

protected:
	int mNumDims;
	Eigen::MatrixXd mEigenVectors;
	int mNumClusters;
};

