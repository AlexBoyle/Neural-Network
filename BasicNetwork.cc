#include "BasicNetwork.h"

BasicNetwork::BasicNetwork(int layerSizes[], int sizeOfArray){
    numLayers = sizeOfArray;
	layers = vector<Matrix>(numLayers);
	bias = vector<Matrix>(numLayers);
	layers[0] = new Matrix(layerSizes[0],1);
	for(int i = 1; i < numLayers; i ++) {
		layers[i] = new Matrix(layerSizes[i],layerSizes[i-1]);
		bias[i] = new Matrix(layerSizes[i], 1);
		bias[i].setTo(0.0);
		layers[i].randGen();
	}
}

double BasicNetwork::rate(double x) {
	return x;
}

Matrix BasicNetwork::forProp(Matrix input) {
	vector<Matrix> nodes = vector<Matrix>(numLayers);
	nodes[0] = input;
	for(int i = 1; i < numLayers; i ++) {
		nodes[i] = (nodes[i-1] * layers[i])+ bias[i];
		nodes[i].apply(sigmoid);
	}
	return  nodes[numLayers-1];
}

void BasicNetwork::backProp(Matrix input, Matrix expected) {
	vector<Matrix> nodes = vector<Matrix>(numLayers);
	nodes[0] = input;


	for(int i = 1; i < numLayers; i ++) {
		nodes[i] = (nodes[i-1] * layers[i])+ bias[i];
        nodes[i].apply(sigmoid);
	}

	vector<Matrix> layerErr = vector<Matrix>(numLayers - 1);
	Matrix err =  nodes[numLayers-1]- expected;

	// Generate weight updates
	for(int i = numLayers-1; i > 0; i --) {
		layerErr[i-1] = layers[i];
		//calculate updates
		for(int j = 0; j < layerErr[i-1].height; j ++) {
			for(int k = 0; k < layerErr[i-1].width; k++) {
				layerErr[i-1][j][k] = nodes[i-1][k][0] * sigmoidP(nodes[i][j][0]) * err[j][0];
			}
		}

		// calculate next layer of error
		if(i > 1) {
			Matrix preErr = err;
			err = new Matrix(nodes[i-1].height, 1);
			for(int j = 0; j < err.height; j ++) {
				for(int k = 0; k < nodes[i].height; k ++) {
					err[j][0] += preErr[k][0] * sigmoidP(nodes[i][k][0]) * layers[i][k][j];
				}
			}
		}

	}

	//apply weight updates
	for (int i = 1; i < numLayers; i ++) {
		layerErr[i-1].apply(rate);
		layers[i] = layers[i] - layerErr[i-1];
	}

}

double BasicNetwork::sigmoid(double x) {
	return (1.0 / (1.0 + (exp((double) -x))));
}

double BasicNetwork::sigmoidP(double x) {
	return x * (1.0-x);
}