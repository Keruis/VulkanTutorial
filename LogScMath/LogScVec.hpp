#ifndef __LOGSCVEC_H
#define __LOGSCVEC_H
#include "LogScMatrix.hpp"
#define OPTIMIZE_VEC_FOR

namespace LogSc {
template<typename T,size_t C> class Vec;
template<size_t Cols> using VecShort      = LogSc::Vec<short,  Cols>;
template<size_t Cols> using VecInt        = LogSc::Vec<int,  Cols>;
template<size_t Cols> using VecFloat      = LogSc::Vec<float,  Cols>;
template<size_t Cols> using VecDouble     = LogSc::Vec<double,  Cols>;
template<size_t Cols> using VecLong       = LogSc::Vec<long,  Cols>;
template<size_t Cols> using VecLongLong   = LogSc::Vec<long long, Cols>;

/// -------------- Vec属于特殊矩阵 --------------
template<typename T,size_t C>
class alignas(16) Vec: public Matrix<T, 1, C>
{
    static_assert(std::is_arithmetic<T>::value, "Matrix requires arithmetic scalar type");
public:
    constexpr Vec() noexcept : Matrix<T, 1, C>(){}
    constexpr Vec(std::initializer_list<T> init) noexcept :Matrix<T, 1, C>(init){}
    ~Vec() = default;
};
/// -------------- 向量 和 矩阵 --------------
/* ---- 乘法通用 ---- */
template<typename T, size_t C1, size_t C2>
constexpr void __multiply_vc(const Vec<T, C1>& lhs, const Matrix<T, C1, C2>& rhs, Vec<T,C2>& result) noexcept{
    for (size_t j = 0; j < C2; ++j) 
        result[0][j] = T{0};
    for (size_t j = 0; j < C2; ++j) 
        for (size_t i = 0; i < C1; ++i) 
            result[0][j] += lhs[0][i] * rhs[i][j];
};
/* ---- 乘法泛化 ---- */
template<typename T, size_t C1, size_t C2>
struct VecMatrixMultiplySp {
    constexpr static void multiply(const Vec<T, C1>& lhs, const Matrix<T, C1, C2>& rhs, Vec<T,C2>& result) noexcept{
        __multiply_vc(lhs,rhs,result);
    }
};
/* ---- 乘法重载 ---- */
template<typename T, size_t C1, size_t C2>
constexpr Vec<T,C2> operator*(const Vec<T, C1>& lhs, const Matrix<T, C1, C2>& rhs) noexcept {
    Vec<T, C2> result;
    LogSc::VecMatrixMultiplySp<T,C1,C2>::multiply(lhs,rhs,result);
    return result;
}
/* ----  乘法特化 ---- */
#define VECMATRIXMULTIPLYSP_TEMPLATE_CLASS(C1,C2) \
template<typename T>\
struct VecMatrixMultiplySp<T, C1, C2> {\
    constexpr static void multiply(const Vec<T, C1>& lhs, const Matrix<T, C1, C2>& rhs, Vec<T,C2>& result) noexcept;\
};
VECMATRIXMULTIPLYSP_TEMPLATE_CLASS(2,2)
VECMATRIXMULTIPLYSP_TEMPLATE_CLASS(2,3)
VECMATRIXMULTIPLYSP_TEMPLATE_CLASS(2,4)
VECMATRIXMULTIPLYSP_TEMPLATE_CLASS(3,2)
VECMATRIXMULTIPLYSP_TEMPLATE_CLASS(3,3)
VECMATRIXMULTIPLYSP_TEMPLATE_CLASS(3,4)
VECMATRIXMULTIPLYSP_TEMPLATE_CLASS(4,2)
VECMATRIXMULTIPLYSP_TEMPLATE_CLASS(4,3)
VECMATRIXMULTIPLYSP_TEMPLATE_CLASS(4,4)
/// -------------- 向量 和 向量 --------------
/* ---- 加法通用 ---- */
template<typename T, size_t C>
constexpr void __add_vec(const Vec<T, C>& lhs, const Vec<T, C>& rhs, Vec<T, C>& result) noexcept {
#ifdef OPTIMIZE_VEC_FOR
    for (size_t i = 0; i < C; ++i)
        result.data(i) = lhs.data(i) + rhs.data(i);
#else
    for (size_t i = 0; i < C; ++i) 
        result[0][i] = lhs[0][i] + rhs[0][i];
#endif
}
/* ---- 加法泛化 ---- */
template<typename T, size_t C>
struct VecMatrixAddSp {
    constexpr static void add(const Vec<T, C>& lhs, const Vec<T, C>& rhs, Vec<T, C>& result) noexcept{
        __add_vec(lhs,rhs,result);
    }
};
/* ---- 加法重载 ---- */
template<typename T, size_t C>
constexpr Vec<T, C> operator+(const Vec<T, C>& lhs, const Vec<T, C>& rhs) noexcept{
    Vec<T, C> result;
    LogSc::VecMatrixAddSp<T, C>::add(lhs,rhs,result);
    return result;
}
/* ---- 加法特化 ---- */
#define VECMATRIXADDSP_TEMPLATE_CLASS(C) \
template<typename T>\
struct VecMatrixAddSp<T, C> {\
    constexpr static void add(const Vec<T, C>& lhs, const Vec<T, C>& rhs, Vec<T, C>& result) noexcept;\
};
VECMATRIXADDSP_TEMPLATE_CLASS(2)
VECMATRIXADDSP_TEMPLATE_CLASS(3)
VECMATRIXADDSP_TEMPLATE_CLASS(4)
/* ---- 减法通用 ---- */
template<typename T, size_t C>
constexpr void __subtract_vec(const Vec<T, C>& lhs, const Vec<T, C>& rhs, Vec<T, C>& result) noexcept {
#ifdef OPTIMIZE_VEC_FOR
    for (size_t i = 0; i < C; ++i)
        result.data(i) = lhs.data(i) - rhs.data(i);
#else
    for (size_t i = 0; i < C; ++i) 
        result[0][i] = lhs[0][i] - rhs[0][i];
#endif
}
/* ---- 减法泛化 ---- */
template<typename T, size_t C>
struct VecMatrixSubtractSp {
    constexpr static void subtract(const Vec<T, C>& lhs, const Vec<T, C>& rhs, Vec<T, C>& result) noexcept{
        __subtract_vec(lhs,rhs,result);
    }
};
/* ---- 减法重载 ---- */
template<typename T, size_t C>
constexpr Vec<T, C> operator-(const Vec<T, C>& lhs, const Vec<T, C>& rhs) noexcept{
    Vec<T, C> result;
    LogSc::VecMatrixSubtractSp<T, C>::subtract(lhs,rhs,result);
    return result;
}
/* ---- 减法特化 ---- */
#define VECMATRIXSUBTRACTSP_TEMPLATE_CLASS(C) \
template<typename T>\
struct VecMatrixSubtractSp<T, C> {\
    constexpr static void subtract(const Vec<T, C>& lhs, const Vec<T, C>& rhs, Vec<T, C>& result) noexcept;\
};
VECMATRIXSUBTRACTSP_TEMPLATE_CLASS(2)
VECMATRIXSUBTRACTSP_TEMPLATE_CLASS(3)
VECMATRIXSUBTRACTSP_TEMPLATE_CLASS(4)
/// -------------- 向量 和 标量 --------------
/* ---- 数乘 乘数 数除 除数 数加 加数 数减 减数 （通用） ---- */
template<typename T, size_t C>
constexpr void __scalar_add_matrix_vec(const T& scalar, const Vec<T, C>& vec, Vec<T, C>& result) noexcept {
#ifdef OPTIMIZE_VEC_FOR
    for (size_t i = 0; i < C; ++i) 
        result.data(i) = scalar + vec.data(i);
#else
    for (size_t i = 0; i < C; ++i)
        result[0][i] = scalar + vec[0][i];
#endif
}
template<typename T, size_t C>
constexpr void __matrix_add_scalar_vec(const Vec<T, C>& vec, const T& scalar, Vec<T, C>& result) noexcept {
    __scalar_add_matrix_vec(scalar,vec,result);
}
template<typename T, size_t C>
constexpr void __scalar_sub_matrix_vec(const T& scalar, const Vec<T, C>& vec, Vec<T, C>& result) noexcept {
#ifdef OPTIMIZE_VEC_FOR
    for (size_t i = 0; i < C; ++i) 
        result.data(i) = scalar - vec.data(i);
#else
    for (size_t i = 0; i < C; ++i)
        result[0][i] = scalar - vec[0][i];
#endif
}
template<typename T, size_t C>
constexpr void __matrix_sub_scalar_vec(const Vec<T, C>& vec, const T& scalar, Vec<T, C>& result) noexcept {
#ifdef OPTIMIZE_VEC_FOR
    for (size_t i = 0; i < C; ++i) 
        result.data(i) = vec.data(i) - scalar;
#else
    for (size_t i = 0; i < C; ++i)
        result[0][i] = vec[0][i] - scalar;
#endif
}
template<typename T, size_t C>
constexpr void __scalar_mul_matrix_vec(const T& scalar, const Vec<T, C>& vec, Vec<T, C>& result) noexcept {
#ifdef OPTIMIZE_VEC_FOR
    for (size_t i = 0; i < C; ++i)
        result.data(i) = scalar * vec.data(i);
#else
    for (size_t i = 0; i < C; ++i)
        result[0][i] = scalar * vec[0][i];
#endif
}
template<typename T, size_t C>
constexpr void __matrix_mul_scalar_vec(const Vec<T, C>& vec, const T& scalar, Vec<T, C>& result) noexcept {
    __scalar_mul_matrix_vec(scalar, vec, result);
}
template<typename T, size_t C>
constexpr void __scalar_div_matrix_vec(const T& scalar, const Vec<T, C>& vec, Vec<T, C>& result) noexcept {
#ifdef OPTIMIZE_VEC_FOR
    for (size_t i = 0; i < C; ++i) 
        result.data(i) = scalar / vec.data(i);
#else
    for (size_t i = 0; i < C; ++i)
        result[0][i] = scalar / vec[0][i];
#endif
}
template<typename T, size_t C>
constexpr void __matrix_div_scalar_vec(const Vec<T, C>& vec, const T& scalar, Vec<T, C>& result) noexcept {
#ifdef OPTIMIZE_VEC_FOR
    for (size_t i = 0; i < C; ++i) 
        result.data(i) = vec.data(i) / scalar;
#else
    for (size_t i = 0; i < C; ++i)
        result[0][i] = vec[0][i] / scalar;
#endif
}
/* ---- 数乘 乘数 数除 除数 数加 加数 数减 减数 （泛化） ---- */
template<typename T, size_t C>
struct VecMatrixFundamentalSp {
    constexpr static void scalar_add_matrix(const T& scalar, const Vec<T, C>& vec, Vec<T, C>& result) noexcept {
        __scalar_add_matrix_vec(scalar, vec, result);
    }
    constexpr static void matrix_add_scalar(const Vec<T, C>& vec, const T& scalar, Vec<T, C>& result) noexcept {
        __matrix_add_scalar_vec(vec, scalar, result);
    }
    constexpr static void scalar_sub_matrix(const T& scalar, const Vec<T, C>& vec, Vec<T, C>& result) noexcept {
        __scalar_sub_matrix_vec(scalar, vec, result);
    }
    constexpr static void matrix_sub_scalar(const Vec<T, C>& vec, const T& scalar, Vec<T, C>& result) noexcept {
        __matrix_sub_scalar_vec(vec, scalar, result);
    }
    constexpr static void scalar_mul_matrix(const T& scalar, const Vec<T, C>& vec, Vec<T, C>& result) noexcept {
        __scalar_mul_matrix_vec(scalar, vec, result);
    }
    constexpr static void matrix_mul_scalar(const Vec<T, C>& vec, const T& scalar, Vec<T, C>& result) noexcept {
        __matrix_mul_scalar_vec(vec, scalar, result);
    }
    constexpr static void scalar_div_matrix(const T& scalar, const Vec<T, C>& vec, Vec<T, C>& result) noexcept {
        __scalar_div_matrix_vec(scalar, vec, result);
    }
    constexpr static void matrix_div_scalar(const Vec<T, C>& vec, const T& scalar, Vec<T, C>& result) noexcept {
        __matrix_div_scalar_vec(vec, scalar, result);
    }
};
/* ---- 数乘 乘数 数除 除数 数加 加数 数减 减数 （特化） ---- */
#define VECMATRIXFUNDAMENTALSP_TEMPLATE_CLASS(C) \
template<typename T>\
struct VecMatrixFundamentalSp<T, C> \
{\
    constexpr static void scalar_add_matrix(const T& scalar, const Vec<T, C>& vec, Vec<T, C>& result) noexcept; \
    constexpr static void matrix_add_scalar(const Vec<T, C>& vec, const T& scalar, Vec<T, C>& result) noexcept; \
    constexpr static void scalar_sub_matrix(const T& scalar, const Vec<T, C>& vec, Vec<T, C>& result) noexcept; \
    constexpr static void matrix_sub_scalar(const Vec<T, C>& vec, const T& scalar, Vec<T, C>& result) noexcept; \
    constexpr static void scalar_mul_matrix(const T& scalar, const Vec<T, C>& vec, Vec<T, C>& result) noexcept; \
    constexpr static void matrix_mul_scalar(const Vec<T, C>& vec, const T& scalar, Vec<T, C>& result) noexcept; \
    constexpr static void scalar_div_matrix(const T& scalar, const Vec<T, C>& vec, Vec<T, C>& result) noexcept; \
    constexpr static void matrix_div_scalar(const Vec<T, C>& vec, const T& scalar, Vec<T, C>& result) noexcept; \
};
VECMATRIXFUNDAMENTALSP_TEMPLATE_CLASS(2)
VECMATRIXFUNDAMENTALSP_TEMPLATE_CLASS(3)
VECMATRIXFUNDAMENTALSP_TEMPLATE_CLASS(4)
/* ---- 作比较通用 ---- */
template<typename T, size_t C>
constexpr bool __compare_vec(const Vec<T, C>& lhs, const Vec<T, C>& rhs) noexcept {
#ifdef OPTIMIZE_VEC_FOR
    for (size_t i = 0; i < C; ++i)
        if (lhs.data(i) != rhs.data(i))
            return false;
#else
    for (size_t i = 0; i < C; ++i)
        if (lhs[0][i] != rhs[0][i])
            return false;
#endif
    return true;
}
/* ---- 作比较泛化 ---- */
template<typename T, size_t C>
struct VecMatrixCompareSp {
    constexpr static bool compare(const Vec<T, C>& lhs, const Vec<T, C>& rhs) noexcept{
        return __compare_vec(lhs,rhs);
    }
};
template<typename T, size_t C>
constexpr bool operator==(const Vec<T, C>& lhs, const Vec<T, C>& rhs) noexcept{
    return LogSc::VecMatrixCompareSp<T, C>::compare(lhs,rhs);
}
template<typename T, size_t C>
constexpr bool operator!=(const Vec<T, C>& lhs, const Vec<T, C>& rhs) noexcept{
    return !LogSc::VecMatrixCompareSp<T, C>::compare(lhs,rhs);
}
/* ---- 作比较特化 ---- */
#define VECMATRIXCOMPARESP_TEMPLATE_CLASS(C) \
template<typename T>\
struct VecMatrixCompareSp<T, C> {\
    constexpr static bool compare(const Vec<T, C>& lhs, const Vec<T, C>& rhs) noexcept;\
};
VECMATRIXCOMPARESP_TEMPLATE_CLASS(2)
VECMATRIXCOMPARESP_TEMPLATE_CLASS(3)
VECMATRIXCOMPARESP_TEMPLATE_CLASS(4)
//------------------------------------------ 复合运算 -----------------------------------------------
/* ---- 复合重载 ---- */
template<typename T, size_t C>
constexpr Vec<T, C>& operator+=(Vec<T, C>& lhs, const Vec<T, C>& rhs) noexcept{
    LogSc::VecMatrixAddSp<T, C>::add(lhs,rhs,lhs);
    return lhs;
}
template<typename T, size_t C>
constexpr Vec<T, C>& operator-=(Vec<T, C>& lhs, const Vec<T, C>& rhs) noexcept{
    LogSc::VecMatrixSubtractSp<T, C>::subtract(lhs,rhs,lhs);
    return lhs;
}
template<typename T, size_t C>
constexpr Vec<T, C>& operator+=(Vec<T, C>& vec, const T& scalar) noexcept {
    LogSc::VecMatrixFundamentalSp<T, C>::matrix_add_scalar(vec,scalar,vec);
    return vec;
}
template<typename T, size_t C>
constexpr Vec<T, C>& operator-=(Vec<T, C>& vec, const T& scalar) noexcept {
    LogSc::VecMatrixFundamentalSp<T, C>::matrix_sub_scalar(vec,scalar,vec);
    return vec;
}
template<typename T, size_t C>
constexpr Vec<T, C>& operator*=(Vec<T, C>& vec, const T& scalar) noexcept {
    LogSc::VecMatrixFundamentalSp<T, C>::matrix_mul_scalar(vec,scalar,vec);
    return vec;
}
template<typename T, size_t C>
constexpr Vec<T, C>& operator/=(Vec<T, C>& vec, const T& scalar) noexcept {
    LogSc::VecMatrixFundamentalSp<T, C>::matrix_div_scalar(vec,scalar,vec);
    return vec;
}
template<typename T, size_t C>
constexpr Vec<T, C>& operator++(Vec<T, C>& vec) noexcept{
    LogSc::VecMatrixFundamentalSp<T, C>::matrix_add_scalar(vec,T{1},vec);
    return vec;
}
template<typename T, size_t C>
constexpr Vec<T, C> operator++(Vec<T, C>& vec, int) noexcept{
    Vec<T, C> result = vec;
    LogSc::VecMatrixFundamentalSp<T, C>::matrix_add_scalar(vec,T{1},vec);
    return result;
}
template<typename T, size_t C>
constexpr Vec<T, C>& operator--(Vec<T, C>& vec) noexcept {
    LogSc::VecMatrixFundamentalSp<T, C>::matrix_sub_scalar(vec, T{1}, vec);
    return vec;
}
template<typename T, size_t C>
constexpr Vec<T, C> operator--(Vec<T, C>& vec, int) noexcept {
    Vec<T, C> result = vec;
    LogSc::VecMatrixFundamentalSp<T, C>::matrix_sub_scalar(vec, T{1}, vec);
    return result;
}
};
#include "LogScVecAdd.tpp"
#include "LogScVecSubtract.tpp"
#include "LogScVecMultiply.tpp"
#include "LogScVecFundamental.tpp"
#include "LogScVecCompare.tpp"
#undef OPTIMIZE_VEC_FOR
#undef VECMATRIXMULTIPLYSP_TEMPLATE_CLASS
#undef VECMATRIXADDSP_TEMPLATE_CLASS
#undef VECMATRIXSUBTRACTSP_TEMPLATE_CLASS
#undef VECMATRIXFUNDAMENTALSP_TEMPLATE_CLASS
#undef VECMATRIXCOMPARESP_TEMPLATE_CLASS
#endif // __LOGSCVEC_H