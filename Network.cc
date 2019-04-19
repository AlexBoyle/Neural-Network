#include "Network.h"

Network::Network(){
	int a[] = {784,16,16,16,10};
	numLayers = sizeof(a)/sizeof(*a);
	layers = vector<Matrix*>(numLayers);
	layers[0] = new Matrix(a[0],1);
	layers[0]->randGen();
	for(int i = 1; i < numLayers; i ++) {
		delete layers[i];
		layers[i] = new Matrix(a[i],a[i-1]);
		layers[i]->randGen();
	}
}
Matrix* Network::forProp(Matrix input){
	Matrix* result = input.clone();
	for(int i = 1; i < numLayers; i ++) {
		Matrix* old = result;
		result = (*(result)) * (*(layers[i]));
		delete old;
		result->apply(this->sigmoid);
	}
	return result;
}
void Network::backProp(Matrix input, Matrix expected) {
	vector<Matrix*> nodes = vector<Matrix*>(numLayers);
	nodes[0] = input.clone();
	for(int i = 1; i < numLayers; i ++) {
		nodes[i] = (*(nodes[i-1])) * (*(layers[i]));
		nodes[i]->apply(this->sigmoid);
	}

	vector<Matrix*> layerErr = vector<Matrix*>(numLayers -1);
	Matrix* err = (*(nodes[numLayers-1])) - expected;
	// Generate weight updates
	for(int i = numLayers-1; i > 0; i --) {
		Matrix* diff = layers[i]->clone();
		//calculate updates
		for(int j = 0; j < diff->height; j ++) {
			for(int k = 0; k < diff->width; k++) {
				(*(diff))[j][k] = ((*(nodes[i-1]))[k][0]) * sigmoidP((*(nodes[i]))[j][0]) * (*(err))[j][0];
			}
		}
		delete layerErr[i-1];
		layerErr[i-1] = diff->clone();
		delete diff;
		// calculate next layer of error
		if(i > 1) {
			Matrix* preErr = err;
			err = new Matrix(nodes[i-1]->height, 1);
			for(int j = 0; j < err->height; j ++) {
				for(int k = 0; k < nodes[i]->height; k ++) {
					(*(err))[j][0] += (*(preErr))[k][0] * sigmoidP((*(nodes[i]))[k][0]) * (*(layers[i]))[k][j];
				}
			}
			delete preErr;
		}
	}
	nodes.clear();
	delete err;
	//apply weight updates
	for (int i = 1; i < numLayers; i ++) {
		Matrix* newLayer = (*(layers[i])) - (*(layerErr[i-1]));
		delete layers[i];
		layers[i] = newLayer;
	}
	layerErr.clear();
}
double Network::sigmoid(double x) {
	return (1 / (1 + (exp((double) -x))));
}
double Network::sigmoidP(double x) {
	return x * (1-x);
}