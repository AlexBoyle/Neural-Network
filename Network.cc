#include "Network.h"

Network::Network(){
	int a[] = {3,3,4,3,3,2};
	numLayers = sizeof(a)/sizeof(*a);
	layers = vector<Matrix*>(numLayers);
	nodes = vector<Matrix*>(numLayers);
	cerr << numLayers;
	bias = vector<Matrix*>(numLayers - 1);
	layers[0] = new Matrix(a[0],1);
	layers[0]->randGen();
	for(int i = 1; i < numLayers; i ++) {
		bias[i-1] = new Matrix(a[i],1);
		layers[i] = new Matrix(a[i],a[i-1]);
		layers[i]->randGen();
	}
	(*(bias[0]))[0][0] = .35;
	(*(bias[0]))[1][0] = .35;
	//(*(bias[0])).print();
	(*(bias[1]))[0][0] = .60;
	(*(bias[1]))[1][0] = .60;

	//(*(layers[2])).print();
	//https://mattmazur.com/2015/03/17/a-step-by-step-backpropagation-example/
}
Matrix Network::forProp(){
	Matrix result = *(layers[0]);
	for(int i = 1; i < numLayers; i ++) {
		result = result * (*(layers[i]));
		result = result + (*(bias[i-1]));
		result.apply(this->sigmoid);
	}
	return result;
}
void Network::backProp(Matrix expected){
	Matrix result = *(layers[0]);
	nodes[0] = result.clone();
	for(int i = 1; i < numLayers; i ++) {
		result = result * (*(layers[i]));
		result = result + (*(bias[i-1]));
		result.apply(this->sigmoid);
		nodes[i] = result.clone();
	}

	vector<Matrix*> layerErr = vector<Matrix*>(numLayers -1);
	Matrix err = result - expected;
	// Generate weight updates
	for(int i = numLayers-1; i > 0; i --) {
		Matrix diff = *(layers[i]->clone());
		//calculate updates
		for(int j = 0; j < diff.height; j ++) {
			for(int k = 0; k < diff.width; k++) {
				double fromVal = (*(nodes[i-1]))[k][0];
				double toVal = (*(nodes[i]))[j][0];
				diff[j][k] = fromVal * sigmoidP(toVal) * err[j][0];
			}
		}
		layerErr[i-1] = diff.clone();
		// calculate next layer of error
		if(i > 1) {
			Matrix preErr = err;
			err = *(nodes[i-1]->clone());
			for(int j = 0; j < err.height; j ++) {
				err[j][0] = 0;
				for(int k = 0; k < nodes[i]->height; k ++) {
					err[j][0] += preErr[k][0] * sigmoidP((*(nodes[i]))[k][0]) * (*(layers[i]))[k][j];
				}
			}
		}
	}
	//apply weight updates
	for (int i = 1; i < numLayers; i ++) {
		Matrix newLayer = (*(layers[i])) - (*(layerErr[i-1]));
		layers[i] = newLayer.clone();
	}
}
double Network::sigmoid(double x) {
	return (1 / (1 + (exp((double) -x))));
}
double Network::sigmoidP(double x) {
	return x * (1-x);
}

/*
np.dot(
	self.input.T,
	(
		np.dot(
			2*(self.y - self.output) * sigmoid_derivative(self.output),
			self.weights2.T
		) 
		* sigmoid_derivative(self.layer1)
	)
)



*/