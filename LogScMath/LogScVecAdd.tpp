#include "LogScVec.hpp"
#define TS_ADD_VEC(C) template< typename T> constexpr void VecMatrixAddSp<T, C>::add(const Vec<T, C>& lhs, const Vec<T, C>& rhs, Vec<T, C>& result) noexcept{

namespace LogSc{
    // 1×2 vector addition
    TS_ADD_VEC(2)
        result[0][0] = lhs[0][0] + rhs[0][0];
        result[0][1] = lhs[0][1] + rhs[0][1];
    }
    // 1×3 vector addition
    TS_ADD_VEC(3)
        result[0][0] = lhs[0][0] + rhs[0][0];
        result[0][1] = lhs[0][1] + rhs[0][1];
        result[0][2] = lhs[0][2] + rhs[0][2];
    }
    // 1×4 vector addition
    TS_ADD_VEC(4)
    
        result[0][0] = lhs[0][0] + rhs[0][0];
        result[0][1] = lhs[0][1] + rhs[0][1];
        result[0][2] = lhs[0][2] + rhs[0][2];
        result[0][3] = lhs[0][3] + rhs[0][3];
    }
};