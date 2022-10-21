#pragma once
// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the GNEURAL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// GNEURAL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef GNEURAL_EXPORTS
#define GNEURAL_API __declspec(dllexport)
#else
#define GNEURAL_API __declspec(dllimport)
#endif

#include "GTypes.h"
#include "GNeuralNet.h"

 
typedef vector<GNeuralNet> GoogiNet;
// This class is exported from the dll
class GNEURAL_API CGNeural {
public:
	CGNeural(void);
	// TODO: add your methods here.
	Topology generateTopology(const int inputs,  const int hidden, const int outputs);
	GNeuralNet* createGNet(const vector <unsigned>& topology);
	void addGNet(GNeuralNet& gnet);
	unsigned size(void) { return m_network.size(); };
private:
	GoogiNet m_network; //main network
	//GoogiNet m_imageProcessors; //Image processors
	//GoogiNet m_langugeProcessor; 
	//GoogiNet m_smartBrain;
	
};


extern GNEURAL_API int nGNeural;

GNEURAL_API int fnGNeural(void);


