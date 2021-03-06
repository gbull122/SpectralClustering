/*
 * SpectralClustering.h
 *
 * Takes an affinity matrix and calculates the eigenvectors
 * Then different clustering algorithms can be applied
 *
 *  Created on: 04-Mar-2009
 *      Author: sbutler
 */

#ifndef SPECTRALCLUSTERING_H_
#define SPECTRALCLUSTERING_H_

#include <vector>
#include <Eigen/Core>

class SpectralClustering {
public:
	/**
	 * Performs eigenvector decomposition of an affinity matrix
	 *
	 * @param data 		the affinity matrix
	 * @param numDims	the number of dimensions to consider when clustering
	 */
	SpectralClustering(int numDims);
	virtual ~SpectralClustering();

	/**
	 * Cluster by rotating the eigenvectors and evaluating the quality
	 */
	std::vector<std::vector<int> > clusterRotate(Eigen::MatrixXd& eigenVectors);

	/**
	 * Cluster by kmeans
	 *
	 * @param numClusters	the number of clusters to assign
	 */
	std::vector<std::vector<int> > clusterKmeans(Eigen::MatrixXd& eigenVectors, int numClusters);

	Eigen::MatrixXd CalcEigenVectors(Eigen::MatrixXd& affinityMatrix);

protected:
	int mNumDims;
	Eigen::MatrixXd mEigenVectors;
	int mNumClusters;
};

#endif /* SPECTRALCLUSTERING_H_ */
