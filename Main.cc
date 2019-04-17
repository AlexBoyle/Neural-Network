#include<cstring>
#include "Matrix.h"
#include "Network.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[]) {
	Network* net = new Network();
	Matrix a = net->forProp();
	a.print();
	cerr << "\n back time \n";
	Matrix* exp = new Matrix(3,1);
	(*exp)[0][0] = .01;
	(*exp)[1][0] = .99;
	(*exp)[2][0] = .5;
	net->backProp(*exp);
	
	for(int i = 0; i < 10000; i ++) {
		net->backProp(*exp);
	}
	 a = net->forProp();
	a.print();
	
}


