#pragma once
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include "GTypes.h"
#include "GNeuron.h"
#include <cassert>




class GNeuralNet
{
public:
		GNeuralNet(const Topology &topology);
		void feedForward(const VectorDouble& inputVals);
		void backPropagate(const VectorDouble& targetVals);
		void getResults(VectorDouble& resultVals) const;
		void generateSoftMaxOutput(VectorDouble &outputSigma, VectorDouble &results) const;
		double getRecentAverageError(void) const { return m_recentAverageError; };
		bool saveNetwork(const string file_name, double err, double forecast, DateTime time, bool common = true);
		bool loadNetwork(const string file_name, double& err, double& forecast, DateTime& time, bool common = true);
		bool TrainNetwork(void);
private:
		Topology m_topology;
		vector<Layer> m_layers;
		double m_error = 0.0;
		double m_recentAverageError = 0.0;
		double m_recentAvergeSmoothingFactor = 0.0;
};

