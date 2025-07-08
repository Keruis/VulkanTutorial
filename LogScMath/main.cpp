#include<iostream>
#include "LogScMatrix.hpp"
#include "LogScVec.hpp"
#include <random>
#include <ctime>

// print matrix
template<typename T, size_t R, size_t C>
void printMatrix(const LogSc::Matrix<T, R, C>& mat) {
    for (size_t i = 0; i < R; ++i) {
        for (size_t j = 0; j < C; ++j) {
            std::cout << mat[i][j] << ',';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}
template<size_t Rows, size_t Cols>
void randomInitialize(LogSc::MatrixInt<Rows, Cols>& mat, int minVal, int maxVal) {
    for (size_t i = 0; i < Rows; ++i) {
        for (size_t j = 0; j < Cols; ++j) {
            mat[i][j] =rand()%100+1;
        }
    }
}
template<size_t Rows, size_t Cols>
void randomInitialize(LogSc::MatrixDouble<Rows, Cols>& mat, int minVal, int maxVal) {
    for (size_t i = 0; i < Rows; ++i) {
        for (size_t j = 0; j < Cols; ++j) {
            mat[i][j] =rand()%100+1;
        }
    }
}
int main() {

// Matrix And Matrix Compare
// /*
    LogSc::MatrixDouble<2,2> m22,result;
    randomInitialize(m22, 1, 50);
    randomInitialize(result, 1, 50);
    if(m22!=result)
        printf("!=\n");
    else
        printf("==\n");
// */
// Matrix And Value +/-* AND Value And Matrix +/-*
/*
    {
        LogSc::MatrixDouble<2,2> m42,result;
        randomInitialize(m42, 1, 50);
        printMatrix(m42);
        LogSc::MatrixFundamentalSp<double,2,2>::scalar_add_matrix(3,m42,result);
        printMatrix(result);
        LogSc::MatrixFundamentalSp<double,2,2>::scalar_mul_matrix(2,m42,result);
        printMatrix(result);
        printMatrix(1000.0*m42);
        printMatrix(1000.0+m42);
        printMatrix(1000.0-m42);
        printMatrix(1000.0/m42);
        printMatrix(m42*1000.0);
        printMatrix(m42+1000.0);
        printMatrix(m42-1000.0);
        printMatrix(m42/1000.0);

    }
*/
// A * B Matrix Matrix
/*
    {
        LogSc::MatrixInt<2,4> m24;
        LogSc::MatrixInt<4,2> m42;
        LogSc::MatrixInt<4,5> m45;
        LogSc::MatrixInt<2,2>result;
        
        randomInitialize(m24, 1, 50);
        randomInitialize(m42, -10, 10);
        randomInitialize(m45, 1, 10);

        std::cout << "Result of A multiply B:\n";
        LogSc::MatrixMultiplySp<int,2,4,2>::multiply(m24,m42,result);
        printMatrix(result);
        std::cout << "Result of A * B :\n";
        printMatrix(m24*m42);
    }
*/
// A + B Matrix Matrix
/*
    {
        LogSc::MatrixInt<2,3> m24_0,m24_1,result;
        randomInitialize(m24_0, 1, 50);
        randomInitialize(m24_1, -10, 10);
        LogSc::MatrixAddSp<int,2,3>::add(m24_0,m24_1,result);

        printMatrix(m24_0);
        printMatrix(m24_1);

        printMatrix(result);
        printMatrix(m24_0+m24_1);
    }
*/
// A / B Matrix Matrix
/*
    {
        LogSc::MatrixDouble<3,3>m24;
        LogSc::MatrixDouble<3,3>m44;


        randomInitialize(m24, 1, 50);
        randomInitialize(m44, -10, 10);

        printMatrix(m24);
        printf("\n");
        printMatrix(m44);
        printf("\n");
        printMatrix(m24/m44);
        
    }
*/
// A - B Matrix Matrix
/*
    {
        LogSc::MatrixInt<2,3> m24_0,m24_1,result;
        randomInitialize(m24_0, 1, 50);
        randomInitialize(m24_1, -10, 10);
        LogSc::MatrixSubtractSp<int,2,3>::subtract(m24_0,m24_1,result);

        printMatrix(m24_0);
        printMatrix(m24_1);

        printMatrix(result);
        printMatrix(m24_0-m24_1);
    }
*/
// A * B Vec Matrix
/*
    {
        LogSc::VecInt<4> vc, result;
        LogSc::MatrixInt<4,4> mc;
        randomInitialize(vc,1,50);
        randomInitialize(mc,1,50);
        printMatrix(vc);
        printMatrix(mc);
        LogSc::MatrixMultiplySp<int,1,4,4>::multiply(vc,mc,result);
        printMatrix(result);
        LogSc::VecMatrixMultiplySp<int,4,4>::multiply(vc,mc,result);
        printMatrix(result);
    }
*/
// A + B Vec Vec
/*
    {
        LogSc::Vec<int,4> vc1, vc2,result;
        randomInitialize(vc1,1,50);
        randomInitialize(vc2,1,50);
        printMatrix(vc1);
        printMatrix(vc2);
        LogSc::VecMatrixAddSp<int,4>::add(vc1,vc2,result);
        printMatrix(result);
        printMatrix(vc1+vc2);
    }
*/
// A - B Vec Vec
/*
    {
        LogSc::Vec<int,4> vc1, vc2,result;
        randomInitialize(vc1,1,50);
        randomInitialize(vc2,1,50);
        printMatrix(vc1);
        printMatrix(vc2);
        LogSc::VecMatrixSubtractSp<int,4>::subtract(vc1,vc2,result);
        printMatrix(result);
        _scalar_add_matrix(100,vc1,result);
        printMatrix(result);
    }
*/

}
