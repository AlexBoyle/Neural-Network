#ifndef UTILITY
#define UTILITY

#include "Matrix.h"
#include <iostream>
using namespace std;

class Utility {
    public:
        Utility();
        static double normalizeImageToOne(double x);
        static double normalizeImageToTernary(double x);
        static void printImageMatrix(Matrix<double> img, int width, int height) {
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
        static void printImageMatrix1(Matrix<double> img, int width, int height) {
            for(int i = 0; i < width * height; i ++) {
                if(i%width == 0) { cout << "\n"; }
                if(img[i][0] == -1) { cout << " ";}
                else if(img[i][0] == 0) { cout << "░";}
                //else if(img[i][0] == ) { cout << "▒";}
                //else if(img[i][0] < 225.0) { cout << "▓";}
                else  { cout << "█";}
            }
            cout << "\n";
        }
        template <class T, class U>
        static Matrix<U> matrixConverter(Matrix<T> mtx) {
             Matrix<U> output = Matrix<U>(mtx.height, mtx.width);
             for(int i = 0; i < output.height; i ++) {
                for(int j = 0; j < output.width; j ++) {
                    output[i][j] = mtx[i][j];
                }
            }
            return output;
        }

};
#endif