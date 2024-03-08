#ifndef BASIC_NETWORK
#define BASIC_NETWORK

#include<cstring>
#include <vector>
#include <iostream>
#include <iomanip>
#include <stdlib.h> 
#include <time.h>
#include "Matrix.h"
#include <math.h>

using namespace std;
class BasicNetwork {
	public:
		int numLayers;
		vector<Matrix<double>> layers;
		vector<Matrix<double>> bias;
		BasicNetwork(int hiddenLayers[], int sizeOfArray);
		BasicNetwork();
		static double sigmoid(double);
		static double sigmoidP(double);
		Matrix<double> forProp(Matrix<double>);
		void backProp(Matrix<double>, Matrix<double>);
		static double rate(double);
		void print();
		void save(char* fileName);
		void load(char* fileName);
};

#endif 