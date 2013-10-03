#ifndef NEURON_H
#define NEURON_H
#include <iostream>
#include "layer.h"
#include "math.h"
#include "connection.h"

using namespace std;
class Neuron{ 

	double outputValue;
	
	double gradient;

	unsigned index;
 	
 	// [0.0..1.0] overall net training rate
 	// 0.0 slow learner
 	// 0.2 medium learner
 	// 1.0 reckless learner

	// [0.0..n] multiplier of last weight change (momentum)
	// 0.0 no momentum
	// 0.5 moderate momentum

	//conections weights
	vector<Connection> outputWeights;

	//	---- transfer Functions hiperbolic tangent
    static double transferFunctionTanH(double x);

	static double transferFunctionTanHDerivative(double x);

	//	---- transfer Functions sigmoid
    static double transferFunctionSig(double x);

	static double transferFunctionSigDerivative(double x);

	//	---- transfer Functions step
    static double transferFunctionStep(double x);

	static double transferFunctionStepDerivative();
   
    // sum of diff of weights of next layer
    double sumDOW(const Layer &nextLayer) const;

public:
	Neuron(unsigned numberOutputs, unsigned index);

	void setOutputValue(double value);

	double getOutputValue() const;

	void feedForward(const Layer &prevLayer);

	void calculateOutputGradients(double targetValue);
	void calculateHiddenGradients(const Layer &nextLayer);
	void updateInputWeights(Layer &prevLayer, const double &eta, const double &alpha);
	

};

#endif