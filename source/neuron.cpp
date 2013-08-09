#include "neuron.h"

Neuron::Neuron(unsigned numberOutputs){
	for (unsigned c = 0; c < numberOutputs; c++){
		outputWeights.push_back(Connection());
	}
}

Neuron::~Neuron(){

}