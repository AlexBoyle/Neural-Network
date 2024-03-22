#include "BasicNetwork.h"

BasicNetwork::BasicNetwork(){}

BasicNetwork::BasicNetwork(int layerSizes[], int sizeOfArray){

}
void BasicNetwork::init(int layerSizes[], int sizeOfArray) {
    numLayers = sizeOfArray;
	layers = vector<Matrix<double>>(numLayers);
	bias = vector<Matrix<double>>(numLayers);
	layers[0] = Matrix<double>(layerSizes[0],1);
	for(int i = 1; i < numLayers; i ++) {
        layers[i] = Matrix<double>(layerSizes[i],layerSizes[i-1]);
        bias[i] = Matrix<double>(layerSizes[i], 1);
        bias[i].setTo(0.0);
        layers[i].apply(initalConditions);
    }
}
double BasicNetwork::rate(double x) {
	return x;
}

Matrix<double> BasicNetwork::forProp(Matrix<double> input) {
	vector<Matrix<double>> nodes = vector<Matrix<double>>(numLayers);
	nodes[0] = input;
	for(int i = 1; i < numLayers; i ++) {
		nodes[i] = (nodes[i-1] * layers[i])+ bias[i];
		nodes[i].apply(sigmoid);
	}
	return  nodes[numLayers-1];
}

void BasicNetwork::backProp(Matrix<double> input, Matrix<double> expected) {
	vector<Matrix<double>> nodes = vector<Matrix<double>>(numLayers);
	vector<Matrix<double>> layerErr = vector<Matrix<double>>(numLayers - 1);
	Matrix<double> preErr;
	Matrix<double> err;
    Matrix<double> nexErr;

	nodes[0] = input;
	for(int i = 1; i < numLayers; i ++) {
		nodes[i] = (nodes[i-1] * layers[i])+ bias[i];
        nodes[i].apply(sigmoid);
	}
	err =  nodes[numLayers-1]- expected;
	// Generate weight updates
	for(int i = numLayers-1; i > 0; i --) {
		layerErr[i-1] = layers[i];
		preErr = err;
		nexErr = Matrix<double>(nodes[i-1].height, 1);
		//calculate updates
		for(int j = 0; j < layerErr[i-1].height; j ++) {
			for(int k = 0; k < layerErr[i-1].width; k++) {
				layerErr[i-1][j][k] = nodes[i-1][k][0] * sigmoidP(nodes[i][j][0]) * err[j][0];
				nexErr[k][0] += preErr[j][0] * sigmoidP(nodes[i][j][0]) * layers[i][j][k];
			}
		}
        err = nexErr;
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
double BasicNetwork::initalConditions(double w) {
    return ((double)((rand() / (double)RAND_MAX) * 2.0)) + -1.0;
}