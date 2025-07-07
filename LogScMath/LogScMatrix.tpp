#include "LogScMatrix.hpp"
namespace LogSc {

    template<typename T, size_t R, size_t C>
    Matrix<T, R, C>::Matrix() noexcept {
        std::fill(&matrix_arr[0][0], &matrix_arr[0][0] + R * C, T{0});
    }
    template<typename T, size_t R, size_t C>
    Matrix<T, R, C>::Matrix(std::initializer_list<std::initializer_list<T>> init) noexcept {
        std::size_t i = 0;
        for (const auto& row : init) {
            std::copy(row.begin(), row.end(), matrix_arr[i++]);
        }
    }
    template<typename T, size_t R, size_t C>
    Matrix<T, R, C>::Matrix(const Matrix& other) noexcept {
        *this = other;
    }
    template<typename T, size_t R, size_t C>
    Matrix<T, R, C>::Matrix(Matrix&& other) noexcept {
        *this = std::move(other);
    }
    template<typename T, size_t R, size_t C>
    Matrix<T, R, C>& Matrix<T, R, C>::operator=(const Matrix& other) noexcept {
        if (this != &other) {
            for (size_t i = 0; i < R; ++i) {
                std::copy(other.matrix_arr[i], other.matrix_arr[i] + C, matrix_arr[i]);
            }
        }
        return *this;
    }
    template<typename T, size_t R, size_t C>
    Matrix<T, R, C>& Matrix<T, R, C>::operator=(Matrix&& other) noexcept {
        if (this != &other) {
            for (size_t i = 0; i < R; ++i) {
                for (size_t j = 0; j < C; ++j) {
                    matrix_arr[i][j] = std::move(other.matrix_arr[i][j]);
                }
            }
        }
        return *this;
    }
};