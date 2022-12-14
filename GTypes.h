#pragma once
#include <stdlib.h>
#include <vector>
#include <ctime>

using namespace std;

typedef vector<unsigned> VectorUnsigned;
typedef vector<int> VectorInt;
typedef vector<double> VectorDouble;


typedef vector<unsigned> Topology;
typedef vector<GNeuron> Memory;
 
class DateTime {
public: 
	//tm* getGMTTime(void) { return gmtime_s(&now); }
	//char* getAscTime(void) { return asctime_s(&now); }
	char* getCurrentTime(void) { return dt; }
private:
	time_t now = time(0);
	char* dt = ctime(&now);

};


class NNetTrainingData {
public:

private:
	VectorDouble m_input;
	VectorDouble m_output;


};
#ifdef MAKEDLL
#  define GN_EXPORT __declspec(dllexport)
#else
#  define GN_EXPORT __declspec(dllimport)
#endif








