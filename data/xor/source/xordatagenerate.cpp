#include <iostream>
#include <time.h>

using namespace std;

int main(int argc, char const *argv[]){
	srand(time(NULL));
	int inputs_number=atoi(argv[1]);
	//cout << inputs_number<<argc<<endl;

	cout<<"topology: 2 4 1"<<endl;
	for (int i = 0; i < inputs_number; i++){
		int n1= (int)(2.0*rand() / double(RAND_MAX));
		int n2= (int)(2.0*rand() / double(RAND_MAX));
		int t = n1 ^ n2;
		cout<<"in: "<<n1<<".0 "<<n2<<".0 "<<endl;
		cout<<"out: "<<t<<".0"<<endl;
	}

	return 0;
}