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


    vector<vector<double>> inputValsA, targetValuesA;
    vector<double> inputVals, targetValues, resultValues;

    double minError=atof(argv[2]);
    double recentAverageError;
    int trainingPass = 0;
    int epochs=0;
    bool test=false;
    int maxEpochs=atoi(argv[3]);

    if(argc==5)
            test=true;

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
    
    Net net(topology,&trainingPass);
    do{
       
       for (int i = 0; i < trainingPass; i++){        
            // Get new input data and feed it forward:
            net.feedForward(inputValsA[i]);        
                    
            // Collect the net's actual output results:
            net.getResults(resultValues);
          
            // Train the net what the outputs should have been:
            net.backPropagation(targetValuesA[i]);
            
            // Report how well the training is working, average over recent samples:
            recentAverageError=net.getRecentAverageError();
            if (!test)
                cout <<recentAverageError<<endl;
        }
        
        recentAverageError/=trainingPass;

        //error/=(* numPatterns); //get average error squared
        epochs++;
    }while(recentAverageError>minError && epochs<=maxEpochs);

    if (test){
         for (int i = 0; i < trainingPass; i++){    
        // Get new input data and feed it forward:][]
            net.feedForward(inputValsA[i]);        
            showVectorValues("Inputs:", inputValsA[i]); 
                    
            // Collect the net's actual output results:
            net.getResults(resultValues);
            showVectorValues("Outputs:", resultValues); 
        }
    }
}
