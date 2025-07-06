#include<iostream>
#include "log159matrix.hpp"
#include <random>
#include <ctime>

template<size_t Rows, size_t Cols>
void randomInitialize(LogSc::MatrixInt<Rows, Cols>& mat, int minVal, int maxVal) {


    for (size_t i = 0; i < Rows; ++i) {
        for (size_t j = 0; j < Cols; ++j) {
            mat[i][j] =rand()%100+1;
        }
    }
}
int main() {

    LogSc::MatrixInt<4,4> m22;
    LogSc::MatrixInt<4,4> m23;
    LogSc::MatrixInt<4,4>result,result2;

    randomInitialize(m22, 1, 50);
    randomInitialize(m23, -10, 10);

    multiply(m22,m23,result);
    LogSc::MatrixSp<int,4,4,4>::multiply(m22,m23,result2);

    std::cout << "Result of A * B:\n";
    printMatrix(result);
    std::cout << "Result2 of A * B:\n";
    printMatrix(result2);

}
