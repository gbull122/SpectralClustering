#pragma once

#include "..\SpectralClustering\Point2D.h"
#include "..\SpectralClustering\PointList.h"
#include <vector>
#include <Eigen/Core>

using namespace System;

namespace Clustering {
	public ref class Clusters
	{
	public:
		array<array<int>^>^ DoCluster(System::String^ path);

	private:
		Eigen::MatrixXd GenerateAffinityMatrix(std::vector<std::vector<double>> points);
		double EuclideanDistance(std::vector<double>& rD1, std::vector<double>& rD2);
		double KthNearestPoint(std::vector<std::vector<double>> rDataset, int nPIndex, int K);
		std::vector<std::vector<double> > ReadDataFile(char* filePath);
	};
}
