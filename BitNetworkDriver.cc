#include "BitNetworkDriver.h"

BitNetworkDriver::BitNetworkDriver() {


    int layers[] = {784, 16, 16, 10};
    bitNetwork = BitNetwork(layers, 4);

}

void BitNetworkDriver::run() {
    cout << "Starting Basic Network Driver\n";

    trainNetwork();
	checkNetwork();
}

void BitNetworkDriver::trainNetwork() {
        char trainingImagesFilename[] = "./train-images.idx3-ubyte";
        char trainingLabelsFilename[] = "./train-labels.idx1-ubyte";
        MNISTHelper mnistTrainingSet = MNISTHelper(trainingImagesFilename, trainingLabelsFilename);
        cout << "~~~~~~~~~~~~~~~~ Start training ~~~~~~~~~~~~~~~ \n";
		for(int i = 0; i < mnistTrainingSet.number_of_images; ++i) {
			if(i%10000 == 0) { cout << "Trained with " << setw(5) << i << "/" << mnistTrainingSet.number_of_images << " images\n"; }

			MNISTImage mnistImage = mnistTrainingSet.getNext();
			Utility::printImageMatrix(mnistImage.image, 28, 28);
			mnistImage.image.apply(Utility::normalizeImageToTernary);
			Utility::printImageMatrix1(mnistImage.image, 28, 28);

			Matrix<double> expected(10,1);
			expected[(int)mnistImage.label][0] = 1;
			bitNetwork.backProp(mnistImage.image,expected);
			return;
		}
		cout << "~~~~~~~~~~~~~~ Finished training ~~~~~~~~~~~~~~~ \n\n";

}
void BitNetworkDriver::checkNetwork()
{
        char testingImagesFilename[] = "./t10k-images.idx3-ubyte";
        char testingLabelsFilename[] = "./t10k-labels.idx1-ubyte";
        MNISTHelper mnistTestingSet = MNISTHelper(testingImagesFilename, testingLabelsFilename);
        cout << "~~~~~~~~~~~~~~~~~~ Start Check ~~~~~~~~~~~~~~~~~ \n";
        int amtCorrect = 0;
		for(int i=0;i<mnistTestingSet.number_of_images;++i)
		{
			MNISTImage mnistImage = mnistTestingSet.getNext();
			mnistImage.image.apply(Utility::normalizeImageToTernary);
			Matrix<double> out = bitNetwork.forProp(mnistImage.image);
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

