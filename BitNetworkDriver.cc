#include<cstring>
#include "Matrix.h"

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
/*
int magic_number=0;
int number_of_images=0;
int n_rows=0;
int n_rows1=0;
int n_cols=0;
int n_cols1=0;
Network* net = new Network();
void read_mnist();
int reverseInt (int);
char imageFileName[] = "./train-images.idx3-ubyte";
char labelFileName[] = "./train-labels.idx1-ubyte";

char imageFileNameT[] = "./t10k-images.idx3-ubyte";
char labelFileNameT[] = "./t10k-labels.idx1-ubyte";
void check();

int main(int argc, char *argv[]) {
    for(int i = 0; i < 1; i ++) {
	    read_mnist();
	}
	check();
}

int reverseInt (int i) {
	unsigned char c1, c2, c3, c4;
	c1 = i & 255;
	c2 = (i >> 8) & 255;
	c3 = (i >> 16) & 255;
	c4 = (i >> 24) & 255;
	return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}

void printImageMatrix(Matrix img, int width, int height) {
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
double normalizeImage(double x) {
	return x/255.0;
}
void read_mnist() {
	ifstream imageFile (imageFileName);
	ifstream labelFile (labelFileName);
	if (imageFile.is_open() && labelFile.is_open())
	{
        // Read and get basic info from Image file
		imageFile.read((char*)&magic_number,sizeof(magic_number));
		magic_number= reverseInt(magic_number);
		imageFile.read((char*)&number_of_images,sizeof(number_of_images));
		number_of_images= reverseInt(number_of_images);
		imageFile.read((char*)&n_rows,sizeof(n_rows));
		n_rows= reverseInt(n_rows);
		imageFile.read((char*)&n_cols,sizeof(n_cols));
		n_cols= reverseInt(n_cols);

		// Read and get basic info from Label file
		labelFile.read((char*)&magic_number,sizeof(magic_number)); 
		magic_number= reverseInt(magic_number);
		labelFile.read((char*)&number_of_images,sizeof(number_of_images));
		number_of_images= reverseInt(number_of_images);

		for(int i=0;i<number_of_images;++i) {
			if(i%10000 == 0) { cout << "Read " << setw(5) << i << "/60000 images\n"; }
			
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
			image.apply(normalizeImage);

			Matrix expected(10,1);
			for(int j = 0; j < 10; j ++) {
				if(j == (double)imageLabel) {
					expected[j][0] = 1;
				}
			}

			net->backProp(image,expected);
		}
		cout << "Finished Reading images\n";

	}
	else {
		cout << "File failed to open mnist\n";
	}
}
void check()
{
	ifstream imageFile (imageFileNameT);
    ifstream labelFile (labelFileNameT);
	if (imageFile.is_open() && labelFile.is_open())
	{
	    // Read and get basic info from Image file
		imageFile.read((char*)&magic_number,sizeof(magic_number)); 
		magic_number= reverseInt(magic_number);
		imageFile.read((char*)&number_of_images,sizeof(number_of_images));
		number_of_images= reverseInt(number_of_images);
		imageFile.read((char*)&n_rows,sizeof(n_rows));
		n_rows= reverseInt(n_rows);
		imageFile.read((char*)&n_cols,sizeof(n_cols));
		n_cols= reverseInt(n_cols);

		// Read and get basic info from Label file
		labelFile.read((char*)&magic_number,sizeof(magic_number)); 
		magic_number= reverseInt(magic_number);
		labelFile.read((char*)&number_of_images,sizeof(number_of_images));
		number_of_images= reverseInt(number_of_images);
        int amtChecked = number_of_images;
        int amtCorrect = 0;
		for(int i=0;i<number_of_images;++i)
		{
			unsigned char imageLabel=0;
			labelFile.read((char*)&imageLabel,sizeof(imageLabel));
			Matrix image(n_rows*n_cols,1);
			for(int r=0;r<n_rows;++r)
			{
				for(int c=0;c<n_cols;++c)
				{
					unsigned char temp=0;
					imageFile.read((char*)&temp,sizeof(temp));
					image[((r * n_cols) + c)][0] = (double)temp;
				}
			}
			image.apply(normalizeImage);
			Matrix out = net->forProp(image);
			int outputNumber = 0;
			double chance = 0.0;
			for (long unsigned int i = 0; i < out.size(); i ++) {
			    if(chance < out[i][0]) {
			    outputNumber = i;
			    chance = out[i][0];
			    }
			}
			if((int)imageLabel == outputNumber){amtCorrect++;}
			break;
		}
		cout << "Got " << amtCorrect << " out of " << amtChecked << " correct\n";
		cout << "Finished Reading images\n";
	}
	else {
		cout << "File failed to open mnist\n";
	}
}

*/