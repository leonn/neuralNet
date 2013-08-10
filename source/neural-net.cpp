#include "net.h"
#include "trainingdata.h"
#include <time.h>

void showVectorValues(string label, vector<double> &v){
    cout << label << " ";
    for (unsigned i = 0; i < v.size(); ++i) {
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

    vector<double> inputVals, targetVals, resultVals;
    int trainingPass = 0;

    while (!trainData.isEof()) {
        ++trainingPass;
        cout << endl << "Pass " << trainingPass;

        // Get new input data and feed it forward:
        if (trainData.getNextInputs(inputVals) != topology[0]) {
            break;
        }
        showVectorValues(": Inputs:", inputVals);
        net.feedForward(inputVals);

        // Collect the net's actual output results:
        net.getResults(resultVals);
        showVectorValues("Outputs:", resultVals);

        // Train the net what the outputs should have been:
        trainData.getTargetOutputs(targetVals);
        showVectorValues("Targets:", targetVals);
        assert(targetVals.size() == topology.back());

        net.backPropagation(targetVals);

        // Report how well the training is working, average over recent samples:
        cout << "Net recent average error: "
                << net.getRecentAverageError() << endl;
    }

    cout << endl << "Done" << endl;
}
