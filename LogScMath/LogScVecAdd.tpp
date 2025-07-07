#include "LogScVec.hpp"
#define TS_ADD_VEC(C1) template< typename T> constexpr void VecMatrixAddSp<T, C1>::add(const Vec<T, C1>& lhs, const Vec<T, C1>& rhs, Vec<T, C1>& result) noexcept{\
printf("specialization vec %dx%d + %dx%d -> %dx%d\n",1,C1,1,C1,1,C1);

namespace LogSc{

    // 1×2 向量加法
    TS_ADD_VEC(2)
        result[0][0] = lhs[0][0] + rhs[0][0];
        result[0][1] = lhs[0][1] + rhs[0][1];
    }
    // 1×3 向量加法
    TS_ADD_VEC(3)
        result[0][0] = lhs[0][0] + rhs[0][0];
        result[0][1] = lhs[0][1] + rhs[0][1];
        result[0][2] = lhs[0][2] + rhs[0][2];
    }
    // 1×4 向量加法
    TS_ADD_VEC(4)
    
        result[0][0] = lhs[0][0] + rhs[0][0];
        result[0][1] = lhs[0][1] + rhs[0][1];
        result[0][2] = lhs[0][2] + rhs[0][2];
        result[0][3] = lhs[0][3] + rhs[0][3];
    }

};