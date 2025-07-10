#include "LogScMatrix.hpp"
#define TS_COMPARE(C1,C2) template<typename T> constexpr bool MatrixCompareSp<T, C1, C2>::compare(const Matrix<T, C1, C2>& lhs, const Matrix<T, C1, C2>& rhs) noexcept{
namespace LogSc {
    TS_COMPARE(2, 2)
        return
            lhs[0][0] == rhs[0][0] && lhs[0][1] == rhs[0][1] &&
            lhs[1][0] == rhs[1][0] && lhs[1][1] == rhs[1][1];
    }
    TS_COMPARE(2, 3) 
        return
            lhs[0][0] == rhs[0][0] && lhs[0][1] == rhs[0][1] && lhs[0][2] == rhs[0][2] &&
            lhs[1][0] == rhs[1][0] && lhs[1][1] == rhs[1][1] && lhs[1][2] == rhs[1][2];
    }
    TS_COMPARE(2, 4) 
        return
            lhs[0][0] == rhs[0][0] && lhs[0][1] == rhs[0][1] && lhs[0][2] == rhs[0][2] && lhs[0][3] == rhs[0][3] &&
            lhs[1][0] == rhs[1][0] && lhs[1][1] == rhs[1][1] && lhs[1][2] == rhs[1][2] && lhs[1][3] == rhs[1][3];
    }
    TS_COMPARE(3, 2) 
        return
            lhs[0][0] == rhs[0][0] && lhs[0][1] == rhs[0][1] &&
            lhs[1][0] == rhs[1][0] && lhs[1][1] == rhs[1][1] &&
            lhs[2][0] == rhs[2][0] && lhs[2][1] == rhs[2][1];
    }
    TS_COMPARE(3, 3) 
        return
            lhs[0][0] == rhs[0][0] && lhs[0][1] == rhs[0][1] && lhs[0][2] == rhs[0][2] &&
            lhs[1][0] == rhs[1][0] && lhs[1][1] == rhs[1][1] && lhs[1][2] == rhs[1][2] &&
            lhs[2][0] == rhs[2][0] && lhs[2][1] == rhs[2][1] && lhs[2][2] == rhs[2][2];
    }
    TS_COMPARE(3, 4) 
        return
            lhs[0][0] == rhs[0][0] && lhs[0][1] == rhs[0][1] && lhs[0][2] == rhs[0][2] && lhs[0][3] == rhs[0][3] &&
            lhs[1][0] == rhs[1][0] && lhs[1][1] == rhs[1][1] && lhs[1][2] == rhs[1][2] && lhs[1][3] == rhs[1][3] &&
            lhs[2][0] == rhs[2][0] && lhs[2][1] == rhs[2][1] && lhs[2][2] == rhs[2][2] && lhs[2][3] == rhs[2][3];
    }
    TS_COMPARE(4, 2) 
        return
            lhs[0][0] == rhs[0][0] && lhs[0][1] == rhs[0][1] &&
            lhs[1][0] == rhs[1][0] && lhs[1][1] == rhs[1][1] &&
            lhs[2][0] == rhs[2][0] && lhs[2][1] == rhs[2][1] &&
            lhs[3][0] == rhs[3][0] && lhs[3][1] == rhs[3][1];
    }
    TS_COMPARE(4, 3) 
        return
            lhs[0][0] == rhs[0][0] && lhs[0][1] == rhs[0][1] && lhs[0][2] == rhs[0][2] &&
            lhs[1][0] == rhs[1][0] && lhs[1][1] == rhs[1][1] && lhs[1][2] == rhs[1][2] &&
            lhs[2][0] == rhs[2][0] && lhs[2][1] == rhs[2][1] && lhs[2][2] == rhs[2][2] &&
            lhs[3][0] == rhs[3][0] && lhs[3][1] == rhs[3][1] && lhs[3][2] == rhs[3][2];
    }
    TS_COMPARE(4, 4)
        return
            lhs[0][0] == rhs[0][0] && lhs[0][1] == rhs[0][1] && lhs[0][2] == rhs[0][2] && lhs[0][3] == rhs[0][3] &&
            lhs[1][0] == rhs[1][0] && lhs[1][1] == rhs[1][1] && lhs[1][2] == rhs[1][2] && lhs[1][3] == rhs[1][3] &&
            lhs[2][0] == rhs[2][0] && lhs[2][1] == rhs[2][1] && lhs[2][2] == rhs[2][2] && lhs[2][3] == rhs[2][3] &&
            lhs[3][0] == rhs[3][0] && lhs[3][1] == rhs[3][1] && lhs[3][2] == rhs[3][2] && lhs[3][3] == rhs[3][3];
    }
};