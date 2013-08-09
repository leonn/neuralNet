#include "net.h"

Net::Net(){	
}

Net::Net(const vector<unsigned> &topology){
	// size
 	unsigned numberOfLayers = topology.size();

 	//create a new  Layer on each interation
 	for (int layerNumber = 0; layerNumber < numberOfLayers; layerNumber++){
 		m_layers.push_back(Layer());

 		// fill layer wiith neurons and  add bias neuron to the layer;
 		for (int neuronNumber = 0; neuronNumber <= topology[numberOfLayers] ; neuronNumber++){
			m_layers.back().push_back(Neuron());	
 		}
 	}

}

Net::~Net(){
	
}

//feedForward - operation to train the network
void Net::feedForward(const vector<double> &inputValues){
}

// brackPropagation learning
void Net::brackPropagation(const vector<double> &targetValues){
}

void Net::getResults(vector<double> &resultValues) const{
}