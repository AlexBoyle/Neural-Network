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
		int INPUT_LAYER;
		int NUMBER_OF_LAYERS;
		int NUMBER_OF_WEIGHTS;
		int* layerSetup;
		int numLayers;
		vector<Matrix> weights;
		vector<Matrix> bias;
		Network();
		static double sigmoid(double);
		static double sigmoidP(double);
		vector<Matrix> forProp(Matrix);
		void backProp(Matrix, Matrix);
		static double rate(double);
};

#endif 