#include "trainingdata.h"

bool TrainingData::isEof(){
    return trainingDataFile.eof();
}

void TrainingData::getTopology(vector<unsigned> &topology){
    string line;
    string label;

    getline(trainingDataFile, line);
    stringstream ss(line);
    ss >> label;
    if (this->isEof() || label.compare("topology:") != 0) {
        abort();
    }

    while (!ss.eof()) {
        unsigned n;
        ss >> n;
        topology.push_back(n);
    }

    return;
}

void TrainingData::getEta(long double &eta){
    string line;
    string label;

    getline(trainingDataFile, line);
    stringstream ss(line);
    ss >> label;
    if (this->isEof() || label.compare("eta:") != 0) {
        abort();
    }

    ss >> eta;

    return;
}

void TrainingData::getTransferFunction(string &transferFunction){
    string line;
    string label;

    getline(trainingDataFile, line);
    stringstream ss(line);
    ss >> label;
    if (this->isEof() || label.compare("transfer_function:") != 0) {
        abort();
    }

    ss >> transferFunction;

    return;
}

void TrainingData::getMomentum(long double &momentum){
    string line;
    string label;

    getline(trainingDataFile, line);
    stringstream ss(line);
    ss >> label;
    if (this->isEof() || label.compare("momentum:") != 0) {
        abort();
    }

    ss >> momentum;

    return;
}

TrainingData::TrainingData(const string filename){
    trainingDataFile.open(filename.c_str());
}

unsigned TrainingData::getNextInputs(vector<double> &inputVals){
    inputVals.clear();

    string line;
    getline(trainingDataFile, line);
    stringstream ss(line);

    string label;
    ss >> label;
    if (label.compare("in:") == 0) {
        long double oneValue;
        while (ss >> oneValue) {
            inputVals.push_back(oneValue);
        }
    }

    return inputVals.size();
}

unsigned TrainingData::getTargetOutputs(vector<double> &targetOutputVals){
    targetOutputVals.clear();

    string line;
    getline(trainingDataFile, line);
    stringstream ss(line);

    string label;
    ss>> label;
    if (label.compare("out:") == 0) {
        long double oneValue;
        while (ss >> oneValue) {
            targetOutputVals.push_back(oneValue);
        }
    }

    return targetOutputVals.size();
}
