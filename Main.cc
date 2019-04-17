#include<cstring>
#include "Matrix.h"
#include "Network.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[]) {
	cerr << "Attempting to train network to (.01, .99)\n";
	cerr << "Network config {3,3,4,3,3,2}\n";
	Network* net = new Network();
	Matrix a;
	Matrix* exp = new Matrix(3,1);
	(*exp)[0][0] = .01;
	(*exp)[1][0] = .99;
	(*exp)[2][0] = .5;
	net->backProp(*exp);
	
	for(int i = 0; i <= 100; i ++) {
		net->backProp(*exp);
		if((i %10) == 0) {
			cerr << "\nOutput at iteration " << i;
			a = net->forProp();
			a.print();
		}
	}
	
}


