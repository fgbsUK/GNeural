#pragma once
#include <stdlib.h>
#include <vector>
#include "GConnection.h"

using namespace std;
class GNeuron;
typedef vector<GNeuron> Layer;

//template<class T>
class GNeuron
{
public:
	GNeuron(unsigned numOutputs, unsigned myIndex);
	void setOutputVal(double val) { m_outputVal = val; }
	double getOutputVal(void) const { return m_outputVal; }
	void feedForward(Layer& prevLayer);
	void calcOutputGradients(double targetVal);
	void calcHiddenGradients(const Layer& nextLayer);
	void updateInputWeights(Layer& prevLayer);
private:
	static double eta;
	static double alpha;
	static double transferFunction(double x);
	static double transferFunctionDerivative(double x);
	static double randomWeight(void) { return rand() / double(RAND_MAX); }
	double sumDOW(const Layer& nextLayer) const;
	double m_outputVal;
	vector<GConnection> m_outputWeights;
	unsigned m_myIndex;
	double m_gradient;
};

