#include "net.h"
#include <time.h>
int main(){
    srand(time(NULL));
    //topology contains number of layers & number of neurons per layer
    //ex: {3,2,1}
    vector<unsigned int> topology;
    topology.push_back(3);
    topology.push_back(2);
    topology.push_back(1);
    Net myNet(topology);

    vector<double> inputValues;
    vector<double> targetValues;
    vector<double> resultsValues;

    //feedForward - operation to train the network
    myNet.feedForward(inputValues);

    // brackPropagation learning
    myNet.brackPropagation(targetValues);

    myNet.getResults(resultsValues);

}

