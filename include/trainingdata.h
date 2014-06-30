#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class TrainingData{
public:
    TrainingData(const string filename);
    bool isEof();
    void getTopology(vector<unsigned> &topology);
    void getEta(double &eta);
    void getMomentum(double &momentum);
    void getTransferFunction(string &transferFunction);

    // Returns the number of input values read from the file:
    unsigned getNextInputs(vector<double> &inputVals);
    unsigned getTargetOutputs(vector<double> &targetOutputVals);

private:
    ifstream trainingDataFile;
};