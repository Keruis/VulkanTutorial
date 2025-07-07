#ifndef __LOGSCMATRIX_H
#define __LOGSCMATRIX_H
#include <cstddef>

namespace LogSc {
template<typename T, size_t R,size_t C>class Matrix;
template<size_t Rows, size_t Cols> using MatrixShort      = LogSc::Matrix<short, Rows, Cols>;
template<size_t Rows, size_t Cols> using MatrixInt        = LogSc::Matrix<int, Rows, Cols>;
template<size_t Rows, size_t Cols> using MatrixFloat      = LogSc::Matrix<float, Rows, Cols>;
template<size_t Rows, size_t Cols> using MatrixDouble     = LogSc::Matrix<double, Rows, Cols>;
template<size_t Rows, size_t Cols> using MatrixLong       = LogSc::Matrix<long, Rows, Cols>;
template<size_t Rows, size_t Cols> using MatrixLongLong   = LogSc::Matrix<long long, Rows, Cols>;

template<typename T, size_t R, size_t C>
class Matrix
{
protected:
    T matrix_arr[R][C];
public:
    static constexpr size_t Rows = R;
    static constexpr size_t Cols = C;

    // 构造和析构
    Matrix() noexcept;
    Matrix(std::initializer_list<std::initializer_list<T>> init) noexcept;
    Matrix(const Matrix& other) noexcept;
    Matrix(Matrix&& other) noexcept;
    Matrix& operator=(const Matrix& other) noexcept;
    Matrix& operator=(Matrix&& other) noexcept;
    ~Matrix() = default;

    // 取值
    inline T&       operator()(size_t row, size_t col) noexcept          {return matrix_arr[row][col];}
    inline const T& operator()(size_t row, size_t col) const noexcept    {return matrix_arr[row][col];}
    inline T*       operator[](size_t rc)              noexcept          {return matrix_arr[rc];      }
    inline const T* operator[](size_t rc)              const noexcept    {return matrix_arr[rc];      }

    // 不要了
    Matrix operator*() = delete;
    bool operator==(const Matrix&) const = delete;
    bool operator!=(const Matrix&) const = delete;

    // 产生新的
    inline Matrix operator++(int) noexcept {
        Matrix temp = *this;
        ++(*this);
        return temp;
    }
    inline Matrix operator--(int) noexcept {
        Matrix temp = *this;
        --(*this);
        return temp;
    }
    inline Matrix operator+() const noexcept {
        return *this;
    }
    inline Matrix operator-() const noexcept {
        Matrix result = *this;
        for (size_t i = 0; i < R; ++i)
            for (size_t j = 0; j < C; ++j)
                result.matrix_arr[i][j] = -result.matrix_arr[i][j];
        return result;
    }

