#ifndef NEURON_H
#define NEURON_H
#include <iostream>
#include "layer.h"
#include "connection.h"

using namespace std;
class Neuron{ 

	double outputValue;

	//conections weights
	vector<Connection> outputWeights;

public:
	Neuron(unsigned numberOutputs);
	~Neuron();

};

#endif