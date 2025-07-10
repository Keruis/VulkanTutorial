#include "LogScVec.hpp"
#define TS_MULTIPLY_VEC(C1,C2) template< typename T> constexpr void  VecMatrixMultiplySp<T,C1,C2>::multiply(const Vec<T, C1>& lhs, const Matrix<T, C1, C2>& rhs, Vec<T,C2>& result) noexcept{

namespace LogSc{
    // 1. 1×2 × 2×2 -> 1×2
   TS_MULTIPLY_VEC(2,2)
        result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0];
        result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1];
    }
    // 2. 1×2 × 2×3 -> 1×3
    TS_MULTIPLY_VEC(2,3)
        result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0];
        result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1];
        result[0][2] = lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2];
    }
    // 3. 1×2 × 2×4 -> 1×4
    TS_MULTIPLY_VEC(2,4)
        result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0];
        result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1];
        result[0][2] = lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2];
        result[0][3] = lhs[0][0] * rhs[0][3] + lhs[0][1] * rhs[1][3];
    }
    // 4. 1×3 × 3×2 -> 1×2
    TS_MULTIPLY_VEC(3,2)
        result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0];
        result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1];
    }
    // 5. 1×3 × 3×3 -> 1×3
    TS_MULTIPLY_VEC(3,3)
        result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0];
        result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1];
        result[0][2] = lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2] + lhs[0][2] * rhs[2][2];
    }
    // 6. 1×3 × 3×4 -> 1×4
    TS_MULTIPLY_VEC(3,4)
        result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0];
        result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1];
        result[0][2] = lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2] + lhs[0][2] * rhs[2][2];
        result[0][3] = lhs[0][0] * rhs[0][3] + lhs[0][1] * rhs[1][3] + lhs[0][2] * rhs[2][3];
    }
    // 7. 1×4 × 4×2 -> 1×2
    TS_MULTIPLY_VEC(4,2)
        result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0] + lhs[0][3] * rhs[3][0];
        result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1] + lhs[0][3] * rhs[3][1];
    }
    // 8. 1×4 × 4×3 -> 1×3
    TS_MULTIPLY_VEC(4,3)
        result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0] + lhs[0][3] * rhs[3][0];
        result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1] + lhs[0][3] * rhs[3][1];
        result[0][2] = lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2] + lhs[0][2] * rhs[2][2] + lhs[0][3] * rhs[3][2];
    }
    // 9. 1×4 × 4×4 -> 1×4
    TS_MULTIPLY_VEC(4,4)
        result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0] + lhs[0][3] * rhs[3][0];
        result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1] + lhs[0][3] * rhs[3][1];
        result[0][2] = lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2] + lhs[0][2] * rhs[2][2] + lhs[0][3] * rhs[3][2];
        result[0][3] = lhs[0][0] * rhs[0][3] + lhs[0][1] * rhs[1][3] + lhs[0][2] * rhs[2][3] + lhs[0][3] * rhs[3][3];
    }
};