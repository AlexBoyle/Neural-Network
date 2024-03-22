#ifndef MATRIX
#define MATRIX

#include<cstring>
#include <vector>
#include <iostream>
#include <iomanip>
#include <stdlib.h>

using namespace std;
template <class T>
class Matrix: public std::vector<std::vector<T>>{
	public:
		int height;
		int width;
        Matrix(){
        	this->height = 0;
        	this->width = 0;
        }
        Matrix(const Matrix<T>& right){
        	this->height = right.height;
        	this->width = right.width;
        	this->resize(this->height , std::vector<T>( (this->width) , 0));
        	for(int i = 0; i < this->height; i ++) {
        		for(int j = 0; j < this->width; j ++) {
        			(*this)[i][j] = right[i][j];
        		}
        	}
        }
        Matrix(int height, int width): std::vector<std::vector<T>>(){
        	this->height = height;
        	this->width = width;
        	this->resize(this->height , std::vector<T>( (this->width) , 0));
        }
        void print() {
        	for(int i = 0; i < this->height; i ++) {
        		cout << "\n|";
        		for(int j = 0; j < this->width; j ++) {
        			cout << setw(8) << left << fixed << std::setprecision(3) << (*this)[i][j];
        		}
        		cout  << "|";
        	}
        	cout << "\n";
        }
        Matrix<T> operator*(Matrix<T> right) {
        	Matrix temp((*this));
        	return (temp *= right);
        }
        Matrix<T> operator*=(Matrix<T> right) {
        	Matrix temp(right.height, this->width);
        	for(int i = 0; i < right.height; i ++) {
        		for(int j = 0; j < this->width; j ++) {
        			for(int k = 0; k < this->height; k ++) {
        				temp[i][j] += (*this)[k][j] * right[i][k];
        			}
        		}
        	}
        	return temp;
        }
        Matrix<T> operator+=(Matrix<T> right) {
        	for(int i = 0; i < this->height; i ++) {
        		for(int j = 0; j < this->width; j ++) {
        			(*this)[i][j] = (*this)[i][j] + right[i][j];
        		}
        	}
        	return (*this);
        }
        Matrix<T> operator-=(Matrix<T> right) {
        	for(int i = 0; i < this->height; i ++) {
        		for(int j = 0; j < this->width; j ++) {
        			(*this)[i][j] -= right[i][j];
        		}
        	}
        	return *this;
        }
        Matrix<T> operator-(Matrix<T> right) {
        	Matrix temp((*this));
        	return (temp -= right);
        }
        Matrix<T> operator+(Matrix<T> right) {
        	Matrix temp((*this));
        	return (temp += right);
        }
        Matrix<T> operator=(Matrix<T> right) {
        	this->clear();
        	this->height = right.height;
        	this->width = right.width;
        	this->resize(this->height , std::vector<T>( (this->width) , 0));
        	for(int i = 0; i < this->height; i ++) {
        		for(int j = 0; j < this->width; j ++) {
        			(*this)[i][j] = right[i][j];
        		}
        	}
        	return (*this);
        }
        Matrix<T> operator=(Matrix* right) {
        	this->clear();
        	this->height = right->height;
        	this->width = right->width;
        	this->resize(this->height , std::vector<T>( (this->width) , 0));
        	for(int i = 0; i < this->height; i ++) {
        		for(int j = 0; j < this->width; j ++) {
        			(*this)[i][j] = (*right)[i][j];
        		}
        	}
        	delete right;
        	return (*this);
        }
        void randGen(T top, T bot) {
        	srand (time(NULL)); // seed with time bc why not
        	int range =  abs(top - bot);
        	for(int i = 0; i < this->height; i ++) {
        		for(int j = 0; j < this->width; j ++) {
        		    //cout << ((T)((rand() / (double)RAND_MAX) * range)) << "\n";
        			(*this)[i][j] = ((T)((rand() / (double)RAND_MAX) * range)) + bot;
        		}
        	}
        }
        void setTo(T a) {
        	srand (time(NULL));
        	for(int i = 0; i < this->height; i ++) {
        		for(int j = 0; j < this->width; j ++) {
        			(*this)[i][j] = a;
        		}
        	}
        }
        Matrix<T> apply(T (*f)(T)) {
        	for(int i = 0; i < this->height; i ++) {
        		for(int j = 0; j < this->width; j ++) {
        			(*this)[i][j] = (*f)((*this)[i][j]);
        		}
        	}
        	return (*this);
        }
        ~Matrix() {
        	this->clear();
        }
};
#endif 