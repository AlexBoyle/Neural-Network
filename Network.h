#ifndef NETWORK
#define NETWORK

#include<cstring>
#include <vector>
#include <iostream>
#include <iomanip>
#include <stdlib.h> 
#include <time.h>
#include "Matrix.h"
#include <math.h>

using namespace std;
class Network{
	public:
		int numLayers;
		vector<Matrix> layers;
		vector<Matrix> bias;
		Network();
		static double sigmoid(double);
		static double sigmoidP(double);
		Matrix forProp(Matrix);
		void backProp(Matrix, Matrix);
		static double rate(double);
		void print();
		void save(char* fileName);
		void load(char* fileName);
};

#endif 