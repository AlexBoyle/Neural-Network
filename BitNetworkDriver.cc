#include "BitNetworkDriver.h"

BitNetworkDriver::BitNetworkDriver() {
    int layers[] = {784, 16, 10};
    bitNetwork = BitNetwork(layers, 3);
}

void BitNetworkDriver::run() {
    cout << "Starting Bit Network Driver\n";

    trainNetwork();
	checkNetwork();
}

void BitNetworkDriver::trainNetwork() {
        char trainingImagesFilename[] = "./train-images.idx3-ubyte";
        char trainingLabelsFilename[] = "./train-labels.idx1-ubyte";
        MNISTHelper mnistTrainingSet = MNISTHelper(trainingImagesFilename, trainingLabelsFilename);
        cout << "~~~~~~~~~~~~~~~~ Start training ~~~~~~~~~~~~~~~ \n";
        //mnistTrainingSet.number_of_images
		for(int i = 0; i < mnistTrainingSet.number_of_images; ++i) {
			if(i%10000 == 0) { cout << "Trained with " << setw(5) << i << "/" << mnistTrainingSet.number_of_images << " images\n"; }

			MNISTImage mnistImage = mnistTrainingSet.getNext();
			mnistImage.image.apply(Utility::normalizeImageToTernary);

			Matrix<int> expected(10,1);
			expected.setTo(-1);
			expected[(int)mnistImage.label][0] = 1;

			Matrix<int> image = Utility::matrixConverter<double, int>(mnistImage.image);

			bitNetwork.backProp(image,expected);
			//return;
		}
		bitNetwork.debug();
		cout << "~~~~~~~~~~~~~~ Finished training ~~~~~~~~~~~~~~~ \n\n";

}
void BitNetworkDriver::checkNetwork()
{
        char testingImagesFilename[] = "./t10k-images.idx3-ubyte";
        char testingLabelsFilename[] = "./t10k-labels.idx1-ubyte";
        MNISTHelper mnistTestingSet = MNISTHelper(testingImagesFilename, testingLabelsFilename);
        cout << "~~~~~~~~~~~~~~~~~~ Start Check ~~~~~~~~~~~~~~~~~ \n";
        int amtCorrect = 0;
		for(int i=0;i<2;++i)
		{
			MNISTImage mnistImage = mnistTestingSet.getNext();
			mnistImage.image.apply(Utility::normalizeImageToTernary);
			Matrix<int> image = Utility::matrixConverter<double, int>(mnistImage.image);
			Matrix<int> out = bitNetwork.forProp(image);
			int outputNumber = 0;
			double chance = 0.0;
			for (long unsigned int i = 0; i < out.size(); i ++) {
			    if(chance < out[i][0]) {
			    outputNumber = i;
			    chance = out[i][0];
			    }
			}
			out.print();
			cout << "Expected: " << (int)mnistImage.label << " Got: " << outputNumber << "\n";
			if((int)mnistImage.label == outputNumber){amtCorrect++;}

		}
		cout << "Got " << amtCorrect << " out of " << mnistTestingSet.number_of_images << " correct\n";
		cout << "Or " << ((double)amtCorrect/(double)mnistTestingSet.number_of_images)*100 << "%\n";
		cout << "~~~~~~~~~~~~~~~~~~~ End Check ~~~~~~~~~~~~~~~~~~ \n";
}

