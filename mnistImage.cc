#include "mnistImage.h"


MNISTImage::MNISTImage(Matrix image, double label) {
    this->image = image;
    this-> label = label;
}
MNISTImage::MNISTImage() {
 cout << "Called\n";
}