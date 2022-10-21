#include "pch.h"
#include "GConnection.h"


void GConnection::setConnectionWeight(double _weight) {
	weight = _weight;
}

double GConnection::getWeight(void) const{
	return weight;
}


double GConnection::getDeltaWeight(void) {
	return deltaWeight;
}