
#include "Clustering.h"
#include "../SpectralClustering/SpectralClustering.h"
#include <iterator>
#include <iostream>
#include <fstream>

using namespace System::Runtime::InteropServices;

	array<array<int>^>^ Clustering::Class1::DoCluster(System::String^ path)
	{
		IntPtr ptrToNativeString = Marshal::StringToHGlobalAnsi(path);

		int K = 4;
		double simCut = 1;
		double stopCriteria = 1;
		std::vector<std::vector<double> > aInput = readData(static_cast<char*>(ptrToNativeString.ToPointer()));

		// generate similarity matrix
		unsigned int size = aInput.size();
		Eigen::MatrixXd m = Eigen::MatrixXd::Zero(size, size);

		// calculate sigmas
		std::vector<double> aSigmas;
		for (int i = 0; i < size; i++) {
			aSigmas.push_back(sigma(aInput, i, K));
		}

		for (unsigned int i = 0; i < size; i++) {
			for (unsigned int j = i + 1; j < size; j++) {
				// generate similarity
				double d = euclideanDistance(aInput[i], aInput[j]);
				double similarity = 0;
				if (d < simCut) {
					similarity = exp(-(d * d) / (aSigmas[i] * aSigmas[j]));
				}
				m(i, j) = similarity;
				m(j, i) = similarity;
			}
		}

		// the number of eigenvectors to consider. This should be near (but greater) than the number of clusters you expect. Fewer dimensions will speed up the clustering
		int numDims = std::stoi("4");

		// do eigenvalue decomposition
		SpectralClustering c(m, numDims);

		std::vector<std::vector<int> > clusters;
		// auto-tuning clustering
		clusters = c.clusterRotate();
		// output clustered items
		// items are ordered according to distance from cluster centre

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

	double Clustering::Class1::euclideanDistance(std::vector<double>& rD1, std::vector<double>& rD2) {
		double dRes = 0;
		for (int i = 0; i < rD1.size(); i++) {
			double dDiff = rD1[i] - rD2[i];
			dRes += dDiff * dDiff;
		}
		return std::sqrt(dRes);
	}

	double Clustering::Class1::sigma(std::vector<std::vector<double>> rDataset, int nPIndex, int K) {
		std::vector<double> aDistances;
		for (int i = 0; i < rDataset.size(); i++) {
			if (i != nPIndex) { //Don't compare the point with itself
				aDistances.push_back(euclideanDistance(rDataset[nPIndex], rDataset[i]));
			}
		}

		std::sort(aDistances.begin(), aDistances.end());

		return aDistances[K];
	}

	std::vector<std::vector<double> > Clustering::Class1::readData(char* filePath) {
		std::fstream aInput;
		aInput.open(filePath, std::fstream::in);

		std::vector<std::vector<double> > aDataVect;
		std::string aLine;
		while (std::getline(aInput, aLine)) {
			std::vector<double> aPoint;
			int nStart = 0, nEnd = 0;
			while ((nEnd = aLine.find(',', nStart)) != std::string::npos) {
				aPoint.push_back(std::stod(aLine.substr(nStart, nEnd - nStart)));
				nStart = nEnd + 1;
			}
			aPoint.push_back(std::stod(aLine.substr(nStart, aLine.length() - nStart)));
			aDataVect.push_back(aPoint);
		}
		aInput.close();
		return aDataVect;
	}

