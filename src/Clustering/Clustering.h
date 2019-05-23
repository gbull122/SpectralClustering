#pragma once

#include "..\SpectralClustering\Point2D.h"
#include "..\SpectralClustering\PointList.h"

using namespace System;

namespace Clustering {
	public ref class Class1
	{
	public:
		array<array<int>^>^ DoCluster(array<double,2>^ data);
	};
}
