#include "net.h"
#include "trainingdata.h"
#include <time.h>

void showVectorValues(string label, vector<double> &v){
    cout << label << " ";
    for (unsigned i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }

    cout << endl;
}

int main(int argc, char *argv[]){
    srand(time(NULL));
    TrainingData trainData(argv[1]);

    // e.g., { 3, 2, 1 }
    vector<unsigned> topology;
    trainData.getTopology(topology);

    Net net(topology);

    vector<vector<double>> inputValsA, targetValuesA;
    vector<double> inputVals, targetValues, resultValues;
    int trainingPass = 0;

    //Load trainning data from file

    while (!trainData.isEof()) {
        trainingPass++;

        // Get new input data and feed it forward:
        if (trainData.getNextInputs(inputVals) != topology[0]) 
            break;
        inputValsA.push_back(inputVals);

        // Train the net what the outputs should have been:
        trainData.getTargetOutputs(targetValues);
        assert(targetValues.size() == topology.back());
        targetValuesA.push_back(targetValues);
    }

    //run trainnig
    for (int i = 0; i < trainingPass-1; i++){
        
        // Get new input data and feed it forward:
        net.feedForward(inputValsA[i]);
        
                
        // Collect the net's actual output results:
        net.getResults(resultValues);
        //showVectorValues("Outputs:", resultValues);
        
        // Train the net what the outputs should have been:
        net.backPropagation(targetValuesA[i]);
        
        // Report how well the training is working, average over recent samples:
        cout <<net.getRecentAverageError() << endl;
    }
    //cout << endl << "Done" << endl;
}
