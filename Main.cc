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
void check();
double invert(double x) {
	if(x == 1)
		return 0;
	else
		return 1;
}
int main(int argc, char *argv[]) {
	
	for(int i = 0; i < 100000; i ++) {
		Matrix image(2,1);
		image[0][0] = (i%4)/2;
		image[1][0] = i%2;
		Matrix expected(image);
		expected.apply(invert);
		net->backProp(image,expected);
	}
	for(int i = 0; i < 4; i ++) {
		Matrix image1(2,1);
		image1[0][0] = (i%4)/2;
		image1[1][0] = i%2;
		Matrix out = net->forProp(image1);
		cerr << "in:";
		image1.print();
		cerr << "out:";
		out.print();
	}
	
	//read_mnist();
	//check();
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
	ifstream file1 ("../train-labels-idx1-ubyte");
	if (file.is_open() && file1.is_open())
	{
		
		file.read((char*)&magic_number,sizeof(magic_number)); 
		magic_number= reverseInt(magic_number);
		file.read((char*)&number_of_images,sizeof(number_of_images));
		number_of_images= reverseInt(number_of_images);
		file.read((char*)&n_rows,sizeof(n_rows));
		n_rows= reverseInt(n_rows);
		file.read((char*)&n_cols,sizeof(n_cols));
		n_cols= reverseInt(n_cols);
		
		file1.read((char*)&magic_number,sizeof(magic_number)); 
		magic_number= reverseInt(magic_number);
		file1.read((char*)&number_of_images,sizeof(number_of_images));
		number_of_images= reverseInt(number_of_images);
		file1.read((char*)&n_rows1,sizeof(n_rows1));
		for(int i=0;i<number_of_images;++i)
		{
			if(i%100 == 0) {
				cerr << "Read " << setw(5) << i << "/60000 images\n";
			}
			
			unsigned char temp1=0;
			file1.read((char*)&temp1,sizeof(temp1));
			Matrix image(n_rows*n_cols,1);
			for(int r=0;r<n_rows;++r)
			{
				for(int c=0;c<n_cols;++c)
				{
					unsigned char temp=0;
					file.read((char*)&temp,sizeof(temp));
					image[((r * n_cols) + c)][0] = (double)temp;
				}
			}
			//eval here
			Matrix expected(10,1);
			for(int j = 0; j < 10; j ++) {
				if(j == (double)temp1) {
					expected[j][0] = 1;
				}
			}
			//Matrix::a = 0;
			net->backProp(image,expected);
			//cerr << "diff: " << Matrix::a << endl;

		}
		cerr << "Finished Reading images\n";
	}
	else {
		cerr << "File failed to open mnist\n";
	}
}
void check()
{
	ifstream file ("../train-images-idx3-ubyte");
	ifstream file1 ("../train-labels-idx1-ubyte");
	if (file.is_open() && file1.is_open())
	{
		
		file.read((char*)&magic_number,sizeof(magic_number)); 
		magic_number= reverseInt(magic_number);
		file.read((char*)&number_of_images,sizeof(number_of_images));
		number_of_images= reverseInt(number_of_images);
		file.read((char*)&n_rows,sizeof(n_rows));
		n_rows= reverseInt(n_rows);
		file.read((char*)&n_cols,sizeof(n_cols));
		n_cols= reverseInt(n_cols);
		
		file1.read((char*)&magic_number,sizeof(magic_number)); 
		magic_number= reverseInt(magic_number);
		file1.read((char*)&number_of_images,sizeof(number_of_images));
		number_of_images= reverseInt(number_of_images);
		file1.read((char*)&n_rows1,sizeof(n_rows1));
		n_rows1= reverseInt(n_rows1);
		for(int i=0;i<5;++i)
		{
			
			unsigned char temp1=0;
			file1.read((char*)&temp1,sizeof(temp1));
			Matrix* image = new Matrix(n_rows*n_cols,1);
			for(int r=0;r<n_rows;++r)
			{
				for(int c=0;c<n_cols;++c)
				{
					unsigned char temp=0;
					file.read((char*)&temp,sizeof(temp));
					(*(image))[((r * n_cols) + c)][0] = (double)temp;
				}
			}
			//(*(image)).print();
			Matrix out = net->forProp((*(image)));
			out.print();
			cerr << (double)temp1 << endl;
			delete image;
		}
		cerr << "Finished Reading images\n";
	}
	else {
		cerr << "File failed to open mnist\n";
	}
}

