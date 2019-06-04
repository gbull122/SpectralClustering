
#include "Clustering.h"

using namespace System::Runtime::InteropServices;

array<array<int>^>^ Clusters::DoCluster(IntPtr dataHandle, int dimension , int length, int maxNumberOfClusters, bool useSpectral)
{
	std::vector<std::vector<double>> convertedData = Convert(dataHandle,dimension,length);

	Eigen::MatrixXd affinityMatrix = GenerateAffinityMatrix(convertedData);

	//Do spectral clustering
	SpectralClustering spectralClustering(maxNumberOfClusters);
	Eigen::MatrixXd eigenvectors = spectralClustering.CalcEigenVectors(affinityMatrix);

	std::vector<std::vector<int>> clusters;

	if (useSpectral)
		clusters = spectralClustering.clusterRotate(eigenvectors);
	else
		clusters = spectralClustering.clusterKmeans(eigenvectors,maxNumberOfClusters);

	return ConvertClusters(clusters);
}

array<array<int>^>^ Clusters::DoCluster(System::String^ path, int maxNumberOfClusters)
{
	IntPtr ptrToNativeString = Marshal::StringToHGlobalAnsi(path);
	std::vector<std::vector<double> > aInput = ReadDataFile(static_cast<char*>(ptrToNativeString.ToPointer()));

	Eigen::MatrixXd affinityMatrix = GenerateAffinityMatrix(aInput);

	//Do spectral clustering
	SpectralClustering spectralClustering(maxNumberOfClusters);
	Eigen::MatrixXd eigenvectors = spectralClustering.CalcEigenVectors(affinityMatrix);

	std::vector<std::vector<int>> clusters;
	clusters = spectralClustering.clusterRotate(eigenvectors);

	return ConvertClusters(clusters);
}

std::vector<std::vector<double>> Clusters::Convert(IntPtr dataHandle, int dimension, int length)
{
	double* p = static_cast<double*>(static_cast<void*>(dataHandle));

	std::vector<std::vector<double>> convertedVector;

	for (unsigned int i = 0; i < length; i++)
	{
		std::vector<double> row;

		for (unsigned int j = 0; j < dimension; j++)
		{
			row.push_back(*p);
			p++;
		}
		convertedVector.push_back(row);

	}

	return convertedVector;
}

array<array<int>^>^ Clusters::ConvertClusters(std::vector<std::vector<int>> clusters)
{
	array<array<int>^>^ arr = gcnew array<array<int>^>(clusters.size());

	for (unsigned int i = 0; i < clusters.size(); i++)
	{
		std::vector<int> cluster = clusters[i];
		arr[i] = gcnew array<int>(cluster.size());
		for (unsigned int j = 0; j < cluster.size(); j++)
		{
			arr[i][j] = cluster[j];
		}
		std::cout << "Cluster " << i << ": " << "Item ";
		std::copy(clusters[i].begin(), clusters[i].end(), std::ostream_iterator<int>(std::cout, ", "));
		std::cout << std::endl;
	}

	return arr;
}

Eigen::MatrixXd Clusters::GenerateAffinityMatrix(std::vector<std::vector<double>> points)
{
	int K = 4;
	double simCut = 1;

	unsigned int size = points.size();
	Eigen::MatrixXd affinityMatrix = Eigen::MatrixXd::Zero(size, size);

	// calculate sigmas
	std::vector<double> kthNearestPoints;
	for (int i = 0; i < size; i++)
	{
		kthNearestPoints.push_back(KthNearestPoint(points, i, K));
	}

	for (unsigned int i = 0; i < size; i++)
	{
		for (unsigned int j = i + 1; j < size; j++)
		{
			// generate similarity
			double d = EuclideanDistance(points[i], points[j]);
			double similarity = 0;
			if (d < simCut)
			{
				similarity = exp(-(d * d) / (kthNearestPoints[i] * kthNearestPoints[j]));
			}
			affinityMatrix(i, j) = similarity;
			affinityMatrix(j, i) = similarity;
		}
	}
	return affinityMatrix;
}

double Clusters::EuclideanDistance(std::vector<double> & point1, std::vector<double> & point2)
{
	double dRes = 0;
	for (int i = 0; i < point1.size(); i++)
	{
		double dDiff = point1[i] - point2[i];
		dRes += dDiff * dDiff;
	}
	return std::sqrt(dRes);
}

double Clusters::KthNearestPoint(std::vector<std::vector<double>> points, int indexOfPoint, int K)
{
	std::vector<double> aDistances;
	for (int i = 0; i < points.size(); i++)
	{
		if (i != indexOfPoint)
		{ //Don't compare the point with itself
			aDistances.push_back(EuclideanDistance(points[indexOfPoint], points[i]));
		}
	}

	std::sort(aDistances.begin(), aDistances.end());

	return aDistances[K];
}

std::vector<std::vector<double> > Clusters::ReadDataFile(char* filePath)
{
	std::fstream aInput;
	aInput.open(filePath, std::fstream::in);

	std::vector<std::vector<double> > aDataVect;
	std::string aLine;
	while (std::getline(aInput, aLine))
	{
		std::vector<double> aPoint;
		int nStart = 0, nEnd = 0;
		while ((nEnd = aLine.find(',', nStart)) != std::string::npos)
		{
			aPoint.push_back(std::stod(aLine.substr(nStart, nEnd - nStart)));
			nStart = nEnd + 1;
		}
		aPoint.push_back(std::stod(aLine.substr(nStart, aLine.length() - nStart)));
		aDataVect.push_back(aPoint);
	}
	aInput.close();
	return aDataVect;
}

