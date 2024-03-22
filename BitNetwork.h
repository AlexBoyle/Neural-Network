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
#include <cmath>

using namespace std;
class BitNetwork {
	public:
		int numLayers;
		vector<Matrix<int>> layers;
		vector<Matrix<int>> bias;
		BitNetwork(int hiddenLayers[], int sizeOfArray);
		BitNetwork();
		static int quantization(int, double);
		static int quantizationP(int);
		Matrix<int> forProp(Matrix<int>);
		void backProp(Matrix<int>, Matrix<int>);
		static int rate(int);
		void print();
		void save(char* fileName);
		void load(char* fileName);
        static int initalConditions(int);
        void debug();
        double lambda(Matrix<int> m);
        static int sigmoid(int);
        static int sigmoidP(int);
};

#endif