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
public:
    static constexpr const size_t Rows = R;
    static constexpr const size_t Cols = C;
private:
    T matrix_arr[R][C];
public:
    Matrix() {
        std::fill(&matrix_arr[0][0], &matrix_arr[0][0] + R * C, T{0});
    }
    Matrix(std::initializer_list<std::initializer_list<T>> init) {
        if (init.size() > R) throw std::out_of_range("Too many rows");
        std::size_t i = 0;
        for (const auto& row : init) {
            if (row.size() > C) throw std::out_of_range("Too many columns");
            std::copy(row.begin(), row.end(), matrix_arr[i++]);
        }
    }
    ~Matrix()=default;
    inline T&       operator()(size_t row, size_t col) noexcept         {return matrix_arr[row][col];}
    inline const T& operator()(size_t row, size_t col) const noexcept   {return matrix_arr[row][col];}
    inline T*       operator[](size_t rc)             noexcept          {return matrix_arr[rc];}
    inline const T* operator[](size_t rc)             const noexcept    {return matrix_arr[rc];}
    // print matrix
    void print() const {
        for (size_t i = 0; i < R; ++i) {
            for (size_t j = 0; j < C; ++j) {
                std::cout << matrix_arr[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }
};
// print matrix
template<typename T, size_t R, size_t C>
void printMatrix(const Matrix<T, R, C>& mat) {
    for (size_t i = 0; i < R; ++i) {
        for (size_t j = 0; j < C; ++j) {
            std::cout << mat[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

// 乘法通用方法
template<typename T, size_t R, size_t C, size_t K>
void _multiply(const Matrix<T, R, C>& lhs, const Matrix<T, C, K>& rhs, Matrix<T, R, K>& result) {
    std::fill(&result[0][0], &result[0][0] + R * K, T{0});
    for (size_t i = 0; i < R; ++i)
        for (size_t k = 0; k < C; ++k)
            for (size_t j = 0; j < K; ++j)
                result[i][j] += lhs[i][k] * rhs[k][j];
}
// 矩阵泛化版本
template<typename T, size_t C1, size_t C2, size_t C3>
struct MatrixSp {
    static void multiply(const Matrix<T, C1, C2>& lhs, const Matrix<T, C2, C3>& rhs, Matrix<T, C1, C3>& result) {
        printf("generalization %dx%d x %dx%d -> %dx%d\n",C1,C2,C2,C3,C1,C3);
        _multiply(lhs,rhs,result);
    }
};
// operator*
template<typename T, size_t C1, size_t C2, size_t C3>
Matrix<T, C1, C3> operator*(const Matrix<T, C1, C2>& lhs, const Matrix<T, C2, C3>& rhs) {
    Matrix<T, C1, C3> result;
    LogSc::MatrixSp<T,C1,C2,C3>::multiply(lhs,rhs,result);
    return result;
}

// 矩阵特化版本
#define MS_TEMPLATE_CLASS(C1,C2,C3) \
template<typename T>\
struct MatrixSp<T, C1, C2, C3> {\
    static void multiply(const Matrix<T, C1, C2>& lhs, const Matrix<T, C2, C3>& rhs, Matrix<T, C1, C3>& result);\
};
//static void addition(const Matrix<T, C1, C2>& lhs, const Matrix<T, C2, C3>& rhs, Matrix<T, C1, C3>& result);
MS_TEMPLATE_CLASS(2,2,2) // 1.  2×2 × 2×2 -> 2×2
MS_TEMPLATE_CLASS(2,2,3) // 2.  2×2 × 2×3 -> 2×3
MS_TEMPLATE_CLASS(2,2,4) // 3.  2×2 × 2×4 -> 2×4
MS_TEMPLATE_CLASS(2,3,2) // 4.  2×3 × 3×2 -> 2×2
MS_TEMPLATE_CLASS(2,3,3) // 5.  2×3 × 3×3 -> 2×3
MS_TEMPLATE_CLASS(2,3,4) // 6.  2×3 × 3×4 -> 2×4
MS_TEMPLATE_CLASS(2,4,2) // 7.  2×4 × 4×2 -> 2×2
MS_TEMPLATE_CLASS(2,4,3) // 8.  2×4 × 4×3 -> 2×3
MS_TEMPLATE_CLASS(2,4,4) // 9.  2×4 × 4×4 -> 2×4
MS_TEMPLATE_CLASS(3,2,2) // 10. 3×2 × 2×2 -> 3×2
MS_TEMPLATE_CLASS(3,2,3) // 11. 3×2 × 2×3 -> 3×3
MS_TEMPLATE_CLASS(3,2,4) // 12. 3×2 × 2×4 -> 3×4
MS_TEMPLATE_CLASS(3,3,2) // 13. 3×3 × 3×2 -> 3×2
MS_TEMPLATE_CLASS(3,3,3) // 14. 3×3 × 3×3 -> 3×3
MS_TEMPLATE_CLASS(3,3,4) // 15. 3×3 × 3×4 -> 3×4
MS_TEMPLATE_CLASS(3,4,2) // 16. 3×4 × 4×2 -> 3×2
MS_TEMPLATE_CLASS(3,4,3) // 17. 3×4 × 4×3 -> 3×3
MS_TEMPLATE_CLASS(3,4,4) // 18. 3×4 × 4×4 -> 3×4
MS_TEMPLATE_CLASS(4,2,2) // 19. 4×2 × 2×2 -> 4×2
MS_TEMPLATE_CLASS(4,2,3) // 20. 4×2 × 2×3 -> 4×3
MS_TEMPLATE_CLASS(4,2,4) // 21. 4×2 × 2×4 -> 4×4
MS_TEMPLATE_CLASS(4,3,2) // 22. 4×3 × 3×2 -> 4×2
MS_TEMPLATE_CLASS(4,3,3) // 23. 4×3 × 3×3 -> 4×3
MS_TEMPLATE_CLASS(4,3,4) // 24. 4×3 × 3×4 -> 4×4
MS_TEMPLATE_CLASS(4,4,2) // 25. 4×4 × 4×2 -> 4×2
MS_TEMPLATE_CLASS(4,4,3) // 26. 4×4 × 4×3 -> 4×3
MS_TEMPLATE_CLASS(4,4,4) // 27. 4×4 × 4×4 -> 4×4

};

#include "log159matrix.tpp"
#endif

