#include "BitNetwork.h"

BitNetwork::BitNetwork(){}

BitNetwork::BitNetwork(int layerSizes[], int sizeOfArray){
    numLayers = sizeOfArray;
	layers = vector<Matrix<int>>(numLayers);
	bias = vector<Matrix<int>>(numLayers);
	layers[0] = new Matrix<int>(layerSizes[0],1);
	for(int i = 1; i < numLayers; i ++) {
		layers[i] = new Matrix<int>(layerSizes[i],layerSizes[i-1]);
		bias[i] = new Matrix<int>(layerSizes[i], 1);
		bias[i].setTo(0.0);
		layers[i].apply(initalConditions);
		layers[i].print();
	}
}

int BitNetwork::rate(int x) {
	return x;
}

Matrix<int> BitNetwork::forProp(Matrix<int> input) {
	vector<Matrix<int>> nodes = vector<Matrix<int>>(numLayers);
	nodes[0] = input;
	for(int i = 1; i < numLayers; i ++) {
		nodes[i] = (nodes[i-1] * layers[i])+ bias[i];
		// Apply Activation
		//nodes[i].apply(sigmoid);
        nodes[i].print();
	}
	return  nodes[numLayers-1];
}

void BitNetwork::debug() {
    for(int i = 1; i < numLayers; i ++) {
		layers[i].print();
	}
}

void BitNetwork::backProp(Matrix<int> input, Matrix<int> expected) {
	vector<Matrix<int>> nodes = vector<Matrix<int>>(numLayers);
	nodes[0] = input;

    //For Prop + store of nodes
	for(int i = 1; i < numLayers; i ++) {
		nodes[i] = (nodes[i-1] * layers[i])+ bias[i];
        // Apply Activation
        //nodes[i].apply(sigmoid);
	}

	vector<Matrix<int>> layerErr = vector<Matrix<int>>(numLayers - 1);
	Matrix<int> err =  nodes[numLayers-1]- expected;

	// Generate weight updates
	for(int i = numLayers-1; i > 0; i --) {
		layerErr[i-1] = layers[i];
		//calculate updates
		for(int j = 0; j < layerErr[i-1].height; j ++) {
			for(int k = 0; k < layerErr[i-1].width; k++) {
				layerErr[i-1][j][k] = nodes[i-1][k][0] * (nodes[i][j][0]) * err[j][0];
			}
		}

		// calculate next layer of error
		if(i > 1) {
			Matrix<int> preErr = err;
			err = new Matrix<int>(nodes[i-1].height, 1);
			for(int j = 0; j < err.height; j ++) {
				for(int k = 0; k < nodes[i].height; k ++) {
					err[j][0] += preErr[k][0] * (nodes[i][k][0]) * layers[i][k][j];
				}
			}
		}

	}

	//apply weight updates
	for (int i = 1; i < numLayers; i ++) {
		layerErr[i-1].apply(rate);
		layers[i] = layers[i] - layerErr[i-1];
		double absmean = lambda(layers[i]);
        for(int j = 0; j < layers[i].height; j ++) {
            for(int k = 0; k < layers[i].width; k ++) {
                layers[i][j][k] = quantization(layers[i][j][k], absmean);
            }
        }

	}

}

int BitNetwork::quantization(int w, double absMean) {
	double out = 0;
	double epsilon = 0;
	out = ((double)w / (absMean + epsilon));

	return round(out/abs(out));
}

int BitNetwork::quantizationP(int x) {
	return x;
}
int BitNetwork::initalConditions(int w) {
    return ((double)((rand() / (double)RAND_MAX) * 2.0)) > 1 ? 1 : -1;
}
int BitNetwork::sigmoid(int x) {
	return round((1.0 / (1.0 + (exp((double) -(double)x)))));
}

int BitNetwork::sigmoidP(int x) {
	return round(x * (1.0-(double)x));
}

double BitNetwork::lambda(Matrix<int> m) {
    int lam = 0;
    for(int j = 0; j < m.height; j ++) {
        for(int k = 0; k < m.width; k ++) {
            lam += abs(m[j][k]);
        }
    }
    lam = lam/(double)(m.height * m.width);
    return lam;
}