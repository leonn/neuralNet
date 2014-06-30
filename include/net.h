#ifndef NET_H
#define NET_H

#include <vector>
#include <iostream>
#include <cassert>
#include "layer.h"
#include <string.h>

using namespace std;

class Net{

	double error;
	double recentAverageError;
	vector<Layer> layers ;// layers[layerNumber][neuronNumber]

public:
	//Net(const vector<unsigned> &topology);
	Net(const vector<unsigned> &topology,const string &transferFunction);

	//feedForward - operation to train the network
	void feedForward(const vector<double> &inputValues);

	// backPropagation learning
	void backPropagation(const vector<double> &targetValues,const double &eta ,const double &alpha);

	void getResults(vector<double> &resultValues) const;

	double getRecentAverageError() const;

};

#endif