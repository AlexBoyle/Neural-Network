#include<cstring>
#include "Matrix.h"
#include "Network.h"
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
Network* net = new Network();
void read_mnist();
int reverseInt (int);
char* imageFileName = "./train-images.idx3-ubyte";
char* labelFileName = "./train-labels.idx1-ubyte";
void check();

int main(int argc, char *argv[]) {
    for(int i = 0; i < 1; i ++) {
	    read_mnist();
	}
	check();
}

int reverseInt (int i) 
{
	unsigned char c1, c2, c3, c4;

	c1 = i & 255;
	c2 = (i >> 8) & 255;
	c3 = (i >> 16) & 255;
	c4 = (i >> 24) & 255;

	return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}

void printImageMatrix(Matrix img, int width, int height) {
    for(int i = 0; i < width * height; i ++) {
        if(i%width == 0) {
            cout << "\n";
        }
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
void read_mnist()
{
	ifstream imageFile (imageFileName);
	ifstream labelFile (labelFileName);
	if (imageFile.is_open() && labelFile.is_open())
	{

		imageFile.read((char*)&magic_number,sizeof(magic_number));
		magic_number= reverseInt(magic_number);
		imageFile.read((char*)&number_of_images,sizeof(number_of_images));
		number_of_images= reverseInt(number_of_images);
		imageFile.read((char*)&n_rows,sizeof(n_rows));
		n_rows= reverseInt(n_rows);
		imageFile.read((char*)&n_cols,sizeof(n_cols));
		n_cols= reverseInt(n_cols);
		
		labelFile.read((char*)&magic_number,sizeof(magic_number)); 
		magic_number= reverseInt(magic_number);
		labelFile.read((char*)&number_of_images,sizeof(number_of_images));
		number_of_images= reverseInt(number_of_images);
		cout << "numLables: " <<number_of_images << "\n";

		net->print();

		for(int i=0;i<number_of_images;++i)
		{
			if(i%10000 == 0) {
				cout << "Read " << setw(5) << i << "/60000 images\n";

			}
			//if(i == 10000) {break;}
			
			unsigned char temp1=0;
			labelFile.read((char*)&temp1,sizeof(temp1));
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
			//printImageMatrix(((image)), 28, 28);
            //cout << "Image Should Be: " << (double)temp1 << "\n" << "################################################" << "\n";
            //if(i > 10) {exit(0);}
			//eval here
			Matrix expected(10,1);
			for(int j = 0; j < 10; j ++) {
				if(j == (double)temp1) {
					expected[j][0] = 1;
				}
			}
			Matrix::a = 0;
			image.apply(normalizeImage);
			net->backProp(image,expected);
			//cout << "diff: " << Matrix::a << endl;

		}
		cout << "Finished Reading images\n";
		net->print();
	}
	else {
		cout << "File failed to open mnist\n";
	}
}
void check()
{
	ifstream imageFile (imageFileName);
    ifstream labelFile (labelFileName);
	if (imageFile.is_open() && labelFile.is_open())
	{
		imageFile.read((char*)&magic_number,sizeof(magic_number)); 
		magic_number= reverseInt(magic_number);
		imageFile.read((char*)&number_of_images,sizeof(number_of_images));
		number_of_images= reverseInt(number_of_images);
		imageFile.read((char*)&n_rows,sizeof(n_rows));
		n_rows= reverseInt(n_rows);
		imageFile.read((char*)&n_cols,sizeof(n_cols));
		n_cols= reverseInt(n_cols);
		
		labelFile.read((char*)&magic_number,sizeof(magic_number)); 
		magic_number= reverseInt(magic_number);
		labelFile.read((char*)&number_of_images,sizeof(number_of_images));
		number_of_images= reverseInt(number_of_images);
        int amtChecked = 10000;
        int amtCorrect = 0;
		for(int i=0;i<amtChecked;++i)
		{
			unsigned char temp1=0;
			labelFile.read((char*)&temp1,sizeof(temp1));
			Matrix* image = new Matrix(n_rows*n_cols,1);
			for(int r=0;r<n_rows;++r)
			{
				for(int c=0;c<n_cols;++c)
				{
					unsigned char temp=0;
					imageFile.read((char*)&temp,sizeof(temp));
					(*(image))[((r * n_cols) + c)][0] = (double)temp;
				}
			}
			//printImageMatrix((*(image)), 28, 28);

			(*(image)).apply(normalizeImage);
			Matrix out = net->forProp((*(image)));
			//out.print();
			int outputNumber = 0;
			double chance = 0.0;
			for (int i = 0; i < out.size(); i ++) {
			    if(chance < out[i][0]) {
			    outputNumber = i;
			    chance = out[i][0];
			    }
			}
			if((int)temp1 == outputNumber){amtCorrect++;}
			//cout << "Should Be: " << (int)temp1 << " got " << outputNumber << "\n";
			delete image;
		}
		cout << "Got " << amtCorrect << " out of " << amtChecked << " correct\n";
		cout << "Finished Reading images\n";
	}
	else {
		cout << "File failed to open mnist\n";
	}
}

