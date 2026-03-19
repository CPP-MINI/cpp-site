#ifndef LAB7_TEMPLATES_MATRIX_HPP
#define LAB7_TEMPLATES_MATRIX_HPP

#include <algorithm>
#include <vector>

template <typename T, size_t Rows = 4, size_t Cols = 4>
class Matrix
{
protected:
    T elements[Rows][Cols] = {};

public:
    Matrix() = default;
    Matrix(std::initializer_list<std::initializer_list<T>> list);

    template <typename T_, size_t Rows_, size_t Cols_>
    friend std::ostream& operator<<(std::ostream &o, const Matrix<T_, Rows_, Cols_> &m);

    Matrix<T, Rows, Cols> operator+(const Matrix<T, Rows, Cols>& other);
    Matrix<T, Rows, Cols> operator-(const Matrix<T, Rows, Cols>& other);

    T* operator[](std::size_t row);
    const T* operator[](std::size_t row) const;

    Matrix<T, Cols, Rows> transpose() const;
};

template<typename T, size_t Rows, size_t Cols>
Matrix<T, Rows, Cols>::Matrix(std::initializer_list<std::initializer_list<T>> list) {
    auto it=list.begin();
    for (int i=0; i<list.size(); i++, it++) {
        std::copy_n(it->begin(), std::min(Cols, it->size()), elements[i]);
    }
}

template<typename T, size_t Rows, size_t Cols>
Matrix<T, Rows, Cols> Matrix<T, Rows, Cols>::operator+(const Matrix<T, Rows, Cols> &other) {
    Matrix<T, Rows, Cols> result;
    for (size_t i = 0; i < Rows; ++i)
        for (size_t j = 0; j < Cols; ++j)
            result[i][j] = elements[i][j] + other[i][j];
    return result;
}

template<typename T, size_t Rows, size_t Cols>
Matrix<T, Rows, Cols> Matrix<T, Rows, Cols>::operator-(const Matrix<T, Rows, Cols> &other) {
    Matrix<T, Rows, Cols> result;
    for (size_t i = 0; i < Rows; ++i)
        for (size_t j = 0; j < Cols; ++j)
            result[i][j] = elements[i][j] - other[i][j];
    return result;
}

template<typename T, size_t Rows, size_t Cols>
const T* Matrix<T, Rows, Cols>::operator[](std::size_t row) const {
    return elements[row];
}

template<typename T, size_t Rows, size_t Cols>
T* Matrix<T, Rows, Cols>::operator[](std::size_t row) {
    return elements[row];
}

template<typename T, size_t Rows, size_t Cols>
Matrix<T, Cols, Rows> Matrix<T, Rows, Cols>::transpose() const {
    Matrix<T, Cols, Rows> result;
    for (std::size_t i = 0; i < Rows; ++i) {
        for (std::size_t j = 0; j < Cols; ++j) {
            result[j][i] = elements[i][j];
        }
    }
    return result;
}

template<typename T, size_t Rows, size_t Cols>
std::ostream &operator<<(std::ostream &o, const Matrix<T, Rows, Cols> &m) {
    for (int row=0; row < Rows; row++) {
        for (int col=0; col < Cols; col++)
            o << m.elements[row][col] << " ";
        o << std::endl;
    }
    return o;
}

#endif //LAB7_TEMPLATES_MATRIX_HPP
