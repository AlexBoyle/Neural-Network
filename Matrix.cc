#include "Matrix.h"

template <class T>
Matrix<T>::Matrix(){
	this->height = 0;
	this->width = 0;
}
template <class T>
Matrix<T>::Matrix(const Matrix<T>& right){
	this->height = right.height;
	this->width = right.width;
	this->resize(this->height , std::vector<T>( (this->width) , 0));
	for(int i = 0; i < this->height; i ++) {
		for(int j = 0; j < this->width; j ++) {
			(*this)[i][j] = right[i][j];
		}
	}
}
template <class T>
Matrix<T>::Matrix(int height, int width): std::vector<std::vector<T>>(){
	this->height = height;
	this->width = width;
	this->resize(this->height , std::vector<T>( (this->width) , 0));
}
template <class T>
void Matrix<T>::print() {
	for(int i = 0; i < this->height; i ++) {
		cout << "\n|";
		for(int j = 0; j < this->width; j ++) {
			cout << setw(8) << left << fixed << std::setprecision(3) << (*this)[i][j];
		}
		cout  << "|";
	}
	cout << "\n";
}
template <class T>
Matrix<T> Matrix<T>::operator*(Matrix<T> right) {
	Matrix temp((*this));
	return (temp *= right);
}
template <class T>
Matrix<T> Matrix<T>::operator*=(Matrix<T> right) {
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
template <class T>
Matrix<T> Matrix<T>::operator+=(Matrix<T> right) {
	for(int i = 0; i < this->height; i ++) {
		for(int j = 0; j < this->width; j ++) {
			(*this)[i][j] = (*this)[i][j] + right[i][j];
		}
	}
	return (*this);
}
template <class T>
Matrix<T> Matrix<T>::operator-=(Matrix<T> right) {
	for(int i = 0; i < this->height; i ++) {
		for(int j = 0; j < this->width; j ++) {
			(*this)[i][j] -= right[i][j];
		}
	}
	return *this;
}
template <class T>
Matrix<T> Matrix<T>::operator-(Matrix<T> right) {
	Matrix temp((*this));
	return (temp -= right);
}
template <class T>
Matrix<T> Matrix<T>::operator+(Matrix<T> right) {
	Matrix temp((*this));
	return (temp += right);
}
template <class T>
Matrix<T> Matrix<T>::operator=(Matrix<T> right) {
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
template <class T>
Matrix<T> Matrix<T>::operator=(Matrix* right) {
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
template <class T>
void Matrix<T>::randGen(int top, int bot) {
	srand (time(NULL)); // seed with time bc why not
	int range =  abs(top - bot)+1;
	for(int i = 0; i < this->height; i ++) {
		for(int j = 0; j < this->width; j ++) {
			(*this)[i][j] = (T)((rand() / (double)RAND_MAX) * range) + bot;
		}
	}
}
template <class T>
void Matrix<T>::setTo(T a) {
	srand (time(NULL));
	for(int i = 0; i < this->height; i ++) {
		for(int j = 0; j < this->width; j ++) {
			(*this)[i][j] = a;
		}
	}
}
template <class T>
Matrix<T> Matrix<T>::apply(T (*f)(T)) {
	for(int i = 0; i < this->height; i ++) {
		for(int j = 0; j < this->width; j ++) {
			(*this)[i][j] = (*f)((*this)[i][j]);
		}
	}
	return (*this);
}
template <class T>
Matrix<T>::~Matrix() {
	this->clear();
}
template class Matrix<double>;
template class Matrix<int>;