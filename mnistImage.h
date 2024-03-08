#ifndef MNIST_IMAGE
#define MNIST_IMAGE

#include<cstring>
#include <vector>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include "Matrix.h"
#include <fstream>

using namespace std;
class MNISTImage {
	public:
        MNISTImage(Matrix<double> image, double label);
        MNISTImage();
        Matrix<double> image;
        double label;
};

#endif