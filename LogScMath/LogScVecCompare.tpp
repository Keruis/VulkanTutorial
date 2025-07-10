#include "LogScVec.hpp"
#define TS_COMPARE_VEC(C) template<typename T> constexpr bool VecMatrixCompareSp<T, C>::compare(const Vec<T, C>& lhs, const Vec<T, C>& rhs) noexcept{

namespace LogSc{
    TS_COMPARE_VEC(2)
        return 
            lhs[0][0] == rhs[0][0] && lhs[0][1] == rhs[0][1];
    }
    TS_COMPARE_VEC(3)
        return
            lhs[0][0] == rhs[0][0] && lhs[0][1] == rhs[0][1] && lhs[0][2] == rhs[0][2];
    }
    TS_COMPARE_VEC(4)
        return
            lhs[0][0] == rhs[0][0] && lhs[0][1] == rhs[0][1] && lhs[0][2] == rhs[0][2] && lhs[0][3] == rhs[0][3];
    }
};