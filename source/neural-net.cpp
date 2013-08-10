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

    vector<double> inputVals, targetValues, resultValues;
    int trainingPass = 0;

    while (!trainData.isEof()) {
        cout << endl << "Pass " << trainingPass;
        trainingPass++;

        // Get new input data and feed it forward:
        if (trainData.getNextInputs(inputVals) != topology[0]) {
            break;
        }
        showVectorValues(": Inputs:", inputVals);
        net.feedForward(inputVals);

        // Collect the net's actual output results:
        net.getResults(resultValues);
        showVectorValues("Outputs:", resultValues);

        // Train the net what the outputs should have been:
        trainData.getTargetOutputs(targetValues);
        showVectorValues("Targets:", targetValues);
        assert(targetValues.size() == topology.back());
 
        net.backPropagation(targetValues);

        // Report how well the training is working, average over recent samples:
        cout << "Net recent average error: "
                << net.getRecentAverageError() << endl;
    }

    cout << endl << "Done" << endl;
}
