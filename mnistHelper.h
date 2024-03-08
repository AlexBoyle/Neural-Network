#ifndef MNIST_HELPER
#define MNIST_HELPER

#include<cstring>
#include <vector>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include "Matrix.h"
#include "mnistImage.h"
#include <fstream>

using namespace std;
class MNISTHelper {
	public:
        MNISTHelper(char imageFileName[], char labelFileName[]);
        MNISTHelper();
        vector<MNISTImage> getAll();
        MNISTImage getNext();
        int reverseInt (int i);
        void printImageMatrix(Matrix img, int width, int height);
        int n_rows = 0;
        int n_cols = 0;
        int magic_number = 0;
        int number_of_images = 0;
        int currentImageIndex = -1;
    private:
        ifstream imageFile;
        ifstream labelFile;

};

#endif