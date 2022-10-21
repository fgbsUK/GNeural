#pragma once
#include "pch.h"
#include "GNeuron.h"
#include "GConnection.h"


//template<> 
//double GNeuron<double>::eta = 0.15;
double GNeuron::eta = 0.15;
double GNeuron::alpha = 0.5;
//template<> double GNeuron<double>::alpha = 0.5;

//template<class T>
//GNeuron<T>::GNeuron(unsigned numOutputs, unsigned myIndex) {
GNeuron::GNeuron(unsigned numOutputs, unsigned myIndex) {
	for (unsigned c = 0; c < numOutputs; ++c) { // iterate over connections 
		m_outputWeights.push_back(GConnection());
		m_outputWeights.back().setConnectionWeight(randomWeight());
	}
}

void GNeuron::feedForward(Layer& prevLayer) {
	double sum = 0;

	// Sum up the prev layer's outputs (which are inputs)
	// Include the bias node from the previous layer

	for (unsigned n = 0; n < prevLayer.size(); ++n) {
		sum += prevLayer[n].getOutputVal() * prevLayer[n].m_outputWeights[m_myIndex].getWeight();
	}

	m_outputVal = GNeuron::transferFunction(sum);
}

void GNeuron::calcOutputGradients(double targetVal) {
	//double delta = targetVal - m_outputVal;
	double delta = (targetVal > 1 ? 1 : targetVal < -1 ? -1 : targetVal) - m_outputVal;
	m_gradient = delta !=0 ? delta * GNeuron::transferFunctionDerivative(targetVal) : 0;
}

void GNeuron::calcHiddenGradients(const Layer& nextLayer) {
	double dow = sumDOW(nextLayer);
	m_gradient = dow * GNeuron::transferFunctionDerivative(m_outputVal);
}

void  GNeuron::updateInputWeights(Layer& prevLayer) {
	//The weights to be updated are in the Connection container
	// in the neurons of the preceding layer
	for (unsigned n = 0; n < prevLayer.size(); ++n) {
		GNeuron& neuron = prevLayer[n];
		double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].getDeltaWeight();

		double newDeltaWeight =
			//Individual input, magnified by the gradient and train rate:
			eta //overall training rate (0.0 - slow learner, 0.2 - medium learner , 1.0 - reckless learner
			* neuron.getOutputVal()
			* m_gradient
			// Also add momentum = a fraction of the previous delta weight
			+ alpha // momentum (0.0 - no momentum, 0.5 moderate momentum)
			* oldDeltaWeight;

	}
}

//Privates
double GNeuron::transferFunctionDerivative(double x) {
	return (1 - x * x);
}

double GNeuron::transferFunction(double x) {
	return tanh(x);
}


double GNeuron::sumDOW(const Layer& nextLayer) const {
	double sum = 0.0;
	// Sum our contributions of the errors at the nodes we feed

	for (unsigned n = 0; n < nextLayer.size() - 1; ++n) {
		sum += m_outputWeights[n].getWeight() * nextLayer[n].m_gradient;
	}

	return sum;
}