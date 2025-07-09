#include "LogScMatrix.hpp"
namespace LogSc {

    template<typename T, size_t R, size_t C>
    constexpr Matrix<T, R, C>::Matrix() noexcept {
        for (size_t i = 0; i < R * C; ++i) {
            matrix_arr[i] = T{0};
        }
    }
    template<typename T, size_t R, size_t C>
    constexpr Matrix<T, R, C>::Matrix(std::initializer_list<T> init) noexcept {
        size_t i = 0;
        for (const auto& val : init) {
            if (i >= R * C) break;
            matrix_arr[i++] = val;
        }
        for (; i < R * C; ++i) {
            matrix_arr[i] = T{0};
        }
    }
    template<typename T, size_t R, size_t C>
    constexpr Matrix<T, R, C>::Matrix(const Matrix& other) noexcept {
        for (size_t i = 0; i < R * C; ++i)
            matrix_arr[i] = other.matrix_arr[i];
    }
    template<typename T, size_t R, size_t C>
    constexpr Matrix<T, R, C>::Matrix(Matrix&& other) noexcept {
        for (size_t i = 0; i < R * C; ++i) 
            matrix_arr[i] = std::move(other.matrix_arr[i]);
    }
    template<typename T, size_t R, size_t C>
    constexpr Matrix<T, R, C>& Matrix<T, R, C>::operator=(const Matrix& other) noexcept {
        if (this != &other) {
            for (size_t i = 0; i < R * C; ++i) 
                matrix_arr[i] = other.matrix_arr[i];
        }
        return *this;
    }
    template<typename T, size_t R, size_t C>
    constexpr Matrix<T, R, C>& Matrix<T, R, C>::operator=(Matrix&& other) noexcept {
        if (this != &other) {
            for (size_t i = 0; i < R * C; ++i) 
                matrix_arr[i] = std::move(other.matrix_arr[i]);
        }
        return *this;
    }
};