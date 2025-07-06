#include<iostream>
#include "LogScMatrix.hpp"
#include <random>
#include <ctime>
// print matrix
template<typename T, size_t R, size_t C>
void printMatrix(const LogSc::Matrix<T, R, C>& mat) {
    for (size_t i = 0; i < R; ++i) {
        for (size_t j = 0; j < C; ++j) {
            std::cout << mat[i][j] << ' ';
        }
        std::cout << '\n';
    }
}
template<size_t Rows, size_t Cols>
void randomInitialize(LogSc::MatrixInt<Rows, Cols>& mat, int minVal, int maxVal) {
    for (size_t i = 0; i < Rows; ++i) {
        for (size_t j = 0; j < Cols; ++j) {
            mat[i][j] =rand()%100+1;
        }
    }
}
int main() {


    // {
    //     LogSc::MatrixInt<2,4> m24;
    //     LogSc::MatrixInt<4,2> m42;
    //     LogSc::MatrixInt<4,5> m45;
    //     LogSc::MatrixInt<2,2>result;
        
    //     randomInitialize(m24, 1, 50);
    //     randomInitialize(m42, -10, 10);
    //     randomInitialize(m45, 1, 10);

    //     std::cout << "Result of A multiply B:\n";
    //     LogSc::MatrixMultiplySp<int,2,4,2>::multiply(m24,m42,result);
    //     printMatrix(result);
    //     std::cout << "Result of A * B :\n";
    //     printMatrix(m24*m42);
    // }

    {
        LogSc::MatrixInt<2,2> m24_0,m24_1,result;
        randomInitialize(m24_0, 1, 50);
        randomInitialize(m24_1, -10, 10);
        LogSc::MatrixAdditionSp<int,2,2>::addition(m24_0,m24_1,result);

        printMatrix(m24_0);
        printMatrix(m24_1);

        printMatrix(result);
        printMatrix(m24_0+m24_1);
    }


}
