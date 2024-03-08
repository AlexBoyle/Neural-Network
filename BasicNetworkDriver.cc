#include<cstring>
#include "Matrix.h"
#include "BasicNetwork.h"
#include "mnistHelper.h"
#include "mnistImage.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int magic_number=0;
int number_of_images=0;
int n_rows=0;
int n_rows1=0;
int n_cols=0;
int n_cols1=0;
BasicNetwork basicNetwork = BasicNetwork((int[]){784, 16, 10}, 3);

char trainingImagesFilename[] = "./train-images.idx3-ubyte";
char trainingLabelsFilename[] = "./train-labels.idx1-ubyte";
char testingImagesFilename[] = "./t10k-images.idx3-ubyte";
char testingLabelsFilename[] = "./t10k-labels.idx1-ubyte";
void trainNetwork();
void checkNetwork();
MNISTHelper* mnistTrainingSet = new MNISTHelper(trainingImagesFilename, trainingLabelsFilename);
MNISTHelper* mnistTestingSet = new MNISTHelper(testingImagesFilename, testingLabelsFilename);

int main(int argc, char *argv[]) {
    trainNetwork();
	checkNetwork();
}

double normalizeImage(double x) {
	return x/255.0;
}
void trainNetwork() {
        cout << "~~~~~~~~~~~~~~~~ Start training ~~~~~~~~~~~~~~~ \n";
		for(int i = 0; i < mnistTrainingSet->number_of_images; ++i) {
			if(i%10000 == 0) { cout << "Trained with " << setw(5) << i << "/" << mnistTrainingSet->number_of_images << " images\n"; }

			MNISTImage mnistImage = mnistTrainingSet->getNext();
			mnistImage.image.apply(normalizeImage);
			Matrix expected(10,1);
			expected[(int)mnistImage.label][0] = 1;
			basicNetwork.backProp(mnistImage.image,expected);
		}
		cout << "~~~~~~~~~~~~~~ Finished training ~~~~~~~~~~~~~~~ \n\n";

}
void checkNetwork()
{
        cout << "~~~~~~~~~~~~~~~~~~ Start Check ~~~~~~~~~~~~~~~~~ \n";
        int amtCorrect = 0;
		for(int i=0;i<mnistTestingSet->number_of_images;++i)
		{
			MNISTImage mnistImage = mnistTestingSet->getNext();
			mnistImage.image.apply(normalizeImage);
			Matrix out = basicNetwork.forProp(mnistImage.image);
			int outputNumber = 0;
			double chance = 0.0;
			for (long unsigned int i = 0; i < out.size(); i ++) {
			    if(chance < out[i][0]) {
			    outputNumber = i;
			    chance = out[i][0];
			    }
			}
			if((int)mnistImage.label == outputNumber){amtCorrect++;}
		}
		cout << "Got " << amtCorrect << " out of " << mnistTestingSet->number_of_images << " correct\n";
		cout << "~~~~~~~~~~~~~~~~~~~ End Check ~~~~~~~~~~~~~~~~~~ \n";
}

