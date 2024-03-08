#include "mnistImage.h"


MNISTImage::MNISTImage(Matrix<double> image, double label) {
    this->image = image;
    this-> label = label;
}
MNISTImage::MNISTImage() {
 cout << "Called\n";
}