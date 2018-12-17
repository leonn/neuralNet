#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

long double round(long double f,long double pres){
        return (double) (floor(f*(1.0f/pres) + 0.5)/(1.0f/pres));
}

int main(int argc, char const *argv[]){
	ifstream testFile;
	int tests_cases=0, success=0;

	testFile.open(argv[1]);

	stringstream ss;
	while (!testFile.eof()) {

	 	string line;
	    string label;
	    int target;
	    long double output;

	    getline(testFile, line);
	    if (line.length()<2)
	   		continue;
		getline(testFile, line);
		ss.str(line);
	    ss >> label;
	    if (label.compare("Target_Output:") != 0) {
	        abort();
	    }

	    ss >> target;

		getline(testFile, line);
		ss.str(line);
	    ss >> label;
	    if (label.compare("Output:") != 0) {
	        abort();
	    }
	    ss >> output;

		output=sqrt(output*output);
		if (target==(int)round(output,1))
	    	success++;

	    tests_cases++;
    }
    cout<<success<<" of "<<tests_cases<<endl;

    cout<<"Accuracy = "<<((double)success/(double)tests_cases)*100<<"%"<<endl;
	return 0;
}