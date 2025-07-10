#include "LogScVec.hpp"
#define TS_FUNDAMENTAL_SM_VEC(C,FUNCTION)\
template<typename T> constexpr void VecMatrixFundamentalSp<T, C>::FUNCTION(const T& scalar,const Vec<T, C>& vec,Vec<T, C>& result) noexcept{
#define TS_FUNDAMENTAL_MS_VEC(C,FUNCTION)\
template<typename T> constexpr void VecMatrixFundamentalSp<T, C>::FUNCTION(const Vec<T, C>& vec,const T& scalar,Vec<T, C>& result) noexcept{

namespace LogSc {
    // 1x2
    TS_FUNDAMENTAL_SM_VEC(2, scalar_add_matrix)
        result[0][0] = scalar + vec[0][0];
        result[0][1] = scalar + vec[0][1];
    }
    TS_FUNDAMENTAL_MS_VEC(2, matrix_add_scalar)
        result[0][0] = vec[0][0] + scalar;
        result[0][1] = vec[0][1] + scalar;
    }
    TS_FUNDAMENTAL_SM_VEC(2, scalar_sub_matrix)
        result[0][0] = scalar - vec[0][0];
        result[0][1] = scalar - vec[0][1];
    }
    TS_FUNDAMENTAL_MS_VEC(2, matrix_sub_scalar)
        result[0][0] = vec[0][0] - scalar;
        result[0][1] = vec[0][1] - scalar;
    }
    TS_FUNDAMENTAL_SM_VEC(2, scalar_mul_matrix)
        result[0][0] = scalar * vec[0][0];
        result[0][1] = scalar * vec[0][1];
    }
    TS_FUNDAMENTAL_MS_VEC(2, matrix_mul_scalar)
        result[0][0] = vec[0][0] * scalar;
        result[0][1] = vec[0][1] * scalar;
    }
    TS_FUNDAMENTAL_SM_VEC(2, scalar_div_matrix)
        result[0][0] = scalar / vec[0][0];
        result[0][1] = scalar / vec[0][1];
    }
    TS_FUNDAMENTAL_MS_VEC(2, matrix_div_scalar)
        result[0][0] = vec[0][0] / scalar;
        result[0][1] = vec[0][1] / scalar;
    }
    // 1x3
    TS_FUNDAMENTAL_SM_VEC(3, scalar_add_matrix)
        result[0][0] = scalar + vec[0][0];
        result[0][1] = scalar + vec[0][1];
        result[0][2] = scalar + vec[0][2];
    }
    TS_FUNDAMENTAL_MS_VEC(3, matrix_add_scalar)
        result[0][0] = vec[0][0] + scalar;
        result[0][1] = vec[0][1] + scalar;
        result[0][2] = vec[0][2] + scalar;
    }
    TS_FUNDAMENTAL_SM_VEC(3, scalar_sub_matrix)
        result[0][0] = scalar - vec[0][0];
        result[0][1] = scalar - vec[0][1];
        result[0][2] = scalar - vec[0][2];
    }
    TS_FUNDAMENTAL_MS_VEC(3, matrix_sub_scalar)
        result[0][0] = vec[0][0] - scalar;
        result[0][1] = vec[0][1] - scalar;
        result[0][2] = vec[0][2] - scalar;
    }
    TS_FUNDAMENTAL_SM_VEC(3, scalar_mul_matrix)
        result[0][0] = scalar * vec[0][0];
        result[0][1] = scalar * vec[0][1];
        result[0][2] = scalar * vec[0][2];
    }
    TS_FUNDAMENTAL_MS_VEC(3, matrix_mul_scalar)
        result[0][0] = vec[0][0] * scalar;
        result[0][1] = vec[0][1] * scalar;
        result[0][2] = vec[0][2] * scalar;
    }
    TS_FUNDAMENTAL_SM_VEC(3, scalar_div_matrix)
        result[0][0] = scalar / vec[0][0];
        result[0][1] = scalar / vec[0][1];
        result[0][2] = scalar / vec[0][2];
    }
    TS_FUNDAMENTAL_MS_VEC(3, matrix_div_scalar)
        result[0][0] = vec[0][0] / scalar;
        result[0][1] = vec[0][1] / scalar;
        result[0][2] = vec[0][2] / scalar;
    }
    // 1x4
    TS_FUNDAMENTAL_SM_VEC(4, scalar_add_matrix)
        result[0][0] = scalar + vec[0][0];
        result[0][1] = scalar + vec[0][1];
        result[0][2] = scalar + vec[0][2];
        result[0][3] = scalar + vec[0][3];
    }
    TS_FUNDAMENTAL_MS_VEC(4, matrix_add_scalar)
        result[0][0] = vec[0][0] + scalar;
        result[0][1] = vec[0][1] + scalar;
        result[0][2] = vec[0][2] + scalar;
        result[0][3] = vec[0][3] + scalar;
    }
    TS_FUNDAMENTAL_SM_VEC(4, scalar_sub_matrix)
        result[0][0] = scalar - vec[0][0];
        result[0][1] = scalar - vec[0][1];
        result[0][2] = scalar - vec[0][2];
        result[0][3] = scalar - vec[0][3];
    }
    TS_FUNDAMENTAL_MS_VEC(4, matrix_sub_scalar)
        result[0][0] = vec[0][0] - scalar;
        result[0][1] = vec[0][1] - scalar;
        result[0][2] = vec[0][2] - scalar;
        result[0][3] = vec[0][3] - scalar;
    }
    TS_FUNDAMENTAL_SM_VEC(4, scalar_mul_matrix)
        result[0][0] = scalar * vec[0][0];
        result[0][1] = scalar * vec[0][1];
        result[0][2] = scalar * vec[0][2];
        result[0][3] = scalar * vec[0][3];
    }
    TS_FUNDAMENTAL_MS_VEC(4, matrix_mul_scalar)
        result[0][0] = vec[0][0] * scalar;
        result[0][1] = vec[0][1] * scalar;
        result[0][2] = vec[0][2] * scalar;
        result[0][3] = vec[0][3] * scalar;
    }
    TS_FUNDAMENTAL_SM_VEC(4, scalar_div_matrix)
        result[0][0] = scalar / vec[0][0];
        result[0][1] = scalar / vec[0][1];
        result[0][2] = scalar / vec[0][2];
        result[0][3] = scalar / vec[0][3];
    }
    TS_FUNDAMENTAL_MS_VEC(4, matrix_div_scalar)
        result[0][0] = vec[0][0] / scalar;
        result[0][1] = vec[0][1] / scalar;
        result[0][2] = vec[0][2] / scalar;
        result[0][3] = vec[0][3] / scalar;
    }
};