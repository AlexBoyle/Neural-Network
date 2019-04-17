#include "Network.h"

Network::Network(){
	int a[] = {3,3,3,3,3,2};
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
	for(int i = numLayers-1; i > 0; i --) {
		Matrix diff = *(layers[i]->clone());
		for(int j = 0; j < diff.height; j ++) {
			for(int k = 0; k < diff.width; k++) {
				double fromVal = (*(nodes[i-1]))[k][0];
				double toVal = (*(nodes[i]))[j][0];
				diff[j][k] = fromVal * sigmoidP(toVal) * err[j][0];
			}
		}
		layerErr[i-1] = diff.clone();
		if(i > 1) {
			Matrix preErr = err;
			err = *(nodes[i-2]->clone());
			for(int j = 0; j < err.height; j ++) {
				err[j][0] = 0;
				for(int k = 0; k < nodes[i]->height; k ++) {
					err[j][0] += preErr[k][0] * sigmoidP((*(nodes[i]))[k][0]) * (*(layers[i]))[k][j];
				}
			}
		}
	}
	for (int i = 1; i < numLayers; i ++) {
		Matrix newLayer = (*(layers[i])) - (*(layerErr[i-1]));
		layers[i] = newLayer.clone();
	}
	
	
	
	/*
	/////////////////////////////////////////////////////////////////////////////////////
	Matrix e1 = result - expected;
	Matrix e2 = ((*(nodes[1]->clone()))).apply(sigmoidP);
	Matrix e3 = *(nodes[0]->clone());
	Matrix e = *(e1.clone());
	for(int i = 0; i < e1.height; i ++) {
		e[i][0] *= e2[i][0];
	}
	Matrix* ErrFor2 = layers[2]->clone();
	for(int i = 0; i < ErrFor2->height ; i++) {
		for(int j = 0; j < ErrFor2->width; j ++) {
			(*(ErrFor2))[i][j] -= (.5 * ((*(nodes[0]))[j][0] * e[i][0]));
		}
	}
	cerr << "here\n";
	/////////////////////////////////////////////////////////////////////////////////////
	Matrix bigBrain = *(e1.clone());
	for(int i = 0; i < 2; i ++) {
		bigBrain[i][0] = ( e[0][0] * (*(layers[2]))[0][1]) + (e[1][0] * (*(layers[2]))[1][1]);
	}
	Matrix e4 = ((*(nodes[0]->clone()))).apply(sigmoidP);
	Matrix* ErrFor1 = layers[1]->clone();
	for(int i = 0; i < (ErrFor2->height * ErrFor2->width); i++) {
		int hei = i / (int)ErrFor2->height;
		int wid = i % ErrFor2->width;
		(*(ErrFor1))[hei][wid] -= (.5 * (bigBrain[hei][0] * e4[hei][0] * (*(layers[0]))[wid][0]));
	}
	/////////////////////////////////////////////////////////////////////////////////////
	*/
	//layers[1] = (*ErrFor1).clone();
	//layers[2] = (*ErrFor2).clone();
}
double Network::err (double x) {
	return .5*(x*x);
}
double Network::err1 (double x) {
	return x*(1-x);
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