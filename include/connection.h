#ifndef CONNECTION_H
#define CONNECTION_H
#include <iostream>

using namespace std;
class Connection{ 
	static double randomWeight(){
		return rand()/double(RAND_MAX);
	}

public:
	double weight;
    double deltaWeight;

	Connection();
	~Connection();

};

#endif