#pragma once

#include "..\SpectralClustering\Point2D.h"
#include "..\SpectralClustering\PointList.h"
#include <vector>

using namespace System;

namespace Clustering {
	public ref class Class1
	{
	public:
		array<array<int>^>^ DoCluster(System::String^ path);

	private:
		double euclideanDistance(std::vector<double>& rD1, std::vector<double>& rD2);
		double sigma(std::vector<std::vector<double>> rDataset, int nPIndex, int K);
		std::vector<std::vector<double> > readData(char* filePath);
	};
}
