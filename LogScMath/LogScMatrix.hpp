#ifndef __MATRIX_H
#define __MATRIX_H
#include <cstddef>
namespace LogSc {
template<typename T, size_t R,size_t C>class Matrix;
template<size_t Rows, size_t Cols> using MatrixShort      = LogSc::Matrix<short, Rows, Cols>;
template<size_t Rows, size_t Cols> using MatrixInt        = LogSc::Matrix<int, Rows, Cols>;
template<size_t Rows, size_t Cols> using MatrixFloat      = LogSc::Matrix<float, Rows, Cols>;
template<size_t Rows, size_t Cols> using MatrixDouble     = LogSc::Matrix<double, Rows, Cols>;
template<size_t Rows, size_t Cols> using MatrixLong       = LogSc::Matrix<long, Rows, Cols>;
template<size_t Rows, size_t Cols> using MatrixLongLong   = LogSc::Matrix<long long, Rows, Cols>;

template<typename T, size_t R,size_t C>
class Matrix
{
private:
    T matrix_arr[R][C];
public:
    static constexpr const size_t Rows = R;
    static constexpr const size_t Cols = C;

public:
    Matrix() noexcept {
        std::fill(&matrix_arr[0][0], &matrix_arr[0][0] + R * C, T{0});
    }
    Matrix(std::initializer_list<std::initializer_list<T>> init) noexcept{
        if (init.size() > R) throw std::out_of_range("Too many rows");
        std::size_t i = 0;
        for (const auto& row : init) {
            if (row.size() > C) throw std::out_of_range("Too many columns");
            std::copy(row.begin(), row.end(), matrix_arr[i++]);
        }
    }
    Matrix(const Matrix& other) noexcept {
        *this = other;
    }
    Matrix(Matrix&& other) noexcept {
        *this = std::move(other);
    }
    Matrix& operator=(const Matrix& other) noexcept {
        if (this != &other) {
            for (size_t i = 0; i < R; ++i) {
                std::copy(other.matrix_arr[i], other.matrix_arr[i] + C, matrix_arr[i]);
            }
        }
        return *this;
    }
    Matrix& operator=(Matrix&& other) noexcept {
        if (this != &other) {
            for (size_t i = 0; i < R; ++i) {
                for (size_t j = 0; j < C; ++j) {
                    matrix_arr[i][j] = std::move(other.matrix_arr[i][j]);
                }
            }
        }
        return *this;
    }
    ~Matrix() = default;
    inline T&       operator()(size_t row, size_t col) noexcept          {return matrix_arr[row][col];}
    inline const T& operator()(size_t row, size_t col) const noexcept    {return matrix_arr[row][col];}
    inline T*       operator[](size_t rc)              noexcept          {return matrix_arr[rc];      }
    inline const T* operator[](size_t rc)              const noexcept    {return matrix_arr[rc];      }
};
/* ---- 乘法通用 ---- */
template<typename T, size_t R, size_t C, size_t K>
constexpr void _multiply(const Matrix<T, R, C>& lhs, const Matrix<T, C, K>& rhs, Matrix<T, R, K>& result) {
    std::fill(&result[0][0], &result[0][0] + R * K, T{0});
    for (size_t i = 0; i < R; ++i)
        for (size_t k = 0; k < C; ++k)
            for (size_t j = 0; j < K; ++j)
                result[i][j] += lhs[i][k] * rhs[k][j];
}
/* ---- 乘法泛化 ---- */
template<typename T, size_t C1, size_t C2, size_t C3>
struct MatrixMultiplySp {
    static void multiply(const Matrix<T, C1, C2>& lhs, const Matrix<T, C2, C3>& rhs, Matrix<T, C1, C3>& result) {
        printf("generalization %dx%d x %dx%d -> %dx%d\n",C1,C2,C2,C3,C1,C3);
        _multiply(lhs,rhs,result);
    }
};
/* ---- 乘法重载 ---- */
template<typename T, size_t C1, size_t C2, size_t C3>
Matrix<T, C1, C3> operator*(const Matrix<T, C1, C2>& lhs, const Matrix<T, C2, C3>& rhs) {
    Matrix<T, C1, C3> result;
    LogSc::MatrixMultiplySp<T,C1,C2,C3>::multiply(lhs,rhs,result);
    return result;
}
/* ----  乘法特化 ---- */
#define MATRIXMULTIPLYSP_TEMPLATE_CLASS(C1,C2,C3) \
template<typename T>\
struct MatrixMultiplySp<T, C1, C2, C3> {\
    static void multiply(const Matrix<T, C1, C2>& lhs, const Matrix<T, C2, C3>& rhs, Matrix<T, C1, C3>& result);\
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

/* ---- 加法通用 ---- */
template<typename T, size_t C1,size_t C2>
constexpr void _addition(const Matrix<T, C1, C2>& lhs, const Matrix<T, C1, C2>& rhs, Matrix<T, C1, C2>& result){
    for (size_t i = 0; i < C1; ++i) 
        for (size_t j = 0; j < C2; ++j)
            result[i][j] = lhs[i][j] + rhs[i][j];
}
/* ---- 加法泛化 ---- */
template<typename T, size_t C1, size_t C2>
struct MatrixAdditionSp {
    static void addition(const Matrix<T, C1, C2>& lhs, const Matrix<T, C1, C2>& rhs, Matrix<T, C1, C2>& result) {
        printf("generalization %dx%d + %dx%d -> %dx%d\n",C1,C2,C1,C2,C1,C2);
        _addition(lhs,rhs,result);
    }
};
/* ---- 加法重载 ---- */
template<typename T, size_t C1, size_t C2>
Matrix<T, C1, C2> operator+(const Matrix<T, C1, C2>& lhs, const Matrix<T, C1, C2>& rhs) {
    Matrix<T, C1, C2> result;
    LogSc::MatrixAdditionSp<T,C1,C2>::addition(lhs,rhs,result);
    return result;
}
/* ---- 加法特化 ---- */
#define MATRIXADDITIONSP_TEMPLATE_CLASS(C1,C2) \
template<typename T>\
struct MatrixAdditionSp<T, C1, C2> {\
    static void addition(const Matrix<T, C1, C2>& lhs, const Matrix<T, C1, C2>& rhs, Matrix<T, C1, C2>& result);\
};
MATRIXADDITIONSP_TEMPLATE_CLASS(2, 2)
MATRIXADDITIONSP_TEMPLATE_CLASS(2, 3)
MATRIXADDITIONSP_TEMPLATE_CLASS(2, 4)
MATRIXADDITIONSP_TEMPLATE_CLASS(3, 2)
MATRIXADDITIONSP_TEMPLATE_CLASS(3, 3)
MATRIXADDITIONSP_TEMPLATE_CLASS(3, 4)
MATRIXADDITIONSP_TEMPLATE_CLASS(4, 2)
MATRIXADDITIONSP_TEMPLATE_CLASS(4, 3)
MATRIXADDITIONSP_TEMPLATE_CLASS(4, 4)

};

#include "LogScMatrixMultiply.tpp"
#include "LogScMatrixAddition.tpp"
#endif

