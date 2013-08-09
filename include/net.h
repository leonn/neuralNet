#ifndef NET_H
#define NET_H

#include <vector>
#include "layer.h"

using namespace std;

class Net{

private:
	vector<Layer> m_layers ;// mlayers[layerNumber][neuronNumber]

public:
	Net();

	Net(const vector<unsigned> &topology);

	~Net();
	
	//feedForward - operation to train the network
	void feedForward(const vector<double> &inputValues);

	// brackPropagation learning
	void brackPropagation(const vector<double> &targetValues);

	void getResults(vector<double> &resultValues) const;

};

#endif