#ifndef BIT_NETWORK
#define BIT_NETWORK

#include<cstring>
#include <vector>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include "Matrix.h"
#include <math.h>

using namespace std;
class BitNetwork {
	public:
		int numLayers;
		vector<Matrix> layers;
		vector<Matrix> bias;
		BitNetwork(int hiddenLayers[], int sizeOfArray);
		BitNetwork();
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