#include "LogScMatrix.hpp"

#define TS_ADDITION(C1,C2) template<typename T> void MatrixAdditionSp<T,C1,C2>::addition(const Matrix<T, C1, C2>& lhs, const Matrix<T, C1, C2>& rhs, Matrix<T, C1, C2>& result){\
printf("specialization %dx%d + %dx%d -> %dx%d\n",C1,C2,C1,C2,C1,C2);
    
namespace LogSc  {
    // 1. 2×2 + 2×2 -> 2×2
    TS_ADDITION(2,2)
        result[0][0] = lhs[0][0]+rhs[0][0];
        result[0][1] = lhs[0][1]+rhs[0][1];
        result[1][0] = lhs[1][0]+rhs[1][0];
        result[1][1] = lhs[1][1]+rhs[1][1];
    }
};