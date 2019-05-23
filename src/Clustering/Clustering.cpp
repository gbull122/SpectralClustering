
#include "Clustering.h"
#include "../SpectralClustering/SpectralClustering.h"
#include <iterator>


	array<array<int>^>^ Clustering::Class1::DoCluster(array<double,2>^ data)
	{
		unsigned int dataLength = data->GetLength(0);

		PointList pointList;

		//Now sort affinity matrix
		Eigen::MatrixXd A(dataLength, dataLength);
		for (int i = 0; i < dataLength; i++)
		{
			Point2D firstPoint(data[i, 0], data[i, 1]);
			Point2D thing = pointList.GetNearestPoint(6, firstPoint);
			for (int j = 0; j < dataLength; j++)
			{
				if (i == j)
				{
					A(i, j) = 0;
				}
				else
				{
					double sigmaI = 0;
					double sigmaJ = 0;
					Point2D secondPoint(imported(j, 0), imported(j, 1));
					sigmaI = firstPoint.dist(thing);
					sigmaJ = firstPoint.dist(secondPoint);
					double dist = pow(firstPoint.dist(secondPoint), 2);
					A(i, j) = exp((-1.0 * dist) / (sigmaI * sigmaJ));
				}
			}
		}

		// generate similarity matrix
		unsigned int size = data->GetLength(0);
		Eigen::MatrixXd m = Eigen::MatrixXd::Zero(size, size);

		for (unsigned int i = 0; i < size; i++) {
			for (unsigned int j = 0; j < size; j++) {
				// generate similarity
				int d = data[i] - data[j];
				int similarity = exp(-d * d / 100);
				m(i, j) = similarity;
				m(j, i) = similarity;
			}
		}

		// the number of eigenvectors to consider. This should be near (but greater) than the number of clusters you expect. Fewer dimensions will speed up the clustering
		int numDims = size;

		// do eigenvalue decomposition
		SpectralClustering* c = new SpectralClustering(m, numDims);

		// whether to use auto-tuning spectral clustering or kmeans spectral clustering
		bool autotune = true;

		std::vector<std::vector<int> > clusters;
		if (autotune) {
			// auto-tuning clustering
			clusters = c->clusterRotate();
		}
		else {
			// how many clusters you want
			int numClusters = 5;
			clusters = c->clusterKmeans(numClusters);
		}

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

