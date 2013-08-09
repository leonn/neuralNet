#include "net.h"

Net::Net(){	
}

Net::Net(const vector<unsigned> &topology){
	// size
 	unsigned numberOfLayers = topology.size();

 	//create a new  Layer on each interation
 	for (unsigned layerNumber = 0; layerNumber < numberOfLayers; layerNumber++){
 		layers.push_back(Layer());

 		//number of outputs to a neuron
		unsigned numberOutputs= (layerNumber==topology.size()-1) ? 0: topology[layerNumber+1] ;

 		// fill layer wiith neurons and  add bias neuron to the layer;
 		for (unsigned neuronNumber = 0; neuronNumber <= topology[layerNumber] ; neuronNumber++){
			layers.back().push_back(Neuron(numberOutputs));	
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