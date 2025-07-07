#include "LogScMatrix.hpp"
#define TS_ADD(C1,C2) template<typename T> constexpr void MatrixAddSp<T,C1,C2>::add(const Matrix<T, C1, C2>& lhs, const Matrix<T, C1, C2>& rhs, Matrix<T, C1, C2>& result) noexcept{
    
namespace LogSc {
    
    // 2x2 矩阵加法
    TS_ADD(2,2)
        result[0][0] = lhs[0][0]+rhs[0][0];
        result[0][1] = lhs[0][1]+rhs[0][1];

        result[1][0] = lhs[1][0]+rhs[1][0];
        result[1][1] = lhs[1][1]+rhs[1][1];
    }

    // 2x3 矩阵加法
    TS_ADD(2,3)
        result[0][0] = lhs[0][0] + rhs[0][0];
        result[0][1] = lhs[0][1] + rhs[0][1];
        result[0][2] = lhs[0][2] + rhs[0][2];

        result[1][0] = lhs[1][0] + rhs[1][0];
        result[1][1] = lhs[1][1] + rhs[1][1];
        result[1][2] = lhs[1][2] + rhs[1][2];
    }

    // 2x4 矩阵加法
    TS_ADD(2,4)
        result[0][0] = lhs[0][0] + rhs[0][0];
        result[0][1] = lhs[0][1] + rhs[0][1];
        result[0][2] = lhs[0][2] + rhs[0][2];
        result[0][3] = lhs[0][3] + rhs[0][3];

        result[1][0] = lhs[1][0] + rhs[1][0];
        result[1][1] = lhs[1][1] + rhs[1][1];
        result[1][2] = lhs[1][2] + rhs[1][2];
        result[1][3] = lhs[1][3] + rhs[1][3];
    }

    // 3x2 矩阵加法
    TS_ADD(3,2)
        result[0][0] = lhs[0][0] + rhs[0][0];
        result[0][1] = lhs[0][1] + rhs[0][1];

        result[1][0] = lhs[1][0] + rhs[1][0];
        result[1][1] = lhs[1][1] + rhs[1][1];

        result[2][0] = lhs[2][0] + rhs[2][0];
        result[2][1] = lhs[2][1] + rhs[2][1];
    }

    // 3x3 矩阵加法
    TS_ADD(3,3)
        result[0][0] = lhs[0][0] + rhs[0][0];
        result[0][1] = lhs[0][1] + rhs[0][1];
        result[0][2] = lhs[0][2] + rhs[0][2];

        result[1][0] = lhs[1][0] + rhs[1][0];
        result[1][1] = lhs[1][1] + rhs[1][1];
        result[1][2] = lhs[1][2] + rhs[1][2];

        result[2][0] = lhs[2][0] + rhs[2][0];
        result[2][1] = lhs[2][1] + rhs[2][1];
        result[2][2] = lhs[2][2] + rhs[2][2];
    }

    // 3x4 矩阵加法
    TS_ADD(3,4)
        result[0][0] = lhs[0][0] + rhs[0][0];
        result[0][1] = lhs[0][1] + rhs[0][1];
        result[0][2] = lhs[0][2] + rhs[0][2];
        result[0][3] = lhs[0][3] + rhs[0][3];

        result[1][0] = lhs[1][0] + rhs[1][0];
        result[1][1] = lhs[1][1] + rhs[1][1];
        result[1][2] = lhs[1][2] + rhs[1][2];
        result[1][3] = lhs[1][3] + rhs[1][3];

        result[2][0] = lhs[2][0] + rhs[2][0];
        result[2][1] = lhs[2][1] + rhs[2][1];
        result[2][2] = lhs[2][2] + rhs[2][2];
        result[2][3] = lhs[2][3] + rhs[2][3];
    }

    // 4x2 矩阵加法
    TS_ADD(4,2)
        result[0][0] = lhs[0][0] + rhs[0][0];
        result[0][1] = lhs[0][1] + rhs[0][1];

        result[1][0] = lhs[1][0] + rhs[1][0];
        result[1][1] = lhs[1][1] + rhs[1][1];

        result[2][0] = lhs[2][0] + rhs[2][0];
        result[2][1] = lhs[2][1] + rhs[2][1];

        result[3][0] = lhs[3][0] + rhs[3][0];
        result[3][1] = lhs[3][1] + rhs[3][1];
    }

    // 4x3 矩阵加法
    TS_ADD(4,3)
        result[0][0] = lhs[0][0] + rhs[0][0];
        result[0][1] = lhs[0][1] + rhs[0][1];
        result[0][2] = lhs[0][2] + rhs[0][2];

        result[1][0] = lhs[1][0] + rhs[1][0];
        result[1][1] = lhs[1][1] + rhs[1][1];
        result[1][2] = lhs[1][2] + rhs[1][2];

        result[2][0] = lhs[2][0] + rhs[2][0];
        result[2][1] = lhs[2][1] + rhs[2][1];
        result[2][2] = lhs[2][2] + rhs[2][2];

        result[3][0] = lhs[3][0] + rhs[3][0];
        result[3][1] = lhs[3][1] + rhs[3][1];
        result[3][2] = lhs[3][2] + rhs[3][2];
    }

    // 4x4 矩阵加法
    TS_ADD(4,4)
        result[0][0] = lhs[0][0] + rhs[0][0];
        result[0][1] = lhs[0][1] + rhs[0][1];
        result[0][2] = lhs[0][2] + rhs[0][2];
        result[0][3] = lhs[0][3] + rhs[0][3];

        result[1][0] = lhs[1][0] + rhs[1][0];
        result[1][1] = lhs[1][1] + rhs[1][1];
        result[1][2] = lhs[1][2] + rhs[1][2];
        result[1][3] = lhs[1][3] + rhs[1][3];

        result[2][0] = lhs[2][0] + rhs[2][0];
        result[2][1] = lhs[2][1] + rhs[2][1];
        result[2][2] = lhs[2][2] + rhs[2][2];
        result[2][3] = lhs[2][3] + rhs[2][3];

        result[3][0] = lhs[3][0] + rhs[3][0];
        result[3][1] = lhs[3][1] + rhs[3][1];
        result[3][2] = lhs[3][2] + rhs[3][2];
        result[3][3] = lhs[3][3] + rhs[3][3];
    }

};