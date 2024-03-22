#ifndef MATRIX
#define MATRIX

#include<cstring>
#include <vector>
#include <iostream>
#include <iomanip>
#include <stdlib.h> 
#include <time.h>

using namespace std;
template <class T>
class Matrix: public std::vector<std::vector<T>>{
	public:
		int height;
		int width;
		Matrix(const Matrix<T>&);
		Matrix(int,int);
		Matrix();
		Matrix<T> operator*(Matrix<T>);
		Matrix<T> operator-(Matrix<T>);
		Matrix<T> operator+(Matrix<T>);
		Matrix<T> operator*=(Matrix<T>);
		Matrix<T> operator+=(Matrix<T>);
		Matrix<T> operator-=(Matrix<T>);
		Matrix<T> operator=(Matrix<T>);
		Matrix<T> operator=(Matrix<T>*);
		void print();
		void randGen(T top, T bot);
		void setTo(T a);
		Matrix apply( T (*f)(T));
		~Matrix();
};

#endif 