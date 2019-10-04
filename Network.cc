#include "Network.h"

Network::Network(){
	// First number is "number of inputs"
	// Second number is "number of outputs"
	int temp[] = {784, 16, 10};
	layerSetup = temp;
	INPUT_LAYER = 0;
	NUMBER_OF_LAYERS = (sizeof(temp)/sizeof(*temp));
	NUMBER_OF_WEIGHTS = NUMBER_OF_LAYERS - 1;
	if(NUMBER_OF_LAYERS <= 1) {
		// Error
	}
	weights = vector<Matrix>(NUMBER_OF_WEIGHTS);
	bias = vector<Matrix>(NUMBER_OF_WEIGHTS);
	for(int i = 1; i < NUMBER_OF_LAYERS; i ++) {
		cerr << temp[i] << '\n';
		bias[i-1] = new Matrix(temp[i],1);
		weights[i-1] = new Matrix(temp[i],temp[i-1]);
		
		weights[i-1].randGen();
		bias[i-1].randGen();
	}
}
double Network::rate(double x) {
	return x*.1;
}
vector<Matrix> Network::forProp(Matrix input) {
	//if(layerSetup[INPUT_LAYER] == input.height) {
		vector<Matrix> calculatedNodes = vector<Matrix>(NUMBER_OF_LAYERS);
		calculatedNodes[INPUT_LAYER] = input;
		
		for(int currentLayer = 0; currentLayer < NUMBER_OF_WEIGHTS; currentLayer ++) {
			calculatedNodes[currentLayer + 1] = (calculatedNodes[currentLayer] * weights[currentLayer]) + bias[currentLayer];
			//calculatedNodes[currentLayer + 1].apply(sigmoid);
		}
		return  calculatedNodes;
	//}
	//return vector<Matrix>(NUMBER_OF_LAYERS);
}
void Network::backProp(Matrix input, Matrix expected) {
	vector<Matrix> nodes = this->forProp(input);
	vector<Matrix> errorInWeights = vector<Matrix>(NUMBER_OF_WEIGHTS);
	Matrix errorInLayer = nodes[NUMBER_OF_LAYERS -1] - expected;
	// Generate weight updates
	for(int currentLayer = NUMBER_OF_LAYERS-1; currentLayer > 0; currentLayer --) {
		errorInWeights[currentLayer-1] = new Matrix(weights[currentLayer-1].height, weights[currentLayer-1].width);
		//calculate updates
		for(int j = 0; j < errorInWeights[currentLayer-1].height; j ++) {
			for(int k = 0; k < errorInWeights[currentLayer-1].width; k++) {
				errorInWeights[currentLayer-1][j][k] = (weights[currentLayer-1][j][k] * errorInLayer[j][0]);
			}
		}
		Matrix preErr = errorInLayer;
		errorInLayer = new Matrix(nodes[currentLayer-1].height, 1);
		for(int j = 0; j < errorInLayer.height; j ++) {
			for(int k = 0; k < nodes[currentLayer].height; k ++) {
				errorInLayer[j][0] += preErr[k][0] * nodes[currentLayer][k][0] * weights[currentLayer-1][k][j];
			}
		}

	}

	//apply weight updates
	for (int currentLayer = 0; currentLayer < NUMBER_OF_WEIGHTS; currentLayer ++) {
		//errorInWeights[currentLayer-1].apply(rate);
		weights[currentLayer] = weights[currentLayer] - errorInWeights[currentLayer];
	}
}
double Network::sigmoid(double x) {
	return (1 / (1 + (exp((double) -x))));
}
double Network::sigmoidP(double x) {
	return x * (1-x);
}