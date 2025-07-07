#ifndef __LOGSCVEC_H
#define __LOGSCVEC_H
#include "LogScMatrix.hpp"

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
class Vec: public Matrix<T, 1, C>
{
public:
    Vec() noexcept :Matrix<T, 1, C>(){}
    Vec(std::initializer_list<T> init)noexcept :Matrix<T, 1, C>({init}){}
    ~Vec() = default;

};
/// -------------- 针对向量 和 矩阵 --------------

/* ---- 乘法通用 ---- */
template<typename T, size_t C1, size_t C2>
constexpr void __multiply_vc(const Vec<T, C1>& lhs, const Matrix<T, C1, C2>& rhs, Vec<T,C2>& result) noexcept{
    std::fill(&result[0][0], &result[0][0] + 1 * C2, T{0});
    for (size_t j = 0; j < C2; ++j) {
        for (size_t i = 0; i < C1; ++i) {
            result[0][j] += lhs[0][i] * rhs[i][j];
        }
    }
};
/* ---- 乘法泛化 ---- */
template<typename T, size_t C1, size_t C2>
struct VecMatrixMultiplySp {
    constexpr static void multiply(const Vec<T, C1>& lhs, const Matrix<T, C1, C2>& rhs, Vec<T,C2>& result) noexcept{
        printf("generalization vec %dx%d x %dx%d -> %dx%d\n",1,C1,C1,C2,1,C2);
        __multiply_vc(lhs,rhs,result);
    }
};
/* ---- 乘法重载 ---- */
template<typename T, size_t C1, size_t C2>
constexpr Vec<T,C2> operator*(const Vec<T, C1>& lhs, const Matrix<T, C1, C2>& rhs) noexcept {
    Vec<T,C2> result;
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

/// -------------- 针对向量 和 向量 --------------
/* ---- 加法通用 ---- */
template<typename T, size_t C1>
constexpr void __add_vec(const Vec<T, C1>& lhs, const Vec<T, C1>& rhs, Vec<T, C1>& result) noexcept {
    for (size_t i = 0; i < C1; ++i)
        result[0][i] = lhs[0][i] + rhs[0][i];
}
/* ---- 加法泛化 ---- */
template<typename T, size_t C1>
struct VecMatrixAddSp {
    constexpr static void add(const Vec<T, C1>& lhs, const Vec<T, C1>& rhs, Vec<T, C1>& result) noexcept{
        printf("generalization %dx%d + %dx%d -> %dx%d\n",1,C1,1,C1,1,C1);
        __add_vec(lhs,rhs,result);
    }
};
/* ---- 加法重载 ---- */
template<typename T, size_t C1>
constexpr Vec<T, C1> operator+(const Vec<T, C1>& lhs, const Vec<T, C1>& rhs) noexcept{
    Vec<T, C1> result;
    LogSc::VecMatrixAddSp<T,C1>::add(lhs,rhs,result);
    return result;
}
/* ---- 加法特化 ---- */
#define VECMATRIXADDSP_TEMPLATE_CLASS(C1) \
template<typename T>\
struct VecMatrixAddSp<T, C1> {\
    constexpr static void add(const Vec<T, C1>& lhs, const Vec<T, C1>& rhs, Vec<T, C1>& result) noexcept;\
};
VECMATRIXADDSP_TEMPLATE_CLASS(2)
VECMATRIXADDSP_TEMPLATE_CLASS(3)
VECMATRIXADDSP_TEMPLATE_CLASS(4)

/* ---- 减法通用 ---- */
template<typename T, size_t C1>
constexpr void __subtract_vec(const Vec<T, C1>& lhs, const Vec<T, C1>& rhs, Vec<T, C1>& result) noexcept {
    for (size_t i = 0; i < C1; ++i) 
        result[0][i] = lhs[0][i] - rhs[0][i];
}
/* ---- 减法泛化 ---- */
template<typename T, size_t C1>
struct VecMatrixSubtractSp {
    constexpr static void subtract(const Vec<T, C1>& lhs, const Vec<T, C1>& rhs, Vec<T, C1>& result) noexcept{
        printf("generalization %dx%d - %dx%d -> %dx%d\n",1,C1,1,C1,1,C1);
        __subtract_vec(lhs,rhs,result);
    }
};
/* ---- 减法重载 ---- */
template<typename T, size_t C1>
constexpr Vec<T, C1> operator-(const Vec<T, C1>& lhs, const Vec<T, C1>& rhs) noexcept{
    Vec<T, C1> result;
    LogSc::VecMatrixSubtractSp<T,C1>::subtract(lhs,rhs,result);
    return result;
}
/* ---- 加法特化 ---- */
#define VECMATRIXSUBTRACTSP_TEMPLATE_CLASS(C1) \
template<typename T>\
struct VecMatrixSubtractSp<T, C1> {\
    constexpr static void subtract(const Vec<T, C1>& lhs, const Vec<T, C1>& rhs, Vec<T, C1>& result) noexcept;\
};
VECMATRIXSUBTRACTSP_TEMPLATE_CLASS(2)
VECMATRIXSUBTRACTSP_TEMPLATE_CLASS(3)
VECMATRIXSUBTRACTSP_TEMPLATE_CLASS(4)


};
#include "LogScVecAdd.tpp"
#include "LogScVecSubtract.tpp"
#include "LogScVecMultiply.tpp"

#endif // __LOGSCVEC_H