#include "Matrix.h"


int Matrix::a = 0;
Matrix::Matrix(){
	a++;
	this->height = 0;
	this->width = 0;
}

Matrix::Matrix(const Matrix& right){
	a++;
	this->height = right.height;
	this->width = right.width;
	this->resize(this->height , std::vector<double>( (this->width) , 0));
	for(int i = 0; i < this->height; i ++) {
		for(int j = 0; j < this->width; j ++) {
			(*this)[i][j] = right[i][j];
		}
	}
}

Matrix::Matrix(int height, int width): std::vector<std::vector<double>>(){
	a++;
	this->height = height;
	this->width = width;
	this->resize(this->height , std::vector<double>( (this->width) , 0));
}

void Matrix::print() {
	for(int i = 0; i < this->height; i ++) {
		cerr << "\n|";
		for(int j = 0; j < this->width; j ++) {
			cerr << setw(12) << left << (*this)[i][j];
		}
		cerr  << "|";
	}
	cerr << "\n";
}
Matrix Matrix::operator*(Matrix right) {
	Matrix temp((*this));
	return (temp *= right);
}
Matrix Matrix::operator*=(Matrix right) {
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
Matrix Matrix::operator+=(Matrix right) {
	for(int i = 0; i < this->height; i ++) {
		for(int j = 0; j < this->width; j ++) {
			(*this)[i][j] = (*this)[i][j] + right[i][j];
		}
	}
	return (*this);
}
Matrix Matrix::operator-=(Matrix right) {
	for(int i = 0; i < this->height; i ++) {
		for(int j = 0; j < this->width; j ++) {
			(*this)[i][j] -= right[i][j];
		}
	}
	return *this;
}
Matrix Matrix::operator-(Matrix right) {
	Matrix temp((*this));
	return (temp -= right);
}
Matrix Matrix::operator+(Matrix right) {
	Matrix temp((*this));
	return (temp += right);
}
Matrix Matrix::operator=(Matrix right) {
	this->clear();
	this->height = right.height;
	this->width = right.width;
	this->resize(this->height , std::vector<double>( (this->width) , 0));
	for(int i = 0; i < this->height; i ++) {
		for(int j = 0; j < this->width; j ++) {
			(*this)[i][j] = right[i][j];
		}
	}
	return (*this);
}
Matrix Matrix::operator=(Matrix* right) {
	this->clear();
	this->height = right->height;
	this->width = right->width;
	this->resize(this->height , std::vector<double>( (this->width) , 0));
	for(int i = 0; i < this->height; i ++) {
		for(int j = 0; j < this->width; j ++) {
			(*this)[i][j] = (*right)[i][j];
		}
	}
	delete right;
	return (*this);
}
void Matrix::randGen() {
	srand (time(NULL));
	for(int i = 0; i < this->height; i ++) {
		for(int j = 0; j < this->width; j ++) {
			(*this)[i][j] = (((double) rand()) / (double) RAND_MAX)*.001;
		}
	}
}
Matrix Matrix::apply( double (*f)(double)) {
	for(int i = 0; i < this->height; i ++) {
		for(int j = 0; j < this->width; j ++) {
			(*this)[i][j] = (*f)((*this)[i][j]);
		}
	}
	return (*this);
}
Matrix::~Matrix() {
	this->clear();
}