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
int n_cols=0;

vector<Matrix*> images;
vector<int> tags;
void read_mnist();
int reverseInt (int);
void read_tags();

int main(int argc, char *argv[]) {
	read_mnist();
	read_tags();
	Network* net = new Network();
	//Train
	for(int i = 0; i < number_of_images; i ++) {
		if(i%100 == 0)
			cerr << "Trained with " << setw(5) << i << "/60000 images\n";
		Matrix* expected = new Matrix(10,1);
		for(int j = 0; j < 10; j ++) {
			if(j == tags[i]) {
				(*(expected))[j][0] = 1;
			}
		}
		net->backProp((*(images[i])),(*(expected)));
	}
	Matrix out = net->forProp((*(images[1])));
	out.print();
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

void read_mnist()
{
	ifstream file ("../train-images-idx3-ubyte");
	if (file.is_open())
	{
		
		file.read((char*)&magic_number,sizeof(magic_number)); 
		magic_number= reverseInt(magic_number);
		file.read((char*)&number_of_images,sizeof(number_of_images));
		number_of_images= reverseInt(number_of_images);
		file.read((char*)&n_rows,sizeof(n_rows));
		n_rows= reverseInt(n_rows);
		file.read((char*)&n_cols,sizeof(n_cols));
		n_cols= reverseInt(n_cols);
		images = vector<Matrix*>(number_of_images);;
		for(int i=0;i<number_of_images;++i)
		{
			if(i%10000 == 0) {
				cerr << "Read " << setw(5) << i << "/60000 images\n";
			}
			Matrix* image = new Matrix(n_rows*n_cols,1);
			for(int r=0;r<n_rows;++r)
			{
				for(int c=0;c<n_cols;++c)
				{
					unsigned char temp=0;
					file.read((char*)&temp,sizeof(temp));
					//cerr << setw(4) << (double)temp ;
					(*(image))[((r * n_cols) + c)][0] = (double)temp;
				}
			}
			images[i] = image->clone();
		}
		cerr << "Finished Reading images\n";
	}
	else {
		cerr << "File failed to open mnist\n";
	}
}
void read_tags()
{
	ifstream file ("../train-labels-idx1-ubyte");
	if (file.is_open())
	{
		
		file.read((char*)&magic_number,sizeof(magic_number)); 
		magic_number= reverseInt(magic_number);
		file.read((char*)&number_of_images,sizeof(number_of_images));
		number_of_images= reverseInt(number_of_images);
		file.read((char*)&n_rows,sizeof(n_rows));
		tags = vector<int>(number_of_images);;
		for(int i=0;i<number_of_images;++i)
		{
			unsigned char temp=0;
			file.read((char*)&temp,sizeof(temp));
			tags[i] = (int)temp;
		}
	}
	else {
		cerr << "File failed to open tags\n";
	}
}

