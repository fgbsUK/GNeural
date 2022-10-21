// GNeural.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "GNeural.h"


// This is an example of an exported variable
GNEURAL_API int nGNeural=0;

// This is an example of an exported function.
GNEURAL_API int fnGNeural(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CGNeural::CGNeural()
{
    return;
}

Topology CGNeural::generateTopology(const int inputs, const int hidden, const int outputs) {
	Topology topology;
	topology.push_back(inputs);
	topology.push_back(hidden);
	topology.push_back(outputs);
	return topology;
}

GNeuralNet* CGNeural::createGNet(const vector <unsigned>& topology) {
    //check for a valid topology
    GNeuralNet gnet = GNeuralNet(topology);
    m_network.push_back(gnet);
    return &gnet;
}

void CGNeural::addGNet(GNeuralNet& gnet) {
    m_network.push_back(gnet);
}


