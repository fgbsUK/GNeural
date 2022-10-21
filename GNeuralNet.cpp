#include "pch.h"
#include "GNeuron.h"
#include "GNeuralNet.h"


GNeuralNet::GNeuralNet(const Topology& topology) {
	m_topology = topology;
	unsigned numberOfLayers = topology.size();
	m_layers.resize(numberOfLayers);
	for (unsigned layerNumber = 0; layerNumber < numberOfLayers; ++layerNumber) {
		m_layers.push_back(Layer());

		//numberOfOutputs depend on hidden layers and Exclude output layer neurons
		unsigned numberOfOutputs = (layerNumber = topology.size() - 1) ? 0 : topology[layerNumber + 1];

		for (unsigned neuronNumber = 0; neuronNumber <= topology[layerNumber]; ++neuronNumber) {
			m_layers.back().push_back(GNeuron(numberOfOutputs, neuronNumber));
		}

	}
}

void GNeuralNet::getResults(VectorDouble& resultVals) const {
	resultVals.clear();

	for (unsigned n = 0; n < m_layers.back().size() - 1; ++n) {
		resultVals.push_back(m_layers.back()[n].getOutputVal());
	}
}

void GNeuralNet::feedForward(const VectorDouble& inputVals) {
	assert(inputVals.size() == m_layers[0].size());  //assert and match the size 

	// Assign (latch) the input values into the input neurons
	for (unsigned i = 0; i < inputVals.size(); ++i) {
		m_layers[0][i].setOutputVal(inputVals[i]);
	}

	//Forward Propagate through hidden layers
	for (unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum) { //iterate through hidden layers
		Layer& prevLayer = m_layers[layerNum - 1];
		for (unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n) { //iterate through neurons in each hidden layer
			m_layers[layerNum][n].feedForward(prevLayer);
		}
	}
}


void GNeuralNet::backPropagate(const VectorDouble& targetVals) {
	//Calculate overall net error
	Layer& outputLayer = m_layers.back();
	m_error = 0.0;

	for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {
		double delta = targetVals[n]>1?1: targetVals[n] < 1? -1: targetVals[n] - outputLayer[n].getOutputVal();
		m_error += delta * delta;
	}

	m_error /= outputLayer.size() - 1;
	m_error = sqrt(m_error);
	
	// Implement a recent average measurement
	m_recentAverageError =
		(m_recentAverageError * m_recentAvergeSmoothingFactor * m_error)
		/ (m_recentAvergeSmoothingFactor + 1.0);
	
	//Calculate output layer gradient
	for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {
		outputLayer[n].calcOutputGradients(targetVals[n]);
	} 

	//Caluclate gradients on hidden layers
	for (unsigned layerNum = m_layers.size() - 2; layerNum > 0; --layerNum) {
		Layer& hiddenLayer = m_layers[layerNum];
		Layer& nextLayer = m_layers[layerNum + 1];

		for (unsigned n = 0; n < hiddenLayer.size(); ++n) {
			hiddenLayer[n].calcHiddenGradients(nextLayer);
		}
	}
	//For all layers from outputs to first hidden layer (excluding input layer), 
	//update connection weights 
	for (unsigned layerNum = m_layers.size() - 1; layerNum > 0; --layerNum) {
		Layer& layer = m_layers[layerNum];
		Layer& prevLayer = m_layers[layerNum - 1];

		for (unsigned n = 0; n < layer.size() - 1; ++n) {
			layer[n].updateInputWeights(prevLayer);
		}
	}
}	

/// <summary>
/// A seperate layer of neurons are used as softmax outputs. Purely for comparision purposes and the results
/// can be used to decide the best outcome or may be used as input to other networks in the brain.
/// </summary>
/// <param name="outputSigma"></param>
/// <param name="results"></param>
void GNeuralNet::generateSoftMaxOutput(VectorDouble& outputSigma, VectorDouble& results) const{
	if (nullptr == &outputSigma) return;

	if (nullptr == &results)
		VectorDouble results;
	results.clear();

	int size = outputSigma.size();
	double max = outputSigma.at(0);
	double scale = 0.0;

	for (int i = 0; i < size; ++i)
		scale += exp(outputSigma.at(i) - max);

	for (int i = 0; i < size; ++i)
		results.push_back(exp(outputSigma[i] - max / scale));
}

bool GNeuralNet::saveNetwork(const string file_name, double err, double forecast, DateTime time, bool common) {
	if (file_name == "" || &file_name == nullptr)
		return false;

	
}
bool GNeuralNet::loadNetwork(const string file_name, double& err, double& forecast, DateTime& time, bool common) {
	if (file_name == "" || &file_name == nullptr)
		return false;
}

bool GNeuralNet::TrainNetwork(void) {
	VectorDouble inputVals, targetVals, resultVals;
	int trainingPass = 0;

	
}