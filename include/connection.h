#ifndef CONNECTION_H
#define CONNECTION_H
#include <iostream>

using namespace std;
class Connection{
	static long double randomWeight(){
		return rand()/double(RAND_MAX);
	}

public:
	long double weight;
    long double deltaWeight;

	Connection();
};

#endif