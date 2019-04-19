#include "Matrix.h"

Matrix::Matrix(){
	this->height = 0;
	this->width = 0;
}
Matrix::Matrix(int height, int width): std::vector<std::vector<double>>(){
	srand (time(NULL));
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
Matrix* Matrix::operator*(Matrix right) {
	Matrix* out = new Matrix(right.height, this->width);
	for(int i = 0; i < right.height; i ++) {
		for(int j = 0; j < this->width; j ++) {
			for(int k = 0; k < this->height; k ++) {
				(*out)[i][j] += (*this)[k][j] * right[i][k];
			}
		}
	}
	return out;
}
Matrix* Matrix::operator-(Matrix right) {
	Matrix* out = new Matrix(this->height, this->width);
	for(int i = 0; i < this->height; i ++) {
		for(int j = 0; j < this->width; j ++) {
			(*out)[i][j] = (*this)[i][j] - right[i][j];
		}
	}
	return out;
}
Matrix* Matrix::operator+(Matrix right) {
	Matrix* out = new Matrix(this->height, this->width);
	for(int i = 0; i < this->height; i ++) {
		for(int j = 0; j < this->width; j ++) {
			(*out)[i][j] = (*this)[i][j] + right[i][j];
		}
	}
	return out;
}
Matrix* Matrix::operator=(Matrix right) {
	this->clear();
	this->height = right.height;
	this->width = right.width;
	this->resize(this->height , std::vector<double>( (this->width) , 0));
	for(int i = 0; i < this->height; i ++) {
		for(int j = 0; j < this->width; j ++) {
			(*this)[i][j] = right[i][j];
		}
	}
	return this;
}
void Matrix::randGen() {
	for(int i = 0; i < this->height; i ++) {
		for(int j = 0; j < this->width; j ++) {
			(*this)[i][j] = ((double) rand()) / (double) RAND_MAX;
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
Matrix Matrix::trans() {
	Matrix* out = new Matrix(this->width, this->height);
	for(int i = 0; i < this->height; i ++) {
		for(int j = 0; j < this->width; j ++) {
			(*out)[j][i] = (*this)[i][j];
		}
	}
	return *out;
}
Matrix* Matrix::clone() {
	Matrix* out = new Matrix(this->height, this->width);
	for(int i = 0; i < this->height; i ++) {
		for(int j = 0; j < this->width; j ++) {
			(*out)[i][j] = (*this)[i][j];
		}
	}
	return out;
}
Matrix::~Matrix() {
	this->clear();
}