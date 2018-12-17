#include "net.h"

Net::Net(const vector<unsigned> &topology,const string &transferFunction){
	// size
 	unsigned numberOfLayers = topology.size();

 	//create a new  Layer on each interation
 	for (unsigned layerNumber = 0; layerNumber < numberOfLayers; layerNumber++){
 		layers.push_back(Layer());

 		//number of outputs to a neuron
		unsigned numberOutputs= (layerNumber==topology.size()-1) ? 0: topology[layerNumber+1] ;

 		// fill layer wiith neurons and  add bias neuron to the layer;
 		for (unsigned neuronNumber = 0; neuronNumber <= topology[layerNumber] ; neuronNumber++){
			layers.back().push_back(Neuron(numberOutputs,neuronNumber,transferFunction));
 		}
 	}

 	// Force the bias node's output to 1.0 (it was the last neuron pushed in this layer):
    layers.back().back().setOutputValue(1.0);

}

//feedForward - operation to train the network
void Net::feedForward(const vector<double> &inputValues){
	assert(inputValues.size()==layers[0].size() - 1 && " the inputValues size needs to be the same of the first layer - bias");

	for (unsigned i = 0; i < inputValues.size(); i++)	{
		layers[0][i].setOutputValue(inputValues[i]);
	}

	//forward propagation
 	//loop each layer and each neuron inside the layer
 	for (unsigned layerNumber = 1; layerNumber <= layers.size(); layerNumber++){
 		Layer &prevLayer = layers[layerNumber-1];
 		for (unsigned n = 0; n < layers[layerNumber].size(); n++){
 			layers[layerNumber][n].feedForward(prevLayer);
 		}
 	}

}

// backPropagation learning
void Net::backPropagation(const vector<double> &targetValues,const long double &eta ,const long double &alpha){

	//-----Calculate overall net error (RMS-root mean square error - of output neuron errors)
	Layer &outputLayer = layers.back();

	//overwall net error
	error=0.0;

 	for(unsigned n = 0; n < outputLayer.size() -1; n++){
 		long double delta= targetValues[n] - outputLayer[n].getOutputValue();
 		error+=delta*delta;
 	}
 	error*=0.5;

 	//error/=(* numPatterns); //get average error squared
	//error/=outputLayer.size()-1; //get average error squared
    //------ Implement a recent average measurement
    recentAverageError = error;

    //------ Calculate output layer gradients
	for(unsigned n = 0; n < outputLayer.size() -1; n++){
 		outputLayer[n].calculateOutputGradients(targetValues[n]);
  	}

    //------- Calculate hidden layer gradients
  	for(unsigned layerNumber = layers.size() -2; layerNumber >0 ; layerNumber--){
		Layer &hiddenLayer = layers[layerNumber];
		Layer &nextLayer = layers[layerNumber+1];

		for(unsigned n = 0; n < hiddenLayer.size(); n++){
			hiddenLayer[n].calculateHiddenGradients(nextLayer);
  		}
  	}

    //------- For all layers from outputs to first hidden layer,
    //------- update connection weights
  	for(unsigned layerNumber = layers.size() -1; layerNumber >0 ; layerNumber--){
		Layer &layer = layers[layerNumber];
		Layer &prevLayer = layers[layerNumber-1];

		for(unsigned n = 0; n < layer.size() -1; n++){
			layer[n].updateInputWeights(prevLayer,eta,alpha);
		}
  	}

}

void Net::getResults(vector<double> &resultValues) const{
	resultValues.clear();

    for (unsigned n = 0; n < layers.back().size() - 1; n++) {
        resultValues.push_back(layers.back()[n].getOutputValue());
    }
}

long double Net::getRecentAverageError(void) const {
	return recentAverageError;
}