#include "net.h"
#include "trainingdata.h"
#include <time.h>
//#include "gnuplot-iostream.h"

void showVectorValues(string label, vector<double> &v,ofstream &file){
    file << label << " ";
    for (unsigned i = 0; i < v.size(); i++) {
        file << v[i] << " ";
    }
    file << endl;
}

void showTestVectorValues(string label, vector<double> &v,ofstream &file){
    file << label << " ";
    for (unsigned i = 0; i < v.size(); i++) {
        file << v[i] <<" : "<<round(v[i]) << " ";
    }
    file << endl;
}

double round(double f,double pres){
        return (double) (floor(f*(1.0f/pres) + 0.5)/(1.0f/pres));
}

int main(int argc, char *argv[]){
    srand(time(NULL));
    TrainingData trainData(argv[1]);

    // e.g., { 3, 2, 1 }
    vector<unsigned> topology;

    vector<vector<double>> inputValsA, targetValuesA;
    vector<double> inputVals, targetValues, resultValues;

    int trainingPass = 0;
    int epochs=0;
    bool test=false;
    bool testFile=false;
    double minError=atof(argv[2]);
    int maxEpochs=atoi(argv[3]);

    ofstream trainingDataOutput;
    ofstream trainingDataGlobalOutput;
    ofstream testDataOutput;
    TrainingData *testDataInput;

    
    trainingDataOutput.open(argv[4]);
    trainingDataGlobalOutput.open(argv[5]);
    
    if(argc>6){
        if(!strcmp(argv[6],"-t")){
        testDataOutput.open(argv[7]);
        test=true;
        }
        else if(!strcmp(argv[6],"-tf")){
            testDataInput=new TrainingData(argv[7]);
            testDataOutput.open(argv[8]);
            testFile=true;
        }
    }
    //Gnuplot gp;
    double eta,momentum;
    string transferFunction;

    trainData.getTopology(topology);
    trainData.getEta(eta);
    trainData.getMomentum(momentum);
    trainData.getTransferFunction(transferFunction);
    
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
    
    //gp << "set xrange [0:"<<maxEpochs*trainingPass<<"]\nset yrange [-1:2]\n";

    Net net(topology,transferFunction);
    double recentAverageError;
    double globalError;
    
    do{
        globalError=0.0;
       
        for (int i = 0; i < trainingPass; i++){        
            // Get new input data and feed it forward:
            net.feedForward(inputValsA[i]);        
                    
            // Collect the net's actual output results:
            net.getResults(resultValues);
          
            // Train the net what the outputs should have been:
            net.backPropagation(targetValuesA[i],eta,momentum);
            
            // Report how well the training is working, average over recent samples:
            recentAverageError=net.getRecentAverageError();
            globalError+=recentAverageError;
            trainingDataOutput <<recentAverageError<<endl;
            // gp << "plot " << recentAverageError<<endl;
        }
        globalError/=trainingPass;
        trainingDataGlobalOutput <<globalError<<endl;
        epochs++;

    }while(round(globalError,minError)>minError && epochs<maxEpochs);
    
    trainingDataOutput.close();
    trainingDataGlobalOutput.close();

    if (test){
         for (int i = 0; i < trainingPass; i++){    
            // Get new input data and feed it forward:][]
            net.feedForward(inputValsA[i]);        
            showVectorValues("Input:", inputValsA[i],testDataOutput); 

            showVectorValues("Target Output:", targetValuesA[i],testDataOutput); 
            
            // Collect the net's actual output results:
            net.getResults(resultValues);
            showTestVectorValues("Output:", resultValues,testDataOutput); 
        }
    }

    if (testFile){
        trainingPass=0;
        //clear trainning data vectors
        inputValsA.clear();
        targetValuesA.clear();
        inputVals.clear();
        targetValues.clear();
        resultValues.clear();

        //Load trainning data from file
        while (!testDataInput->isEof()) {
            trainingPass++;

            // Get new input data and feed it forward:
            if (testDataInput->getNextInputs(inputVals) != topology[0]) 
                break;
            inputValsA.push_back(inputVals);

            // Train the net what the outputs should have been:
            testDataInput->getTargetOutputs(targetValues);
            assert(targetValues.size() == topology.back());
            targetValuesA.push_back(targetValues);
        }

        for (int i = 0; i < trainingPass; i++){    
            // Get new input data and feed it forward:][]
            net.feedForward(inputValsA[i]);        
            showVectorValues("Input:", inputValsA[i],testDataOutput); 

            showVectorValues("Target Output:", targetValuesA[i],testDataOutput); 
            
            // Collect the net's actual output results:
            net.getResults(resultValues);
            showVectorValues("Output:", resultValues,testDataOutput); 
        }
    }

    testDataOutput.close();
}
