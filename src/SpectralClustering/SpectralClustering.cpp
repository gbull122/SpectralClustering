/*
 * SpectralClustering.cpp
 *
 *  Created on: 04-Mar-2009
 *      Author: sbutler
 */
#define EIGEN2_SUPPORT

#include "SpectralClustering.h"
#include "ClusterRotate.h"
#include "Kmeans.h"

#include <Eigen/QR>

 /**
 * Performs eigenvector decomposition of an affinity matrix
 *
 * @param data 		the affinity matrix
 * @param numDims	the number of dimensions to consider when clustering
 */
SpectralClustering::SpectralClustering(int numDims) :
	mNumDims(numDims),
	mNumClusters(0)
{

}

SpectralClustering::~SpectralClustering() {
}

Eigen::MatrixXd SpectralClustering::CalcEigenVectors(Eigen::MatrixXd& affinityMatrix)
{
	Eigen::MatrixXd Deg = Eigen::MatrixXd::Zero(affinityMatrix.rows(), affinityMatrix.cols());

	// calc normalised laplacian 
	for (int i = 0; i < affinityMatrix.cols(); i++) 
	{
		Deg(i, i) = 1 / (sqrt((affinityMatrix.row(i).sum())));
	}
	Eigen::MatrixXd Lapla = Deg * affinityMatrix * Deg;

	Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> s(Lapla, true);
	Eigen::VectorXd val = s.eigenvalues();
	Eigen::MatrixXd vec = s.eigenvectors();

	//sort eigenvalues/vectors
	int n = affinityMatrix.cols();
	for (int i = 0; i < n - 1; ++i) 
	{
		int k;
		val.segment(i, n - i).maxCoeff(&k);
		if (k > 0) 
		{
			std::swap(val[i], val[k + i]);
			vec.col(i).swap(vec.col(k + i));
		}
	}

	//choose the number of eigenvectors to consider
	if (mNumDims < vec.cols()) 
	{
		mEigenVectors = vec.block(0, 0, vec.rows(), mNumDims);
	}
	else 
	{
		mEigenVectors = vec;
	}

	return mEigenVectors;
}

/**
 * Cluster by rotating the eigenvectors and evaluating the quality
 */
std::vector<std::vector<int> > SpectralClustering::clusterRotate(Eigen::MatrixXd& eigenVectors)
{

	ClusterRotate* clusterRotate = new ClusterRotate();
	std::vector<std::vector<int> > clusters = clusterRotate->cluster(eigenVectors);

	mNumClusters = clusters.size();

	return clusters;
}

/**
 * Cluster by kmeans
 *
 * @param numClusters	the number of clusters to assign
 */
std::vector<std::vector<int> > SpectralClustering::clusterKmeans(Eigen::MatrixXd& eigenVectors,int numClusters)
{
	mNumClusters = numClusters;
	return Kmeans::cluster(mEigenVectors, numClusters);
}
