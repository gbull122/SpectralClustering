#pragma once

#include <vector>
#include <Eigen/Core>
#include <iterator>
#include <iostream>
#include <fstream>

#include "../SpectralClustering/SpectralClustering.h"

using namespace System;

public ref class Clusters
{

public:
	array<array<int>^>^ DoCluster(System::String^ path, int maxNumberOfClusters);
	array<array<int>^>^ Clusters::DoCluster(IntPtr dataHandle, int dimension, int length, int maxNumberOfClusters);

private:
	array<array<int>^>^ ConvertClusters(std::vector<std::vector<int>> clusters);
	std::vector<std::vector<double>> Clusters::Convert(IntPtr dataHandle, int dimension, int length);
	Eigen::MatrixXd GenerateAffinityMatrix(std::vector<std::vector<double>> points);
	double EuclideanDistance(std::vector<double>& rD1, std::vector<double>& rD2);
	double KthNearestPoint(std::vector<std::vector<double>> rDataset, int nPIndex, int K);
	std::vector<std::vector<double> > ReadDataFile(char* filePath);

};

