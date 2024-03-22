#include "BasicNetworkDriver.h"

BasicNetworkDriver::BasicNetworkDriver() {





}

void BasicNetworkDriver::run() {
    cout << "Starting Basic Network Driver\n";
    int layers[] = {784, 16, 10};
    int len = 3;
    long numOfParams = 0;
    for(int i = 0; i < len-1; i ++) {
        numOfParams += ((long)layers[i]*(long)layers[i+1]);
    }
    cout << "Generating network of " << numOfParams << " params" << "\n";
    basicNetwork.init(layers, len);
    trainNetwork();
	checkNetwork();
}

void BasicNetworkDriver::trainNetwork() {
        char trainingImagesFilename[] = "./train-images.idx3-ubyte";
        char trainingLabelsFilename[] = "./train-labels.idx1-ubyte";
        MNISTHelper mnistTrainingSet = MNISTHelper(trainingImagesFilename, trainingLabelsFilename);
        cout << "~~~~~~~~~~~~~~~~ Start training ~~~~~~~~~~~~~~~ \n";
		for(int i = 0; i < mnistTrainingSet.number_of_images; ++i) {
			if(i%10000 == 0) { cout << "Trained with " << setw(5) << i << "/" << mnistTrainingSet.number_of_images << " images\n"; }

			MNISTImage mnistImage = mnistTrainingSet.getNext();
			mnistImage.image.apply(Utility::normalizeImageToOne);
			Matrix<double> expected(10,1);
			expected[(int)mnistImage.label][0] = 1;
			basicNetwork.backProp(mnistImage.image,expected);
		}
		cout << "~~~~~~~~~~~~~~ Finished training ~~~~~~~~~~~~~~~ \n\n";

}
void BasicNetworkDriver::checkNetwork()
{
        char testingImagesFilename[] = "./t10k-images.idx3-ubyte";
        char testingLabelsFilename[] = "./t10k-labels.idx1-ubyte";
        MNISTHelper mnistTestingSet = MNISTHelper(testingImagesFilename, testingLabelsFilename);
        cout << "~~~~~~~~~~~~~~~~~~ Start Check ~~~~~~~~~~~~~~~~~ \n";
        int amtCorrect = 0;
		for(int i=0;i<mnistTestingSet.number_of_images;++i)
		{
			MNISTImage mnistImage = mnistTestingSet.getNext();
			mnistImage.image.apply(Utility::normalizeImageToOne);
			Matrix<double> out = basicNetwork.forProp(mnistImage.image);
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
		cout << "Got " << amtCorrect << " out of " << mnistTestingSet.number_of_images << " correct\n";
		cout << "Or " << ((double)amtCorrect/(double)mnistTestingSet.number_of_images)*100 << "%\n";
		cout << "~~~~~~~~~~~~~~~~~~~ End Check ~~~~~~~~~~~~~~~~~~ \n";
}

