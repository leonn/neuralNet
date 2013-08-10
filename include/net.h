#ifndef NET_H
#define NET_H

#include <vector>
#include <iostream>
#include <cassert>
#include "layer.h"

using namespace std;

class Net{

	double error;
	double recentAverageError;
	double recentAverageSmoothingFactor;
	vector<Layer> layers ;// layers[layerNumber][neuronNumber]

public:
	Net(const vector<unsigned> &topology);
	
	//feedForward - operation to train the network
	void feedForward(const vector<double> &inputValues);

	// brackPropagation learning
	void brackPropagation(const vector<double> &targetValues);

	void getResults(vector<double> &resultValues) const;

};

#endif