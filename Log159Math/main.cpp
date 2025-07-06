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
    LogSc::MatrixInt<2,4> m24;
    LogSc::MatrixInt<4,2> m42;
    LogSc::MatrixInt<4,5> m45;
    LogSc::MatrixInt<2,2>result;
    
    randomInitialize(m24, 1, 50);
    randomInitialize(m42, -10, 10);
    randomInitialize(m45, 1, 10);

    std::cout << "Result of A multiply B:\n";
    LogSc::MatrixSp<int,2,4,2>::multiply(m24,m42,result);
    printMatrix(result);
    std::cout << "Result of A * B :\n";
    printMatrix(m24*m42);



}
