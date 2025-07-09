#include "LogScMatrix.hpp"
#define TS_FUNDAMENTAL_SM(R,C,FUNCTION)\
template<typename T> constexpr void MatrixFundamentalSp<T, R, C>::FUNCTION(const T& scalar,const Matrix<T, R, C>& mat,Matrix<T, R, C>& result) noexcept{
#define TS_FUNDAMENTAL_MS(R,C,FUNCTION)\
template<typename T> constexpr void MatrixFundamentalSp<T, R, C>::FUNCTION(const Matrix<T, R, C>& mat,const T& scalar,Matrix<T, R, C>& result) noexcept{

namespace LogSc {

    TS_FUNDAMENTAL_SM(2, 2, scalar_add_matrix)
        result[0][0] = scalar + mat[0][0];
        result[0][1] = scalar + mat[0][1];
        result[1][0] = scalar + mat[1][0];
        result[1][1] = scalar + mat[1][1];
    }
    TS_FUNDAMENTAL_MS(2, 2, matrix_add_scalar)
        result[0][0] = mat[0][0] + scalar;
        result[0][1] = mat[0][1] + scalar;
        result[1][0] = mat[1][0] + scalar;
        result[1][1] = mat[1][1] + scalar;
    }
    TS_FUNDAMENTAL_SM(2, 2, scalar_sub_matrix)
        result[0][0] = scalar - mat[0][0];
        result[0][1] = scalar - mat[0][1];
        result[1][0] = scalar - mat[1][0];
        result[1][1] = scalar - mat[1][1];
    }
    TS_FUNDAMENTAL_MS(2, 2, matrix_sub_scalar)
        result[0][0] = mat[0][0] - scalar;
        result[0][1] = mat[0][1] - scalar;
        result[1][0] = mat[1][0] - scalar;
        result[1][1] = mat[1][1] - scalar;
    }
    TS_FUNDAMENTAL_SM(2, 2, scalar_mul_matrix)
        result[0][0] = scalar * mat[0][0];
        result[0][1] = scalar * mat[0][1];
        result[1][0] = scalar * mat[1][0];
        result[1][1] = scalar * mat[1][1];
    }
    TS_FUNDAMENTAL_MS(2, 2, matrix_mul_scalar)
        result[0][0] = mat[0][0] * scalar;
        result[0][1] = mat[0][1] * scalar;
        result[1][0] = mat[1][0] * scalar;
        result[1][1] = mat[1][1] * scalar;
    }
    TS_FUNDAMENTAL_SM(2, 2, scalar_div_matrix)
        result[0][0] = scalar / mat[0][0];
        result[0][1] = scalar / mat[0][1];
        result[1][0] = scalar / mat[1][0];
        result[1][1] = scalar / mat[1][1];
    }
    TS_FUNDAMENTAL_MS(2, 2, matrix_div_scalar)
        result[0][0] = mat[0][0] / scalar;
        result[0][1] = mat[0][1] / scalar;
        result[1][0] = mat[1][0] / scalar;
        result[1][1] = mat[1][1] / scalar;
    }

    // 2x3
    TS_FUNDAMENTAL_SM(2, 3, scalar_add_matrix)
        result[0][0] = scalar + mat[0][0];
        result[0][1] = scalar + mat[0][1];
        result[0][2] = scalar + mat[0][2];
        result[1][0] = scalar + mat[1][0];
        result[1][1] = scalar + mat[1][1];
        result[1][2] = scalar + mat[1][2];
    }

    TS_FUNDAMENTAL_MS(2, 3, matrix_add_scalar)
        result[0][0] = mat[0][0] + scalar;
        result[0][1] = mat[0][1] + scalar;
        result[0][2] = mat[0][2] + scalar;
        result[1][0] = mat[1][0] + scalar;
        result[1][1] = mat[1][1] + scalar;
        result[1][2] = mat[1][2] + scalar;
    }

    TS_FUNDAMENTAL_SM(2, 3, scalar_sub_matrix)
        result[0][0] = scalar - mat[0][0];
        result[0][1] = scalar - mat[0][1];
        result[0][2] = scalar - mat[0][2];
        result[1][0] = scalar - mat[1][0];
        result[1][1] = scalar - mat[1][1];
        result[1][2] = scalar - mat[1][2];
    }

    TS_FUNDAMENTAL_MS(2, 3, matrix_sub_scalar)
        result[0][0] = mat[0][0] - scalar;
        result[0][1] = mat[0][1] - scalar;
        result[0][2] = mat[0][2] - scalar;
        result[1][0] = mat[1][0] - scalar;
        result[1][1] = mat[1][1] - scalar;
        result[1][2] = mat[1][2] - scalar;
    }

    TS_FUNDAMENTAL_SM(2, 3, scalar_mul_matrix)
        result[0][0] = scalar * mat[0][0];
        result[0][1] = scalar * mat[0][1];
        result[0][2] = scalar * mat[0][2];
        result[1][0] = scalar * mat[1][0];
        result[1][1] = scalar * mat[1][1];
        result[1][2] = scalar * mat[1][2];
    }

    TS_FUNDAMENTAL_MS(2, 3, matrix_mul_scalar)
        result[0][0] = mat[0][0] * scalar;
        result[0][1] = mat[0][1] * scalar;
        result[0][2] = mat[0][2] * scalar;
        result[1][0] = mat[1][0] * scalar;
        result[1][1] = mat[1][1] * scalar;
        result[1][2] = mat[1][2] * scalar;
    }

    TS_FUNDAMENTAL_SM(2, 3, scalar_div_matrix)
        result[0][0] = scalar / mat[0][0];
        result[0][1] = scalar / mat[0][1];
        result[0][2] = scalar / mat[0][2];
        result[1][0] = scalar / mat[1][0];
        result[1][1] = scalar / mat[1][1];
        result[1][2] = scalar / mat[1][2];
    }

    TS_FUNDAMENTAL_MS(2, 3, matrix_div_scalar)
        result[0][0] = mat[0][0] / scalar;
        result[0][1] = mat[0][1] / scalar;
        result[0][2] = mat[0][2] / scalar;
        result[1][0] = mat[1][0] / scalar;
        result[1][1] = mat[1][1] / scalar;
        result[1][2] = mat[1][2] / scalar;
    }

    // 2x4
    TS_FUNDAMENTAL_SM(2, 4, scalar_add_matrix)
        result[0][0] = scalar + mat[0][0];
        result[0][1] = scalar + mat[0][1];
        result[0][2] = scalar + mat[0][2];
        result[0][3] = scalar + mat[0][3];
        result[1][0] = scalar + mat[1][0];
        result[1][1] = scalar + mat[1][1];
        result[1][2] = scalar + mat[1][2];
        result[1][3] = scalar + mat[1][3];
    }

    TS_FUNDAMENTAL_MS(2, 4, matrix_add_scalar)
        result[0][0] = mat[0][0] + scalar;
        result[0][1] = mat[0][1] + scalar;
        result[0][2] = mat[0][2] + scalar;
        result[0][3] = mat[0][3] + scalar;
        result[1][0] = mat[1][0] + scalar;
        result[1][1] = mat[1][1] + scalar;
        result[1][2] = mat[1][2] + scalar;
        result[1][3] = mat[1][3] + scalar;
    }

    TS_FUNDAMENTAL_SM(2, 4, scalar_sub_matrix)
        result[0][0] = scalar - mat[0][0];
        result[0][1] = scalar - mat[0][1];
        result[0][2] = scalar - mat[0][2];
        result[0][3] = scalar - mat[0][3];
        result[1][0] = scalar - mat[1][0];
        result[1][1] = scalar - mat[1][1];
        result[1][2] = scalar - mat[1][2];
        result[1][3] = scalar - mat[1][3];
    }

    TS_FUNDAMENTAL_MS(2, 4, matrix_sub_scalar)
        result[0][0] = mat[0][0] - scalar;
        result[0][1] = mat[0][1] - scalar;
        result[0][2] = mat[0][2] - scalar;
        result[0][3] = mat[0][3] - scalar;
        result[1][0] = mat[1][0] - scalar;
        result[1][1] = mat[1][1] - scalar;
        result[1][2] = mat[1][2] - scalar;
        result[1][3] = mat[1][3] - scalar;
    }

    TS_FUNDAMENTAL_SM(2, 4, scalar_mul_matrix)
        result[0][0] = scalar * mat[0][0];
        result[0][1] = scalar * mat[0][1];
        result[0][2] = scalar * mat[0][2];
        result[0][3] = scalar * mat[0][3];
        result[1][0] = scalar * mat[1][0];
        result[1][1] = scalar * mat[1][1];
        result[1][2] = scalar * mat[1][2];
        result[1][3] = scalar * mat[1][3];
    }

    TS_FUNDAMENTAL_MS(2, 4, matrix_mul_scalar)
        result[0][0] = mat[0][0] * scalar;
        result[0][1] = mat[0][1] * scalar;
        result[0][2] = mat[0][2] * scalar;
        result[0][3] = mat[0][3] * scalar;
        result[1][0] = mat[1][0] * scalar;
        result[1][1] = mat[1][1] * scalar;
        result[1][2] = mat[1][2] * scalar;
        result[1][3] = mat[1][3] * scalar;
    }

    TS_FUNDAMENTAL_SM(2, 4, scalar_div_matrix)
        result[0][0] = scalar / mat[0][0];
        result[0][1] = scalar / mat[0][1];
        result[0][2] = scalar / mat[0][2];
        result[0][3] = scalar / mat[0][3];
        result[1][0] = scalar / mat[1][0];
        result[1][1] = scalar / mat[1][1];
        result[1][2] = scalar / mat[1][2];
        result[1][3] = scalar / mat[1][3];
    }

    TS_FUNDAMENTAL_MS(2, 4, matrix_div_scalar)
        result[0][0] = mat[0][0] / scalar;
        result[0][1] = mat[0][1] / scalar;
        result[0][2] = mat[0][2] / scalar;
        result[0][3] = mat[0][3] / scalar;
        result[1][0] = mat[1][0] / scalar;
        result[1][1] = mat[1][1] / scalar;
        result[1][2] = mat[1][2] / scalar;
        result[1][3] = mat[1][3] / scalar;
    }

    // 3x2
    TS_FUNDAMENTAL_SM(3, 2, scalar_add_matrix)
        result[0][0] = scalar + mat[0][0];
        result[0][1] = scalar + mat[0][1];
        result[1][0] = scalar + mat[1][0];
        result[1][1] = scalar + mat[1][1];
        result[2][0] = scalar + mat[2][0];
        result[2][1] = scalar + mat[2][1];
    }

    TS_FUNDAMENTAL_MS(3, 2, matrix_add_scalar)
        result[0][0] = mat[0][0] + scalar;
        result[0][1] = mat[0][1] + scalar;
        result[1][0] = mat[1][0] + scalar;
        result[1][1] = mat[1][1] + scalar;
        result[2][0] = mat[2][0] + scalar;
        result[2][1] = mat[2][1] + scalar;
    }

    TS_FUNDAMENTAL_SM(3, 2, scalar_sub_matrix)
        result[0][0] = scalar - mat[0][0];
        result[0][1] = scalar - mat[0][1];
        result[1][0] = scalar - mat[1][0];
        result[1][1] = scalar - mat[1][1];
        result[2][0] = scalar - mat[2][0];
        result[2][1] = scalar - mat[2][1];
    }

    TS_FUNDAMENTAL_MS(3, 2, matrix_sub_scalar)
        result[0][0] = mat[0][0] - scalar;
        result[0][1] = mat[0][1] - scalar;
        result[1][0] = mat[1][0] - scalar;
        result[1][1] = mat[1][1] - scalar;
        result[2][0] = mat[2][0] - scalar;
        result[2][1] = mat[2][1] - scalar;
    }

    TS_FUNDAMENTAL_SM(3, 2, scalar_mul_matrix)
        result[0][0] = scalar * mat[0][0];
        result[0][1] = scalar * mat[0][1];
        result[1][0] = scalar * mat[1][0];
        result[1][1] = scalar * mat[1][1];
        result[2][0] = scalar * mat[2][0];
        result[2][1] = scalar * mat[2][1];
    }

    TS_FUNDAMENTAL_MS(3, 2, matrix_mul_scalar)
        result[0][0] = mat[0][0] * scalar;
        result[0][1] = mat[0][1] * scalar;
        result[1][0] = mat[1][0] * scalar;
        result[1][1] = mat[1][1] * scalar;
        result[2][0] = mat[2][0] * scalar;
        result[2][1] = mat[2][1] * scalar;
    }

    TS_FUNDAMENTAL_SM(3, 2, scalar_div_matrix)
        result[0][0] = scalar / mat[0][0];
        result[0][1] = scalar / mat[0][1];
        result[1][0] = scalar / mat[1][0];
        result[1][1] = scalar / mat[1][1];
        result[2][0] = scalar / mat[2][0];
        result[2][1] = scalar / mat[2][1];
    }

    TS_FUNDAMENTAL_MS(3, 2, matrix_div_scalar)
        result[0][0] = mat[0][0] / scalar;
        result[0][1] = mat[0][1] / scalar;
        result[1][0] = mat[1][0] / scalar;
        result[1][1] = mat[1][1] / scalar;
        result[2][0] = mat[2][0] / scalar;
        result[2][1] = mat[2][1] / scalar;
    }

    //3x3
    TS_FUNDAMENTAL_SM(3, 3, scalar_add_matrix)
        result[0][0] = scalar + mat[0][0];
        result[0][1] = scalar + mat[0][1];
        result[0][2] = scalar + mat[0][2];
        result[1][0] = scalar + mat[1][0];
        result[1][1] = scalar + mat[1][1];
        result[1][2] = scalar + mat[1][2];
        result[2][0] = scalar + mat[2][0];
        result[2][1] = scalar + mat[2][1];
        result[2][2] = scalar + mat[2][2];
    }

    TS_FUNDAMENTAL_MS(3, 3, matrix_add_scalar)
        result[0][0] = mat[0][0] + scalar;
        result[0][1] = mat[0][1] + scalar;
        result[0][2] = mat[0][2] + scalar;
        result[1][0] = mat[1][0] + scalar;
        result[1][1] = mat[1][1] + scalar;
        result[1][2] = mat[1][2] + scalar;
        result[2][0] = mat[2][0] + scalar;
        result[2][1] = mat[2][1] + scalar;
        result[2][2] = mat[2][2] + scalar;
    }

    TS_FUNDAMENTAL_SM(3, 3, scalar_sub_matrix)
        result[0][0] = scalar - mat[0][0];
        result[0][1] = scalar - mat[0][1];
        result[0][2] = scalar - mat[0][2];
        result[1][0] = scalar - mat[1][0];
        result[1][1] = scalar - mat[1][1];
        result[1][2] = scalar - mat[1][2];
        result[2][0] = scalar - mat[2][0];
        result[2][1] = scalar - mat[2][1];
        result[2][2] = scalar - mat[2][2];
    }

    TS_FUNDAMENTAL_MS(3, 3, matrix_sub_scalar)
        result[0][0] = mat[0][0] - scalar;
        result[0][1] = mat[0][1] - scalar;
        result[0][2] = mat[0][2] - scalar;
        result[1][0] = mat[1][0] - scalar;
        result[1][1] = mat[1][1] - scalar;
        result[1][2] = mat[1][2] - scalar;
        result[2][0] = mat[2][0] - scalar;
        result[2][1] = mat[2][1] - scalar;
        result[2][2] = mat[2][2] - scalar;
    }

    TS_FUNDAMENTAL_SM(3, 3, scalar_mul_matrix)
        result[0][0] = scalar * mat[0][0];
        result[0][1] = scalar * mat[0][1];
        result[0][2] = scalar * mat[0][2];
        result[1][0] = scalar * mat[1][0];
        result[1][1] = scalar * mat[1][1];
        result[1][2] = scalar * mat[1][2];
        result[2][0] = scalar * mat[2][0];
        result[2][1] = scalar * mat[2][1];
        result[2][2] = scalar * mat[2][2];
    }

    TS_FUNDAMENTAL_MS(3, 3, matrix_mul_scalar)
        result[0][0] = mat[0][0] * scalar;
        result[0][1] = mat[0][1] * scalar;
        result[0][2] = mat[0][2] * scalar;
        result[1][0] = mat[1][0] * scalar;
        result[1][1] = mat[1][1] * scalar;
        result[1][2] = mat[1][2] * scalar;
        result[2][0] = mat[2][0] * scalar;
        result[2][1] = mat[2][1] * scalar;
        result[2][2] = mat[2][2] * scalar;
    }

    TS_FUNDAMENTAL_SM(3, 3, scalar_div_matrix)
        result[0][0] = scalar / mat[0][0];
        result[0][1] = scalar / mat[0][1];
        result[0][2] = scalar / mat[0][2];
        result[1][0] = scalar / mat[1][0];
        result[1][1] = scalar / mat[1][1];
        result[1][2] = scalar / mat[1][2];
        result[2][0] = scalar / mat[2][0];
        result[2][1] = scalar / mat[2][1];
        result[2][2] = scalar / mat[2][2];
    }

    TS_FUNDAMENTAL_MS(3, 3, matrix_div_scalar)
        result[0][0] = mat[0][0] / scalar;
        result[0][1] = mat[0][1] / scalar;
        result[0][2] = mat[0][2] / scalar;
        result[1][0] = mat[1][0] / scalar;
        result[1][1] = mat[1][1] / scalar;
        result[1][2] = mat[1][2] / scalar;
        result[2][0] = mat[2][0] / scalar;
        result[2][1] = mat[2][1] / scalar;
        result[2][2] = mat[2][2] / scalar;
    }

    //3x4
    TS_FUNDAMENTAL_SM(3, 4, scalar_add_matrix)
        result[0][0] = scalar + mat[0][0];
        result[0][1] = scalar + mat[0][1];
        result[0][2] = scalar + mat[0][2];
        result[0][3] = scalar + mat[0][3];
        result[1][0] = scalar + mat[1][0];
        result[1][1] = scalar + mat[1][1];
        result[1][2] = scalar + mat[1][2];
        result[1][3] = scalar + mat[1][3];
        result[2][0] = scalar + mat[2][0];
        result[2][1] = scalar + mat[2][1];
        result[2][2] = scalar + mat[2][2];
        result[2][3] = scalar + mat[2][3];
    }

    TS_FUNDAMENTAL_MS(3, 4, matrix_add_scalar)
        result[0][0] = mat[0][0] + scalar;
        result[0][1] = mat[0][1] + scalar;
        result[0][2] = mat[0][2] + scalar;
        result[0][3] = mat[0][3] + scalar;
        result[1][0] = mat[1][0] + scalar;
        result[1][1] = mat[1][1] + scalar;
        result[1][2] = mat[1][2] + scalar;
        result[1][3] = mat[1][3] + scalar;
        result[2][0] = mat[2][0] + scalar;
        result[2][1] = mat[2][1] + scalar;
        result[2][2] = mat[2][2] + scalar;
        result[2][3] = mat[2][3] + scalar;
    }

    TS_FUNDAMENTAL_SM(3, 4, scalar_sub_matrix)
        result[0][0] = scalar - mat[0][0];
        result[0][1] = scalar - mat[0][1];
        result[0][2] = scalar - mat[0][2];
        result[0][3] = scalar - mat[0][3];
        result[1][0] = scalar - mat[1][0];
        result[1][1] = scalar - mat[1][1];
        result[1][2] = scalar - mat[1][2];
        result[1][3] = scalar - mat[1][3];
        result[2][0] = scalar - mat[2][0];
        result[2][1] = scalar - mat[2][1];
        result[2][2] = scalar - mat[2][2];
        result[2][3] = scalar - mat[2][3];
    }

    TS_FUNDAMENTAL_MS(3, 4, matrix_sub_scalar)
        result[0][0] = mat[0][0] - scalar;
        result[0][1] = mat[0][1] - scalar;
        result[0][2] = mat[0][2] - scalar;
        result[0][3] = mat[0][3] - scalar;
        result[1][0] = mat[1][0] - scalar;
        result[1][1] = mat[1][1] - scalar;
        result[1][2] = mat[1][2] - scalar;
        result[1][3] = mat[1][3] - scalar;
        result[2][0] = mat[2][0] - scalar;
        result[2][1] = mat[2][1] - scalar;
        result[2][2] = mat[2][2] - scalar;
        result[2][3] = mat[2][3] - scalar;
    }

    TS_FUNDAMENTAL_SM(3, 4, scalar_mul_matrix)
        result[0][0] = scalar * mat[0][0];
        result[0][1] = scalar * mat[0][1];
        result[0][2] = scalar * mat[0][2];
        result[0][3] = scalar * mat[0][3];
        result[1][0] = scalar * mat[1][0];
        result[1][1] = scalar * mat[1][1];
        result[1][2] = scalar * mat[1][2];
        result[1][3] = scalar * mat[1][3];
        result[2][0] = scalar * mat[2][0];
        result[2][1] = scalar * mat[2][1];
        result[2][2] = scalar * mat[2][2];
        result[2][3] = scalar * mat[2][3];
    }

    TS_FUNDAMENTAL_MS(3, 4, matrix_mul_scalar)
        result[0][0] = mat[0][0] * scalar;
        result[0][1] = mat[0][1] * scalar;
        result[0][2] = mat[0][2] * scalar;
        result[0][3] = mat[0][3] * scalar;
        result[1][0] = mat[1][0] * scalar;
        result[1][1] = mat[1][1] * scalar;
        result[1][2] = mat[1][2] * scalar;
        result[1][3] = mat[1][3] * scalar;
        result[2][0] = mat[2][0] * scalar;
        result[2][1] = mat[2][1] * scalar;
        result[2][2] = mat[2][2] * scalar;
        result[2][3] = mat[2][3] * scalar;
    }

    TS_FUNDAMENTAL_SM(3, 4, scalar_div_matrix)
        result[0][0] = scalar / mat[0][0];
        result[0][1] = scalar / mat[0][1];
        result[0][2] = scalar / mat[0][2];
        result[0][3] = scalar / mat[0][3];
        result[1][0] = scalar / mat[1][0];
        result[1][1] = scalar / mat[1][1];
        result[1][2] = scalar / mat[1][2];
        result[1][3] = scalar / mat[1][3];
        result[2][0] = scalar / mat[2][0];
        result[2][1] = scalar / mat[2][1];
        result[2][2] = scalar / mat[2][2];
        result[2][3] = scalar / mat[2][3];
    }

    TS_FUNDAMENTAL_MS(3, 4, matrix_div_scalar)
        result[0][0] = mat[0][0] / scalar;
        result[0][1] = mat[0][1] / scalar;
        result[0][2] = mat[0][2] / scalar;
        result[0][3] = mat[0][3] / scalar;
        result[1][0] = mat[1][0] / scalar;
        result[1][1] = mat[1][1] / scalar;
        result[1][2] = mat[1][2] / scalar;
        result[1][3] = mat[1][3] / scalar;
        result[2][0] = mat[2][0] / scalar;
        result[2][1] = mat[2][1] / scalar;
        result[2][2] = mat[2][2] / scalar;
        result[2][3] = mat[2][3] / scalar;
    }

    // 4x2
    TS_FUNDAMENTAL_SM(4, 2, scalar_add_matrix)
        result[0][0] = scalar + mat[0][0];
        result[0][1] = scalar + mat[0][1];
        result[1][0] = scalar + mat[1][0];
        result[1][1] = scalar + mat[1][1];
        result[2][0] = scalar + mat[2][0];
        result[2][1] = scalar + mat[2][1];
        result[3][0] = scalar + mat[3][0];
        result[3][1] = scalar + mat[3][1];
    }

    TS_FUNDAMENTAL_MS(4, 2, matrix_add_scalar)
        result[0][0] = mat[0][0] + scalar;
        result[0][1] = mat[0][1] + scalar;
        result[1][0] = mat[1][0] + scalar;
        result[1][1] = mat[1][1] + scalar;
        result[2][0] = mat[2][0] + scalar;
        result[2][1] = mat[2][1] + scalar;
        result[3][0] = mat[3][0] + scalar;
        result[3][1] = mat[3][1] + scalar;
    }

    TS_FUNDAMENTAL_SM(4, 2, scalar_sub_matrix)
        result[0][0] = scalar - mat[0][0];
        result[0][1] = scalar - mat[0][1];
        result[1][0] = scalar - mat[1][0];
        result[1][1] = scalar - mat[1][1];
        result[2][0] = scalar - mat[2][0];
        result[2][1] = scalar - mat[2][1];
        result[3][0] = scalar - mat[3][0];
        result[3][1] = scalar - mat[3][1];
    }

    TS_FUNDAMENTAL_MS(4, 2, matrix_sub_scalar)
        result[0][0] = mat[0][0] - scalar;
        result[0][1] = mat[0][1] - scalar;
        result[1][0] = mat[1][0] - scalar;
        result[1][1] = mat[1][1] - scalar;
        result[2][0] = mat[2][0] - scalar;
        result[2][1] = mat[2][1] - scalar;
        result[3][0] = mat[3][0] - scalar;
        result[3][1] = mat[3][1] - scalar;
    }

    TS_FUNDAMENTAL_SM(4, 2, scalar_mul_matrix)
        result[0][0] = scalar * mat[0][0];
        result[0][1] = scalar * mat[0][1];
        result[1][0] = scalar * mat[1][0];
        result[1][1] = scalar * mat[1][1];
        result[2][0] = scalar * mat[2][0];
        result[2][1] = scalar * mat[2][1];
        result[3][0] = scalar * mat[3][0];
        result[3][1] = scalar * mat[3][1];
    }

    TS_FUNDAMENTAL_MS(4, 2, matrix_mul_scalar)
        result[0][0] = mat[0][0] * scalar;
        result[0][1] = mat[0][1] * scalar;
        result[1][0] = mat[1][0] * scalar;
        result[1][1] = mat[1][1] * scalar;
        result[2][0] = mat[2][0] * scalar;
        result[2][1] = mat[2][1] * scalar;
        result[3][0] = mat[3][0] * scalar;
        result[3][1] = mat[3][1] * scalar;
    }

    TS_FUNDAMENTAL_SM(4, 2, scalar_div_matrix)
        result[0][0] = scalar / mat[0][0];
        result[0][1] = scalar / mat[0][1];
        result[1][0] = scalar / mat[1][0];
        result[1][1] = scalar / mat[1][1];
        result[2][0] = scalar / mat[2][0];
        result[2][1] = scalar / mat[2][1];
        result[3][0] = scalar / mat[3][0];
        result[3][1] = scalar / mat[3][1];
    }

    TS_FUNDAMENTAL_MS(4, 2, matrix_div_scalar)
        result[0][0] = mat[0][0] / scalar;
        result[0][1] = mat[0][1] / scalar;
        result[1][0] = mat[1][0] / scalar;
        result[1][1] = mat[1][1] / scalar;
        result[2][0] = mat[2][0] / scalar;
        result[2][1] = mat[2][1] / scalar;
        result[3][0] = mat[3][0] / scalar;
        result[3][1] = mat[3][1] / scalar;
    }

    // 4x3
    TS_FUNDAMENTAL_SM(4, 3, scalar_add_matrix)
        result[0][0] = scalar + mat[0][0];
        result[0][1] = scalar + mat[0][1];
        result[0][2] = scalar + mat[0][2];
        result[1][0] = scalar + mat[1][0];
        result[1][1] = scalar + mat[1][1];
        result[1][2] = scalar + mat[1][2];
        result[2][0] = scalar + mat[2][0];
        result[2][1] = scalar + mat[2][1];
        result[2][2] = scalar + mat[2][2];
        result[3][0] = scalar + mat[3][0];
        result[3][1] = scalar + mat[3][1];
        result[3][2] = scalar + mat[3][2];
    }

    TS_FUNDAMENTAL_MS(4, 3, matrix_add_scalar)
        result[0][0] = mat[0][0] + scalar;
        result[0][1] = mat[0][1] + scalar;
        result[0][2] = mat[0][2] + scalar;
        result[1][0] = mat[1][0] + scalar;
        result[1][1] = mat[1][1] + scalar;
        result[1][2] = mat[1][2] + scalar;
        result[2][0] = mat[2][0] + scalar;
        result[2][1] = mat[2][1] + scalar;
        result[2][2] = mat[2][2] + scalar;
        result[3][0] = mat[3][0] + scalar;
        result[3][1] = mat[3][1] + scalar;
        result[3][2] = mat[3][2] + scalar;
    }

    TS_FUNDAMENTAL_SM(4, 3, scalar_sub_matrix)
        result[0][0] = scalar - mat[0][0];
        result[0][1] = scalar - mat[0][1];
        result[0][2] = scalar - mat[0][2];
        result[1][0] = scalar - mat[1][0];
        result[1][1] = scalar - mat[1][1];
        result[1][2] = scalar - mat[1][2];
        result[2][0] = scalar - mat[2][0];
        result[2][1] = scalar - mat[2][1];
        result[2][2] = scalar - mat[2][2];
        result[3][0] = scalar - mat[3][0];
        result[3][1] = scalar - mat[3][1];
        result[3][2] = scalar - mat[3][2];
    }

    TS_FUNDAMENTAL_MS(4, 3, matrix_sub_scalar)
        result[0][0] = mat[0][0] - scalar;
        result[0][1] = mat[0][1] - scalar;
        result[0][2] = mat[0][2] - scalar;
        result[1][0] = mat[1][0] - scalar;
        result[1][1] = mat[1][1] - scalar;
        result[1][2] = mat[1][2] - scalar;
        result[2][0] = mat[2][0] - scalar;
        result[2][1] = mat[2][1] - scalar;
        result[2][2] = mat[2][2] - scalar;
        result[3][0] = mat[3][0] - scalar;
        result[3][1] = mat[3][1] - scalar;
        result[3][2] = mat[3][2] - scalar;
    }

    TS_FUNDAMENTAL_SM(4, 3, scalar_mul_matrix)
        result[0][0] = scalar * mat[0][0];
        result[0][1] = scalar * mat[0][1];
        result[0][2] = scalar * mat[0][2];
        result[1][0] = scalar * mat[1][0];
        result[1][1] = scalar * mat[1][1];
        result[1][2] = scalar * mat[1][2];
        result[2][0] = scalar * mat[2][0];
        result[2][1] = scalar * mat[2][1];
        result[2][2] = scalar * mat[2][2];
        result[3][0] = scalar * mat[3][0];
        result[3][1] = scalar * mat[3][1];
        result[3][2] = scalar * mat[3][2];
    }

    TS_FUNDAMENTAL_MS(4, 3, matrix_mul_scalar)
        result[0][0] = mat[0][0] * scalar;
        result[0][1] = mat[0][1] * scalar;
        result[0][2] = mat[0][2] * scalar;
        result[1][0] = mat[1][0] * scalar;
        result[1][1] = mat[1][1] * scalar;
        result[1][2] = mat[1][2] * scalar;
        result[2][0] = mat[2][0] * scalar;
        result[2][1] = mat[2][1] * scalar;
        result[2][2] = mat[2][2] * scalar;
        result[3][0] = mat[3][0] * scalar;
        result[3][1] = mat[3][1] * scalar;
        result[3][2] = mat[3][2] * scalar;
    }

    TS_FUNDAMENTAL_SM(4, 3, scalar_div_matrix)
        result[0][0] = scalar / mat[0][0];
        result[0][1] = scalar / mat[0][1];
        result[0][2] = scalar / mat[0][2];
        result[1][0] = scalar / mat[1][0];
        result[1][1] = scalar / mat[1][1];
        result[1][2] = scalar / mat[1][2];
        result[2][0] = scalar / mat[2][0];
        result[2][1] = scalar / mat[2][1];
        result[2][2] = scalar / mat[2][2];
        result[3][0] = scalar / mat[3][0];
        result[3][1] = scalar / mat[3][1];
        result[3][2] = scalar / mat[3][2];
    }

    TS_FUNDAMENTAL_MS(4, 3, matrix_div_scalar)
        result[0][0] = mat[0][0] / scalar;
        result[0][1] = mat[0][1] / scalar;
        result[0][2] = mat[0][2] / scalar;
        result[1][0] = mat[1][0] / scalar;
        result[1][1] = mat[1][1] / scalar;
        result[1][2] = mat[1][2] / scalar;
        result[2][0] = mat[2][0] / scalar;
        result[2][1] = mat[2][1] / scalar;
        result[2][2] = mat[2][2] / scalar;
        result[3][0] = mat[3][0] / scalar;
        result[3][1] = mat[3][1] / scalar;
        result[3][2] = mat[3][2] / scalar;
    }

    // 4x4
    TS_FUNDAMENTAL_SM(4, 4, scalar_add_matrix)
        result[0][0] = scalar + mat[0][0];
        result[0][1] = scalar + mat[0][1];
        result[0][2] = scalar + mat[0][2];
        result[0][3] = scalar + mat[0][3];
        result[1][0] = scalar + mat[1][0];
        result[1][1] = scalar + mat[1][1];
        result[1][2] = scalar + mat[1][2];
        result[1][3] = scalar + mat[1][3];
        result[2][0] = scalar + mat[2][0];
        result[2][1] = scalar + mat[2][1];
        result[2][2] = scalar + mat[2][2];
        result[2][3] = scalar + mat[2][3];
        result[3][0] = scalar + mat[3][0];
        result[3][1] = scalar + mat[3][1];
        result[3][2] = scalar + mat[3][2];
        result[3][3] = scalar + mat[3][3];
    }

    TS_FUNDAMENTAL_MS(4, 4, matrix_add_scalar)
        result[0][0] = mat[0][0] + scalar;
        result[0][1] = mat[0][1] + scalar;
        result[0][2] = mat[0][2] + scalar;
        result[0][3] = mat[0][3] + scalar;
        result[1][0] = mat[1][0] + scalar;
        result[1][1] = mat[1][1] + scalar;
        result[1][2] = mat[1][2] + scalar;
        result[1][3] = mat[1][3] + scalar;
        result[2][0] = mat[2][0] + scalar;
        result[2][1] = mat[2][1] + scalar;
        result[2][2] = mat[2][2] + scalar;
        result[2][3] = mat[2][3] + scalar;
        result[3][0] = mat[3][0] + scalar;
        result[3][1] = mat[3][1] + scalar;
        result[3][2] = mat[3][2] + scalar;
        result[3][3] = mat[3][3] + scalar;
    }

    TS_FUNDAMENTAL_SM(4, 4, scalar_sub_matrix)
        result[0][0] = scalar - mat[0][0];
        result[0][1] = scalar - mat[0][1];
        result[0][2] = scalar - mat[0][2];
        result[0][3] = scalar - mat[0][3];
        result[1][0] = scalar - mat[1][0];
        result[1][1] = scalar - mat[1][1];
        result[1][2] = scalar - mat[1][2];
        result[1][3] = scalar - mat[1][3];
        result[2][0] = scalar - mat[2][0];
        result[2][1] = scalar - mat[2][1];
        result[2][2] = scalar - mat[2][2];
        result[2][3] = scalar - mat[2][3];
        result[3][0] = scalar - mat[3][0];
        result[3][1] = scalar - mat[3][1];
        result[3][2] = scalar - mat[3][2];
        result[3][3] = scalar - mat[3][3];
    }

    TS_FUNDAMENTAL_MS(4, 4, matrix_sub_scalar)
        result[0][0] = mat[0][0] - scalar;
        result[0][1] = mat[0][1] - scalar;
        result[0][2] = mat[0][2] - scalar;
        result[0][3] = mat[0][3] - scalar;
        result[1][0] = mat[1][0] - scalar;
        result[1][1] = mat[1][1] - scalar;
        result[1][2] = mat[1][2] - scalar;
        result[1][3] = mat[1][3] - scalar;
        result[2][0] = mat[2][0] - scalar;
        result[2][1] = mat[2][1] - scalar;
        result[2][2] = mat[2][2] - scalar;
        result[2][3] = mat[2][3] - scalar;
        result[3][0] = mat[3][0] - scalar;
        result[3][1] = mat[3][1] - scalar;
        result[3][2] = mat[3][2] - scalar;
        result[3][3] = mat[3][3] - scalar;
    }

    TS_FUNDAMENTAL_SM(4, 4, scalar_mul_matrix)
        result[0][0] = scalar * mat[0][0];
        result[0][1] = scalar * mat[0][1];
        result[0][2] = scalar * mat[0][2];
        result[0][3] = scalar * mat[0][3];
        result[1][0] = scalar * mat[1][0];
        result[1][1] = scalar * mat[1][1];
        result[1][2] = scalar * mat[1][2];
        result[1][3] = scalar * mat[1][3];
        result[2][0] = scalar * mat[2][0];
        result[2][1] = scalar * mat[2][1];
        result[2][2] = scalar * mat[2][2];
        result[2][3] = scalar * mat[2][3];
        result[3][0] = scalar * mat[3][0];
        result[3][1] = scalar * mat[3][1];
        result[3][2] = scalar * mat[3][2];
        result[3][3] = scalar * mat[3][3];
    }

    TS_FUNDAMENTAL_MS(4, 4, matrix_mul_scalar)
        result[0][0] = mat[0][0] * scalar;
        result[0][1] = mat[0][1] * scalar;
        result[0][2] = mat[0][2] * scalar;
        result[0][3] = mat[0][3] * scalar;
        result[1][0] = mat[1][0] * scalar;
        result[1][1] = mat[1][1] * scalar;
        result[1][2] = mat[1][2] * scalar;
        result[1][3] = mat[1][3] * scalar;
        result[2][0] = mat[2][0] * scalar;
        result[2][1] = mat[2][1] * scalar;
        result[2][2] = mat[2][2] * scalar;
        result[2][3] = mat[2][3] * scalar;
        result[3][0] = mat[3][0] * scalar;
        result[3][1] = mat[3][1] * scalar;
        result[3][2] = mat[3][2] * scalar;
        result[3][3] = mat[3][3] * scalar;
    }

    TS_FUNDAMENTAL_SM(4, 4, scalar_div_matrix)
        result[0][0] = scalar / mat[0][0];
        result[0][1] = scalar / mat[0][1];
        result[0][2] = scalar / mat[0][2];
        result[0][3] = scalar / mat[0][3];
        result[1][0] = scalar / mat[1][0];
        result[1][1] = scalar / mat[1][1];
        result[1][2] = scalar / mat[1][2];
        result[1][3] = scalar / mat[1][3];
        result[2][0] = scalar / mat[2][0];
        result[2][1] = scalar / mat[2][1];
        result[2][2] = scalar / mat[2][2];
        result[2][3] = scalar / mat[2][3];
        result[3][0] = scalar / mat[3][0];
        result[3][1] = scalar / mat[3][1];
        result[3][2] = scalar / mat[3][2];
        result[3][3] = scalar / mat[3][3];
    }

    TS_FUNDAMENTAL_MS(4, 4, matrix_div_scalar)
        result[0][0] = mat[0][0] / scalar;
        result[0][1] = mat[0][1] / scalar;
        result[0][2] = mat[0][2] / scalar;
        result[0][3] = mat[0][3] / scalar;
        result[1][0] = mat[1][0] / scalar;
        result[1][1] = mat[1][1] / scalar;
        result[1][2] = mat[1][2] / scalar;
        result[1][3] = mat[1][3] / scalar;
        result[2][0] = mat[2][0] / scalar;
        result[2][1] = mat[2][1] / scalar;
        result[2][2] = mat[2][2] / scalar;
        result[2][3] = mat[2][3] / scalar;
        result[3][0] = mat[3][0] / scalar;
        result[3][1] = mat[3][1] / scalar;
        result[3][2] = mat[3][2] / scalar;
        result[3][3] = mat[3][3] / scalar;
    }

};