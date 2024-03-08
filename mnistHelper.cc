#include "mnistHelper.h"

MNISTHelper::MNISTHelper(char imageFileName[], char labelFileName[]){
    imageFile = ifstream(imageFileName);
    labelFile = ifstream(labelFileName);
    if (imageFile.is_open() && labelFile.is_open()) {
        imageFile.read((char*)&magic_number,sizeof(magic_number));
        this->magic_number = this->reverseInt(magic_number);
        imageFile.read((char*)&this->number_of_images,sizeof(this->number_of_images));
        this->number_of_images = this->reverseInt(this->number_of_images);
        imageFile.read((char*)&n_rows,sizeof(n_rows));
        this->n_rows= this->reverseInt(n_rows);
        imageFile.read((char*)&n_cols,sizeof(n_cols));
        this->n_cols= this->reverseInt(n_cols);
        labelFile.read((char*)&magic_number,sizeof(magic_number));
        this->magic_number = reverseInt(magic_number);
        labelFile.read((char*)&this->number_of_images,sizeof(this->number_of_images));
        this->number_of_images = reverseInt(this->number_of_images);
    }
}
vector<MNISTImage> MNISTHelper::getAll() {
    vector<MNISTImage> allImages = vector<MNISTImage>(this->number_of_images);
    while (this->currentImageIndex < this->number_of_images) {
        MNISTImage image = this->getNext();
        allImages[this->currentImageIndex] = image;
    }
    return allImages;
}

MNISTImage MNISTHelper::getNext(){
    this->currentImageIndex ++;
    unsigned char imageLabel;
    labelFile.read((char*)&imageLabel,sizeof(imageLabel));
    Matrix image(n_rows*n_cols,1);
    for(int r=0;r<n_rows;++r) {
        for(int c=0;c<n_cols;++c) {
            unsigned char temp=0;
            imageFile.read((char*)&temp,sizeof(temp));
            image[((r * n_cols) + c)][0] = (double)temp;
        }
    }
    MNISTImage mnistImage = MNISTImage(image, (double)imageLabel);
   return mnistImage;
}

int MNISTHelper::reverseInt (int i) {
	unsigned char c1, c2, c3, c4;
	c1 = i & 255;
	c2 = (i >> 8) & 255;
	c3 = (i >> 16) & 255;
	c4 = (i >> 24) & 255;
	return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}
void MNISTHelper::printImageMatrix(Matrix img, int width, int height) {
    for(int i = 0; i < width * height; i ++) {
        if(i%width == 0) { cout << "\n"; }
        if(img[i][0] < 10.0) { cout << " ";}
        else if(img[i][0] < 75.0) { cout << "░";}
        else if(img[i][0] < 150.0) { cout << "▒";}
        else if(img[i][0] < 225.0) { cout << "▓";}
        else  { cout << "█";}
    }
    cout << "\n";
}