    // 不产生新的
    inline Matrix& operator+=(const Matrix& rhs) noexcept {
        for (size_t i = 0; i < R; ++i)
            for (size_t j = 0; j < C; ++j)
                matrix_arr[i][j] += rhs.matrix_arr[i][j];
        return *this;
    }
    inline Matrix& operator-=(const Matrix& rhs) noexcept {
        for (size_t i = 0; i < R; ++i)
            for (size_t j = 0; j < C; ++j)
                matrix_arr[i][j] -= rhs.matrix_arr[i][j];
        return *this;
    }
    inline Matrix& operator+=(const T& scalar) noexcept {
        for (size_t i = 0; i < R; ++i)
            for (size_t j = 0; j < C; ++j)
                matrix_arr[i][j] += scalar;
        return *this;
    }
    inline Matrix& operator-=(const T& scalar) noexcept {
        for (size_t i = 0; i < R; ++i)
            for (size_t j = 0; j < C; ++j)
                matrix_arr[i][j] -= scalar;
        return *this;
    }
    inline Matrix& operator*=(const T& scalar) noexcept {
        for (size_t i = 0; i < R; ++i)
            for (size_t j = 0; j < C; ++j)
                matrix_arr[i][j] *= scalar;
        return *this;
    }
    inline Matrix& operator/=(const T& scalar) noexcept {
        for (size_t i = 0; i < R; ++i)
            for (size_t j = 0; j < C; ++j)
                matrix_arr[i][j] /= scalar;
        return *this;
    }
    inline Matrix& operator++() noexcept {
        return (*this += static_cast<T>(1));
    }
    inline Matrix& operator--() noexcept {
        return (*this -= static_cast<T>(1));
    }
};
/* ---- 乘法通用 ---- */
template<typename T, size_t C1, size_t C2, size_t C3>
constexpr void _multiply(const Matrix<T, C1, C2>& lhs, const Matrix<T, C2, C3>& rhs, Matrix<T, C1, C3>& result) noexcept{
    for (size_t i = 0; i < C1; ++i)
        for (size_t j = 0; j < C3; ++j)
            result[i][j] = T{0};
    for (size_t i = 0; i < C1; ++i)
        for (size_t k = 0; k < C2; ++k)
            for (size_t j = 0; j < C3; ++j)
                result[i][j] += lhs[i][k] * rhs[k][j];
}
/* ---- 乘法泛化 ---- */
template<typename T, size_t C1, size_t C2, size_t C3>
struct MatrixMultiplySp {
    constexpr static void multiply(const Matrix<T, C1, C2>& lhs, const Matrix<T, C2, C3>& rhs, Matrix<T, C1, C3>& result) noexcept{
        printf("generalization %dx%d x %dx%d -> %dx%d\n",C1,C2,C2,C3,C1,C3);
        _multiply(lhs,rhs,result);
    }
};
/* ---- 乘法重载 ---- */
template<typename T, size_t C1, size_t C2, size_t C3>
constexpr Matrix<T, C1, C3> operator*(const Matrix<T, C1, C2>& lhs, const Matrix<T, C2, C3>& rhs) noexcept {
    Matrix<T, C1, C3> result;
    LogSc::MatrixMultiplySp<T,C1,C2,C3>::multiply(lhs,rhs,result);
    return result;
}
/* ----  乘法特化 ---- */
#define MATRIXMULTIPLYSP_TEMPLATE_CLASS(C1,C2,C3) \
template<typename T>\
struct MatrixMultiplySp<T, C1, C2, C3> {\
    constexpr static void multiply(const Matrix<T, C1, C2>& lhs, const Matrix<T, C2, C3>& rhs, Matrix<T, C1, C3>& result) noexcept;\
};
MATRIXMULTIPLYSP_TEMPLATE_CLASS(2,2,2) // 1.  2×2 × 2×2 -> 2×2
MATRIXMULTIPLYSP_TEMPLATE_CLASS(2,2,3) // 2.  2×2 × 2×3 -> 2×3
MATRIXMULTIPLYSP_TEMPLATE_CLASS(2,2,4) // 3.  2×2 × 2×4 -> 2×4
MATRIXMULTIPLYSP_TEMPLATE_CLASS(2,3,2) // 4.  2×3 × 3×2 -> 2×2
MATRIXMULTIPLYSP_TEMPLATE_CLASS(2,3,3) // 5.  2×3 × 3×3 -> 2×3
MATRIXMULTIPLYSP_TEMPLATE_CLASS(2,3,4) // 6.  2×3 × 3×4 -> 2×4
MATRIXMULTIPLYSP_TEMPLATE_CLASS(2,4,2) // 7.  2×4 × 4×2 -> 2×2
MATRIXMULTIPLYSP_TEMPLATE_CLASS(2,4,3) // 8.  2×4 × 4×3 -> 2×3
MATRIXMULTIPLYSP_TEMPLATE_CLASS(2,4,4) // 9.  2×4 × 4×4 -> 2×4
MATRIXMULTIPLYSP_TEMPLATE_CLASS(3,2,2) // 10. 3×2 × 2×2 -> 3×2
MATRIXMULTIPLYSP_TEMPLATE_CLASS(3,2,3) // 11. 3×2 × 2×3 -> 3×3
MATRIXMULTIPLYSP_TEMPLATE_CLASS(3,2,4) // 12. 3×2 × 2×4 -> 3×4
MATRIXMULTIPLYSP_TEMPLATE_CLASS(3,3,2) // 13. 3×3 × 3×2 -> 3×2
MATRIXMULTIPLYSP_TEMPLATE_CLASS(3,3,3) // 14. 3×3 × 3×3 -> 3×3
MATRIXMULTIPLYSP_TEMPLATE_CLASS(3,3,4) // 15. 3×3 × 3×4 -> 3×4
MATRIXMULTIPLYSP_TEMPLATE_CLASS(3,4,2) // 16. 3×4 × 4×2 -> 3×2
MATRIXMULTIPLYSP_TEMPLATE_CLASS(3,4,3) // 17. 3×4 × 4×3 -> 3×3
MATRIXMULTIPLYSP_TEMPLATE_CLASS(3,4,4) // 18. 3×4 × 4×4 -> 3×4
MATRIXMULTIPLYSP_TEMPLATE_CLASS(4,2,2) // 19. 4×2 × 2×2 -> 4×2
MATRIXMULTIPLYSP_TEMPLATE_CLASS(4,2,3) // 20. 4×2 × 2×3 -> 4×3
MATRIXMULTIPLYSP_TEMPLATE_CLASS(4,2,4) // 21. 4×2 × 2×4 -> 4×4
MATRIXMULTIPLYSP_TEMPLATE_CLASS(4,3,2) // 22. 4×3 × 3×2 -> 4×2
MATRIXMULTIPLYSP_TEMPLATE_CLASS(4,3,3) // 23. 4×3 × 3×3 -> 4×3
MATRIXMULTIPLYSP_TEMPLATE_CLASS(4,3,4) // 24. 4×3 × 3×4 -> 4×4
MATRIXMULTIPLYSP_TEMPLATE_CLASS(4,4,2) // 25. 4×4 × 4×2 -> 4×2
MATRIXMULTIPLYSP_TEMPLATE_CLASS(4,4,3) // 26. 4×4 × 4×3 -> 4×3
MATRIXMULTIPLYSP_TEMPLATE_CLASS(4,4,4) // 27. 4×4 × 4×4 -> 4×4

/* ---- 除法通用 ---- */
template<typename T, size_t C1, size_t C2>
constexpr void _divide(const Matrix<T, C1, C2>& lhs, const Matrix<T, C2, C2>& rhs, Matrix<T, C1, C2>& result) noexcept {
    Matrix<T, C2, C2> tmp = rhs;
    Matrix<T, C2, C2> rhsInv;
    for (size_t i = 0; i < C2; ++i)
        for (size_t j = 0; j < C2; ++j)
            rhsInv[i][j] = (i == j) ? T{1} : T{0};
    for (size_t i = 0; i < C2; ++i) {
        size_t pivot = i;
        for (size_t r = i + 1; r < C2; ++r) {
            if (std::abs(tmp[r][i]) > std::abs(tmp[pivot][i])) {
                pivot = r;
            }
        }
        if (tmp[pivot][i] == T{0}) {
            for (size_t i = 0; i < C1; ++i) {
                for (size_t j = 0; j < C2; ++j) {
                    result[i][j] = T{0};
                }
            }
            return ;
        }
        if (pivot != i) {
            for (size_t c = 0; c < C2; ++c) {
                std::swap(tmp[i][c], tmp[pivot][c]);
                std::swap(rhsInv[i][c], rhsInv[pivot][c]);
            }
        }
        T pivotVal = tmp[i][i];
        for (size_t c = 0; c < C2; ++c) {
            tmp[i][c] /= pivotVal;
            rhsInv[i][c] /= pivotVal;
        }
        for (size_t r = 0; r < C2; ++r) {
            if (r == i) continue;
            T factor = tmp[r][i];
            for (size_t c = 0; c < C2; ++c) {
                tmp[r][c] -= factor * tmp[i][c];
                rhsInv[r][c] -= factor * rhsInv[i][c];
            }
        }
    }
    for (size_t i = 0; i < C1; ++i) {
        for (size_t j = 0; j < C2; ++j) {
            T sum = T{0};
            for (size_t k = 0; k < C2; ++k) {
                sum += lhs[i][k] * rhsInv[k][j];
            }
            result[i][j] = sum;
        }
    }
}
/* ---- 除法泛化 ---- */
template<typename T, size_t C1, size_t C2>
struct MatrixDivideSp {
    constexpr static void divide(const Matrix<T, C1, C2>& lhs, const Matrix<T, C2, C2>& rhs, Matrix<T, C1, C2>& result) noexcept{
        printf("generalization %dx%d / %dx%d -> %dx%d\n",C1,C2,C2,C2,C1,C2);
        _divide(lhs,rhs,result);
    }
};
/* ---- 除法重载 ---- */
template<typename T, size_t C1, size_t C2>
constexpr Matrix<T, C1, C2> operator/(const Matrix<T, C1, C2>& lhs, const Matrix<T, C2, C2>& rhs) noexcept{
    Matrix<T, C1, C2> result;
    LogSc::MatrixDivideSp<T,C1,C2>::divide(lhs,rhs,result);
    return result;
}
/* ---- 除法特化 ---- */
// NULL TEMPLATE CLASS

/* ---- 加法通用 ---- */
template<typename T, size_t C1,size_t C2>
constexpr void _add(const Matrix<T, C1, C2>& lhs, const Matrix<T, C1, C2>& rhs, Matrix<T, C1, C2>& result) noexcept{
    for (size_t i = 0; i < C1; ++i) 
        for (size_t j = 0; j < C2; ++j)
            result[i][j] = lhs[i][j] + rhs[i][j];
}
/* ---- 加法泛化 ---- */
template<typename T, size_t C1, size_t C2>
struct MatrixAddSp {
    constexpr static void add(const Matrix<T, C1, C2>& lhs, const Matrix<T, C1, C2>& rhs, Matrix<T, C1, C2>& result) noexcept{
        printf("generalization %dx%d + %dx%d -> %dx%d\n",C1,C2,C1,C2,C1,C2);
        _add(lhs,rhs,result);
    }
};
/* ---- 加法重载 ---- */
template<typename T, size_t C1, size_t C2>
constexpr Matrix<T, C1, C2> operator+(const Matrix<T, C1, C2>& lhs, const Matrix<T, C1, C2>& rhs) noexcept{
    Matrix<T, C1, C2> result;
    LogSc::MatrixAddSp<T,C1,C2>::add(lhs,rhs,result);
    return result;
}
/* ---- 加法特化 ---- */
#define MATRIXADDSP_TEMPLATE_CLASS(C1,C2) \
template<typename T>\
struct MatrixAddSp<T, C1, C2> {\
    constexpr static void add(const Matrix<T, C1, C2>& lhs, const Matrix<T, C1, C2>& rhs, Matrix<T, C1, C2>& result) noexcept;\
};
MATRIXADDSP_TEMPLATE_CLASS(2, 2)
MATRIXADDSP_TEMPLATE_CLASS(2, 3)
MATRIXADDSP_TEMPLATE_CLASS(2, 4)
MATRIXADDSP_TEMPLATE_CLASS(3, 2)
MATRIXADDSP_TEMPLATE_CLASS(3, 3)
MATRIXADDSP_TEMPLATE_CLASS(3, 4)
MATRIXADDSP_TEMPLATE_CLASS(4, 2)
MATRIXADDSP_TEMPLATE_CLASS(4, 3)
MATRIXADDSP_TEMPLATE_CLASS(4, 4)

/* ---- 减法通用 ---- */
template<typename T, size_t C1,size_t C2>
constexpr void _subtract(const Matrix<T, C1, C2>& lhs, const Matrix<T, C1, C2>& rhs, Matrix<T, C1, C2>& result) noexcept{
    for (size_t i = 0; i < C1; ++i) 
        for (size_t j = 0; j < C2; ++j)
            result[i][j] = lhs[i][j] - rhs[i][j];
}
/* ---- 减法泛化 ---- */
template<typename T, size_t C1, size_t C2>
struct MatrixSubtractSp {
    constexpr static void subtract(const Matrix<T, C1, C2>& lhs, const Matrix<T, C1, C2>& rhs, Matrix<T, C1, C2>& result) noexcept{
        printf("generalization %dx%d - %dx%d -> %dx%d\n",C1,C2,C1,C2,C1,C2);
        _subtract(lhs,rhs,result);
    }
};
/* ---- 减法重载 ---- */
template<typename T, size_t C1, size_t C2>
constexpr Matrix<T, C1, C2> operator-(const Matrix<T, C1, C2>& lhs, const Matrix<T, C1, C2>& rhs) noexcept{
    Matrix<T, C1, C2> result;
    LogSc::MatrixSubtractSp<T,C1,C2>::subtract(lhs,rhs,result);
    return result;
}
/* ---- 减法特化 ---- */
#define MATRIXSUBTRACTSP_TEMPLATE_CLASS(C1,C2) \
template<typename T>\
struct MatrixSubtractSp<T, C1, C2> {\
    constexpr static void subtract(const Matrix<T, C1, C2>& lhs, const Matrix<T, C1, C2>& rhs, Matrix<T, C1, C2>& result) noexcept;\
};
MATRIXSUBTRACTSP_TEMPLATE_CLASS(2, 2)
MATRIXSUBTRACTSP_TEMPLATE_CLASS(2, 3)
MATRIXSUBTRACTSP_TEMPLATE_CLASS(2, 4)
MATRIXSUBTRACTSP_TEMPLATE_CLASS(3, 2)
MATRIXSUBTRACTSP_TEMPLATE_CLASS(3, 3)
MATRIXSUBTRACTSP_TEMPLATE_CLASS(3, 4)
MATRIXSUBTRACTSP_TEMPLATE_CLASS(4, 2)
MATRIXSUBTRACTSP_TEMPLATE_CLASS(4, 3)
MATRIXSUBTRACTSP_TEMPLATE_CLASS(4, 4)

};

#include "LogScMatrix.tpp"
#include "LogScMatrixAdd.tpp"
#include "LogScMatrixSubtract.tpp"
#include "LogScMatrixMultiply.tpp"

#endif // __LOGSCMATRIX_H

