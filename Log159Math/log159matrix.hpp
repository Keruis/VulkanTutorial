#ifndef __MATRIX_H
#define __MATRIX_H
#include <cstddef>
namespace LogSc {

template<typename T, size_t R,size_t C>class Matrix;
template<int Rows, int Cols> using MatrixShort      = LogSc::Matrix<short, Rows, Cols>;
template<int Rows, int Cols> using MatrixInt        = LogSc::Matrix<int, Rows, Cols>;
template<int Rows, int Cols> using MatrixFloat      = LogSc::Matrix<float, Rows, Cols>;
template<int Rows, int Cols> using MatrixDouble     = LogSc::Matrix<double, Rows, Cols>;
template<int Rows, int Cols> using MatrixLong       = LogSc::Matrix<long, Rows, Cols>;
template<int Rows, int Cols> using MatrixLongLong   = LogSc::Matrix<long long, Rows, Cols>;

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
    inline T*       operator[](size_t rc)             noexcept         {return matrix_arr[rc];}
    inline const T* operator[](size_t rc)             const noexcept   {return matrix_arr[rc];}
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
// operator*
template<typename T, size_t R, size_t C, size_t K>
Matrix<T, R, K> operator*(const Matrix<T, R, C>& lhs, const Matrix<T, C, K>& rhs) {
    Matrix<T, R, K> result;
    for (size_t i = 0; i < R; ++i)
        for (size_t k = 0; k < C; ++k)
            for (size_t j = 0; j < K; ++j)
                result[i][j] += lhs[i][k] * rhs[k][j];
    return result;
}
// 乘法通用方法
template<typename T, size_t R, size_t C, size_t K>
void multiply(const Matrix<T, R, C>& lhs, const Matrix<T, C, K>& rhs, Matrix<T, R, K>& result) {
    std::fill(&result[0][0], &result[0][0] + R * K, T{0});
    for (size_t i = 0; i < R; ++i)
        for (size_t k = 0; k < C; ++k)
            for (size_t j = 0; j < K; ++j)
                result[i][j] += lhs[i][k] * rhs[k][j];
}

template<typename T, size_t C1, size_t C2, size_t C3>
struct MatrixSp {
    static void multiply(const Matrix<T, C1, C2>& lhs, const Matrix<T, C2, C3>& rhs, Matrix<T, C1, C3>& result) {
        multiply(lhs,rhs,result);
    }
};

// 1. 2×2 × 2×2 → 2×2
template<typename T>
struct MatrixSp<T, 2, 2, 2> {
    static void multiply(const Matrix<T, 2, 2>& lhs, const Matrix<T, 2, 2>& rhs, Matrix<T, 2, 2>& result) {
        result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0];
        result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1];
        result[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0];
        result[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1];
    }
};
// 2. 2×2 × 2×3 → 2×3
template<typename T>
struct MatrixSp<T, 2, 2, 3> {
    static void multiply(const Matrix<T, 2, 2>& lhs, const Matrix<T, 2, 3>& rhs, Matrix<T, 2, 3>& result) {
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2];
        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2];
    }
};
// 3. 2×2 × 2×4 → 2×4
template<typename T>
struct MatrixSp<T, 2, 2, 4> {
    static void multiply(const Matrix<T, 2, 2>& lhs, const Matrix<T, 2, 4>& rhs, Matrix<T, 2, 4>& result) {
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2];
        result[0][3] = lhs[0][0]*rhs[0][3] + lhs[0][1]*rhs[1][3];
        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2];
        result[1][3] = lhs[1][0]*rhs[0][3] + lhs[1][1]*rhs[1][3];
    }
};
// 4. 2×3 × 3×2 → 2×2
template<typename T>
struct MatrixSp<T, 2, 3, 2> {
    static void multiply(const Matrix<T, 2, 3>& lhs, const Matrix<T, 3, 2>& rhs, Matrix<T, 2, 2>& result) {
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1];
        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1];
    }
};
// 5. 2×3 × 3×3 → 2×3
template<typename T>
struct MatrixSp<T, 2, 3, 3> {
    static void multiply(const Matrix<T, 2, 3>& lhs, const Matrix<T, 3, 3>& rhs, Matrix<T, 2, 3>& result) {
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2] + lhs[0][2]*rhs[2][2];
        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2] + lhs[1][2]*rhs[2][2];
    }
};
// 6. 2×3 × 3×4 → 2×4
template<typename T>
struct MatrixSp<T, 2, 3, 4> {
    static void multiply(const Matrix<T, 2, 3>& lhs, const Matrix<T, 3, 4>& rhs, Matrix<T, 2, 4>& result) {
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2] + lhs[0][2]*rhs[2][2];
        result[0][3] = lhs[0][0]*rhs[0][3] + lhs[0][1]*rhs[1][3] + lhs[0][2]*rhs[2][3];
        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2] + lhs[1][2]*rhs[2][2];
        result[1][3] = lhs[1][0]*rhs[0][3] + lhs[1][1]*rhs[1][3] + lhs[1][2]*rhs[2][3];
    }
};
// 7. 2×4 × 4×2 → 2×2
template<typename T>
struct MatrixSp<T, 2, 4, 2> {
    static void multiply(const Matrix<T, 2, 4>& lhs, const Matrix<T, 4, 2>& rhs, Matrix<T, 2, 2>& result) {
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0] + lhs[0][3]*rhs[3][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1] + lhs[0][3]*rhs[3][1];
        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0] + lhs[1][3]*rhs[3][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1] + lhs[1][3]*rhs[3][1];
    }
};
// 8. 2×4 × 4×3 → 2×3
template<typename T>
struct MatrixSp<T, 2, 4, 3> {
    static void multiply(const Matrix<T, 2, 4>& lhs, const Matrix<T, 4, 3>& rhs, Matrix<T, 2, 3>& result) {
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0] + lhs[0][3]*rhs[3][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1] + lhs[0][3]*rhs[3][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2] + lhs[0][2]*rhs[2][2] + lhs[0][3]*rhs[3][2];
        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0] + lhs[1][3]*rhs[3][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1] + lhs[1][3]*rhs[3][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2] + lhs[1][2]*rhs[2][2] + lhs[1][3]*rhs[3][2];
    }
};
// 9. 2×4 × 4×4 → 2×4
template<typename T>
struct MatrixSp<T, 2, 4, 4> {
    static void multiply(const Matrix<T, 2, 4>& lhs, const Matrix<T, 4, 4>& rhs, Matrix<T, 2, 4>& result) {
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0] + lhs[0][3]*rhs[3][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1] + lhs[0][3]*rhs[3][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2] + lhs[0][2]*rhs[2][2] + lhs[0][3]*rhs[3][2];
        result[0][3] = lhs[0][0]*rhs[0][3] + lhs[0][1]*rhs[1][3] + lhs[0][2]*rhs[2][3] + lhs[0][3]*rhs[3][3];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0] + lhs[1][3]*rhs[3][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1] + lhs[1][3]*rhs[3][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2] + lhs[1][2]*rhs[2][2] + lhs[1][3]*rhs[3][2];
        result[1][3] = lhs[1][0]*rhs[0][3] + lhs[1][1]*rhs[1][3] + lhs[1][2]*rhs[2][3] + lhs[1][3]*rhs[3][3];
    }
};
// 10. 3×2 × 2×2 → 3×2
template<typename T>
struct MatrixSp<T, 3, 2, 2> {
    static void multiply(const Matrix<T, 3, 2>& lhs, const Matrix<T, 2, 2>& rhs, Matrix<T, 3, 2>& result) {
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1];
        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1];
        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1];
    }
};
// 11. 3×2 × 2×3 → 3×3
template<typename T>
struct MatrixSp<T, 3, 2, 3> {
    static void multiply(const Matrix<T, 3, 2>& lhs, const Matrix<T, 2, 3>& rhs, Matrix<T, 3, 3>& result) {
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2];
        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2];
        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1];
        result[2][2] = lhs[2][0]*rhs[0][2] + lhs[2][1]*rhs[1][2];
    }
};
// 12. 3×2 × 2×4 → 3×4
template<typename T>
struct MatrixSp<T, 3, 2, 4> {
    static void multiply(const Matrix<T, 3, 2>& lhs, const Matrix<T, 2, 4>& rhs, Matrix<T, 3, 4>& result) {
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2];
        result[0][3] = lhs[0][0]*rhs[0][3] + lhs[0][1]*rhs[1][3];
        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2];
        result[1][3] = lhs[1][0]*rhs[0][3] + lhs[1][1]*rhs[1][3];
        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1];
        result[2][2] = lhs[2][0]*rhs[0][2] + lhs[2][1]*rhs[1][2];
        result[2][3] = lhs[2][0]*rhs[0][3] + lhs[2][1]*rhs[1][3];
    }
};
// 13. 3×3 × 3×2 → 3×2
template<typename T>
struct MatrixSp<T, 3, 3, 2> {
    static void multiply(const Matrix<T, 3, 3>& lhs, const Matrix<T, 3, 2>& rhs, Matrix<T, 3, 2>& result) {
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1];
        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1];
        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0] + lhs[2][2]*rhs[2][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1] + lhs[2][2]*rhs[2][1];
    }
};
// 14. 3×3 × 3×3 → 3×3
template<typename T>
struct MatrixSp<T, 3, 3, 3> {
    static void multiply(const Matrix<T, 3, 3>& lhs, const Matrix<T, 3, 3>& rhs, Matrix<T, 3, 3>& result) {
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2] + lhs[0][2]*rhs[2][2];
        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2] + lhs[1][2]*rhs[2][2];
        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0] + lhs[2][2]*rhs[2][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1] + lhs[2][2]*rhs[2][1];
        result[2][2] = lhs[2][0]*rhs[0][2] + lhs[2][1]*rhs[1][2] + lhs[2][2]*rhs[2][2];
    }
};
// 15. 3×3 × 3×4 → 3×4
template<typename T>
struct MatrixSp<T, 3, 3, 4> {
    static void multiply(const Matrix<T, 3, 3>& lhs, const Matrix<T, 3, 4>& rhs, Matrix<T, 3, 4>& result) {
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2] + lhs[0][2]*rhs[2][2];
        result[0][3] = lhs[0][0]*rhs[0][3] + lhs[0][1]*rhs[1][3] + lhs[0][2]*rhs[2][3];
        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2] + lhs[1][2]*rhs[2][2];
        result[1][3] = lhs[1][0]*rhs[0][3] + lhs[1][1]*rhs[1][3] + lhs[1][2]*rhs[2][3];
        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0] + lhs[2][2]*rhs[2][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1] + lhs[2][2]*rhs[2][1];
        result[2][2] = lhs[2][0]*rhs[0][2] + lhs[2][1]*rhs[1][2] + lhs[2][2]*rhs[2][2];
        result[2][3] = lhs[2][0]*rhs[0][3] + lhs[2][1]*rhs[1][3] + lhs[2][2]*rhs[2][3];
    }
};
// 16. 3×4 × 4×2 → 3×2
template<typename T>
struct MatrixSp<T, 3, 4, 2> {
    static void multiply(const Matrix<T, 3, 4>& lhs, const Matrix<T, 4, 2>& rhs, Matrix<T, 3, 2>& result) {
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0] + lhs[0][3]*rhs[3][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1] + lhs[0][3]*rhs[3][1];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0] + lhs[1][3]*rhs[3][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1] + lhs[1][3]*rhs[3][1];

        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0] + lhs[2][2]*rhs[2][0] + lhs[2][3]*rhs[3][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1] + lhs[2][2]*rhs[2][1] + lhs[2][3]*rhs[3][1];
    }
};
// 17. 3×4 × 4×3 → 3×3
template<typename T>
struct MatrixSp<T, 3, 4, 3> {
    static void multiply(const Matrix<T, 3, 4>& lhs, const Matrix<T, 4, 3>& rhs, Matrix<T, 3, 3>& result) {
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0] + lhs[0][3]*rhs[3][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1] + lhs[0][3]*rhs[3][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2] + lhs[0][2]*rhs[2][2] + lhs[0][3]*rhs[3][2];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0] + lhs[1][3]*rhs[3][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1] + lhs[1][3]*rhs[3][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2] + lhs[1][2]*rhs[2][2] + lhs[1][3]*rhs[3][2];

        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0] + lhs[2][2]*rhs[2][0] + lhs[2][3]*rhs[3][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1] + lhs[2][2]*rhs[2][1] + lhs[2][3]*rhs[3][1];
        result[2][2] = lhs[2][0]*rhs[0][2] + lhs[2][1]*rhs[1][2] + lhs[2][2]*rhs[2][2] + lhs[2][3]*rhs[3][2];
    }
};
// 18. 3×4 × 4×4 → 3×4
template<typename T>
struct MatrixSp<T, 3, 4, 4> {
    static void multiply(const Matrix<T, 3, 4>& lhs, const Matrix<T, 4, 4>& rhs, Matrix<T, 3, 4>& result) {
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0] + lhs[0][3]*rhs[3][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1] + lhs[0][3]*rhs[3][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2] + lhs[0][2]*rhs[2][2] + lhs[0][3]*rhs[3][2];
        result[0][3] = lhs[0][0]*rhs[0][3] + lhs[0][1]*rhs[1][3] + lhs[0][2]*rhs[2][3] + lhs[0][3]*rhs[3][3];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0] + lhs[1][3]*rhs[3][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1] + lhs[1][3]*rhs[3][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2] + lhs[1][2]*rhs[2][2] + lhs[1][3]*rhs[3][2];
        result[1][3] = lhs[1][0]*rhs[0][3] + lhs[1][1]*rhs[1][3] + lhs[1][2]*rhs[2][3] + lhs[1][3]*rhs[3][3];

        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0] + lhs[2][2]*rhs[2][0] + lhs[2][3]*rhs[3][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1] + lhs[2][2]*rhs[2][1] + lhs[2][3]*rhs[3][1];
        result[2][2] = lhs[2][0]*rhs[0][2] + lhs[2][1]*rhs[1][2] + lhs[2][2]*rhs[2][2] + lhs[2][3]*rhs[3][2];
        result[2][3] = lhs[2][0]*rhs[0][3] + lhs[2][1]*rhs[1][3] + lhs[2][2]*rhs[2][3] + lhs[2][3]*rhs[3][3];
    }
};
// 19. 4×2 × 2×2 → 4×2
template<typename T>
struct MatrixSp<T, 4, 2, 2> {
    static void multiply(const Matrix<T, 4, 2>& lhs, const Matrix<T, 2, 2>& rhs, Matrix<T, 4, 2>& result) {
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1];

        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1];

        result[3][0] = lhs[3][0]*rhs[0][0] + lhs[3][1]*rhs[1][0];
        result[3][1] = lhs[3][0]*rhs[0][1] + lhs[3][1]*rhs[1][1];
    }
};
// 20. 4×2 × 2×3 → 4×3
template<typename T>
struct MatrixSp<T, 4, 2, 3> {
    static void multiply(const Matrix<T, 4, 2>& lhs, const Matrix<T, 2, 3>& rhs, Matrix<T, 4, 3>& result) {
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2];

        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1];
        result[2][2] = lhs[2][0]*rhs[0][2] + lhs[2][1]*rhs[1][2];

        result[3][0] = lhs[3][0]*rhs[0][0] + lhs[3][1]*rhs[1][0];
        result[3][1] = lhs[3][0]*rhs[0][1] + lhs[3][1]*rhs[1][1];
        result[3][2] = lhs[3][0]*rhs[0][2] + lhs[3][1]*rhs[1][2];
    }
};
// 21. 4×2 × 2×4 → 4×4
template<typename T>
struct MatrixSp<T, 4, 2, 4> {
    static void multiply(const Matrix<T, 4, 2>& lhs, const Matrix<T, 2, 4>& rhs, Matrix<T, 4, 4>& result) {
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2];
        result[0][3] = lhs[0][0]*rhs[0][3] + lhs[0][1]*rhs[1][3];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2];
        result[1][3] = lhs[1][0]*rhs[0][3] + lhs[1][1]*rhs[1][3];

        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1];
        result[2][2] = lhs[2][0]*rhs[0][2] + lhs[2][1]*rhs[1][2];
        result[2][3] = lhs[2][0]*rhs[0][3] + lhs[2][1]*rhs[1][3];

        result[3][0] = lhs[3][0]*rhs[0][0] + lhs[3][1]*rhs[1][0];
        result[3][1] = lhs[3][0]*rhs[0][1] + lhs[3][1]*rhs[1][1];
        result[3][2] = lhs[3][0]*rhs[0][2] + lhs[3][1]*rhs[1][2];
        result[3][3] = lhs[3][0]*rhs[0][3] + lhs[3][1]*rhs[1][3];
    }
};
// 22. 4×3 × 3×2 → 4×2
template<typename T>
struct MatrixSp<T, 4, 3, 2> {
    static void multiply(const Matrix<T, 4, 3>& lhs, const Matrix<T, 3, 2>& rhs, Matrix<T, 4, 2>& result) {
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1];

        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0] + lhs[2][2]*rhs[2][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1] + lhs[2][2]*rhs[2][1];

        result[3][0] = lhs[3][0]*rhs[0][0] + lhs[3][1]*rhs[1][0] + lhs[3][2]*rhs[2][0];
        result[3][1] = lhs[3][0]*rhs[0][1] + lhs[3][1]*rhs[1][1] + lhs[3][2]*rhs[2][1];
    }
};
// 23. 4×3 × 3×3 → 4×3
template<typename T>
struct MatrixSp<T, 4, 3, 3> {
    static void multiply(const Matrix<T, 4, 3>& lhs, const Matrix<T, 3, 3>& rhs, Matrix<T, 4, 3>& result) {
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2] + lhs[0][2]*rhs[2][2];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2] + lhs[1][2]*rhs[2][2];

        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0] + lhs[2][2]*rhs[2][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1] + lhs[2][2]*rhs[2][1];
        result[2][2] = lhs[2][0]*rhs[0][2] + lhs[2][1]*rhs[1][2] + lhs[2][2]*rhs[2][2];

        result[3][0] = lhs[3][0]*rhs[0][0] + lhs[3][1]*rhs[1][0] + lhs[3][2]*rhs[2][0];
        result[3][1] = lhs[3][0]*rhs[0][1] + lhs[3][1]*rhs[1][1] + lhs[3][2]*rhs[2][1];
        result[3][2] = lhs[3][0]*rhs[0][2] + lhs[3][1]*rhs[1][2] + lhs[3][2]*rhs[2][2];
    }
};
// 24. 4×3 × 3×4 → 4×4
template<typename T>
struct MatrixSp<T, 4, 3, 4> {
    static void multiply(const Matrix<T, 4, 3>& lhs, const Matrix<T, 3, 4>& rhs, Matrix<T, 4, 4>& result) {
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2] + lhs[0][2]*rhs[2][2];
        result[0][3] = lhs[0][0]*rhs[0][3] + lhs[0][1]*rhs[1][3] + lhs[0][2]*rhs[2][3];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2] + lhs[1][2]*rhs[2][2];
        result[1][3] = lhs[1][0]*rhs[0][3] + lhs[1][1]*rhs[1][3] + lhs[1][2]*rhs[2][3];

        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0] + lhs[2][2]*rhs[2][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1] + lhs[2][2]*rhs[2][1];
        result[2][2] = lhs[2][0]*rhs[0][2] + lhs[2][1]*rhs[1][2] + lhs[2][2]*rhs[2][2];
        result[2][3] = lhs[2][0]*rhs[0][3] + lhs[2][1]*rhs[1][3] + lhs[2][2]*rhs[2][3];

        result[3][0] = lhs[3][0]*rhs[0][0] + lhs[3][1]*rhs[1][0] + lhs[3][2]*rhs[2][0];
        result[3][1] = lhs[3][0]*rhs[0][1] + lhs[3][1]*rhs[1][1] + lhs[3][2]*rhs[2][1];
        result[3][2] = lhs[3][0]*rhs[0][2] + lhs[3][1]*rhs[1][2] + lhs[3][2]*rhs[2][2];
        result[3][3] = lhs[3][0]*rhs[0][3] + lhs[3][1]*rhs[1][3] + lhs[3][2]*rhs[2][3];
    }
};
// 25. 4×4 × 4×2 → 4×2
template<typename T>
struct MatrixSp<T, 4, 4, 2> {
    static void multiply(const Matrix<T, 4, 4>& lhs, const Matrix<T, 4, 2>& rhs, Matrix<T, 4, 2>& result) {
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0] + lhs[0][3]*rhs[3][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1] + lhs[0][3]*rhs[3][1];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0] + lhs[1][3]*rhs[3][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1] + lhs[1][3]*rhs[3][1];

        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0] + lhs[2][2]*rhs[2][0] + lhs[2][3]*rhs[3][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1] + lhs[2][2]*rhs[2][1] + lhs[2][3]*rhs[3][1];

        result[3][0] = lhs[3][0]*rhs[0][0] + lhs[3][1]*rhs[1][0] + lhs[3][2]*rhs[2][0] + lhs[3][3]*rhs[3][0];
        result[3][1] = lhs[3][0]*rhs[0][1] + lhs[3][1]*rhs[1][1] + lhs[3][2]*rhs[2][1] + lhs[3][3]*rhs[3][1];
    }
};
// 26. 4×4 × 4×3 → 4×3
template<typename T>
struct MatrixSp<T, 4, 4, 3> {
    static void multiply(const Matrix<T, 4, 4>& lhs, const Matrix<T, 4, 3>& rhs, Matrix<T, 4, 3>& result) {
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0] + lhs[0][3]*rhs[3][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1] + lhs[0][3]*rhs[3][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2] + lhs[0][2]*rhs[2][2] + lhs[0][3]*rhs[3][2];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0] + lhs[1][3]*rhs[3][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1] + lhs[1][3]*rhs[3][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2] + lhs[1][2]*rhs[2][2] + lhs[1][3]*rhs[3][2];

        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0] + lhs[2][2]*rhs[2][0] + lhs[2][3]*rhs[3][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1] + lhs[2][2]*rhs[2][1] + lhs[2][3]*rhs[3][1];
        result[2][2] = lhs[2][0]*rhs[0][2] + lhs[2][1]*rhs[1][2] + lhs[2][2]*rhs[2][2] + lhs[2][3]*rhs[3][2];

        result[3][0] = lhs[3][0]*rhs[0][0] + lhs[3][1]*rhs[1][0] + lhs[3][2]*rhs[2][0] + lhs[3][3]*rhs[3][0];
        result[3][1] = lhs[3][0]*rhs[0][1] + lhs[3][1]*rhs[1][1] + lhs[3][2]*rhs[2][1] + lhs[3][3]*rhs[3][1];
        result[3][2] = lhs[3][0]*rhs[0][2] + lhs[3][1]*rhs[1][2] + lhs[3][2]*rhs[2][2] + lhs[3][3]*rhs[3][2];
    }
};
// 27. 4×4 × 4×4 → 4×4
template<typename T>
struct MatrixSp<T, 4, 4, 4> {
    static void multiply(const Matrix<T, 4, 4>& lhs, const Matrix<T, 4, 4>& rhs, Matrix<T, 4, 4>& result) {
        result[0][0] = lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0] + lhs[0][3]*rhs[3][0];
        result[0][1] = lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1] + lhs[0][3]*rhs[3][1];
        result[0][2] = lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2] + lhs[0][2]*rhs[2][2] + lhs[0][3]*rhs[3][2];
        result[0][3] = lhs[0][0]*rhs[0][3] + lhs[0][1]*rhs[1][3] + lhs[0][2]*rhs[2][3] + lhs[0][3]*rhs[3][3];

        result[1][0] = lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0] + lhs[1][3]*rhs[3][0];
        result[1][1] = lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1] + lhs[1][3]*rhs[3][1];
        result[1][2] = lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2] + lhs[1][2]*rhs[2][2] + lhs[1][3]*rhs[3][2];
        result[1][3] = lhs[1][0]*rhs[0][3] + lhs[1][1]*rhs[1][3] + lhs[1][2]*rhs[2][3] + lhs[1][3]*rhs[3][3];

        result[2][0] = lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0] + lhs[2][2]*rhs[2][0] + lhs[2][3]*rhs[3][0];
        result[2][1] = lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1] + lhs[2][2]*rhs[2][1] + lhs[2][3]*rhs[3][1];
        result[2][2] = lhs[2][0]*rhs[0][2] + lhs[2][1]*rhs[1][2] + lhs[2][2]*rhs[2][2] + lhs[2][3]*rhs[3][2];
        result[2][3] = lhs[2][0]*rhs[0][3] + lhs[2][1]*rhs[1][3] + lhs[2][2]*rhs[2][3] + lhs[2][3]*rhs[3][3];

        result[3][0] = lhs[3][0]*rhs[0][0] + lhs[3][1]*rhs[1][0] + lhs[3][2]*rhs[2][0] + lhs[3][3]*rhs[3][0];
        result[3][1] = lhs[3][0]*rhs[0][1] + lhs[3][1]*rhs[1][1] + lhs[3][2]*rhs[2][1] + lhs[3][3]*rhs[3][1];
        result[3][2] = lhs[3][0]*rhs[0][2] + lhs[3][1]*rhs[1][2] + lhs[3][2]*rhs[2][2] + lhs[3][3]*rhs[3][2];
        result[3][3] = lhs[3][0]*rhs[0][3] + lhs[3][1]*rhs[1][3] + lhs[3][2]*rhs[2][3] + lhs[3][3]*rhs[3][3];
    }
};
};
#endif

