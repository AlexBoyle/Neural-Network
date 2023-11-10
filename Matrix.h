#ifndef MATRIX
#define MATRIX

#include<cstring>
#include <vector>
#include <iostream>
#include <iomanip>
#include <stdlib.h> 
#include <time.h>

using namespace std;
class Matrix: public std::vector<std::vector<double>>{
	public:
		static int a;
		int height;
		int width;
		Matrix::Matrix(const Matrix&);
		Matrix(int,int);
		Matrix();
		Matrix operator*(Matrix);
		Matrix operator-(Matrix);
		Matrix operator+(Matrix);
		Matrix operator*=(Matrix);
		Matrix operator+=(Matrix);
		Matrix operator-=(Matrix);
		Matrix operator=(Matrix);
		Matrix operator=(Matrix*);
		void print();
		void randGen();
		void setTo(double a);
		Matrix apply( double (*f)(double));
		~Matrix();
};

#endif 