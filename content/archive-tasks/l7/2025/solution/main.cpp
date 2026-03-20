#include <iostream>
#include <format>

#define STAGE_1
#define STAGE_2
#define STAGE_3
#define STAGE_4

// TODO: Include all necessary headers
#include "matrix.hpp"
#include "square_matrix.hpp"


#ifdef STAGE_2
template <typename T, size_t Rows, size_t Cols>
void print_matrix_operator(Matrix<T, Rows, Cols> m1, Matrix<T, Rows, Cols> m2, Matrix<T, Rows, Cols> out, char operator_char) {
    auto formatted_operator = std::format("  {}   ", operator_char);
    for (int row=0; row < Rows; row++) {
        for (int col=0; col < Cols; col++)
            std::cout << m1[row][col] << " ";
        std::cout << (row == Rows / 2 ? formatted_operator : "      ");
        for (int col=0; col < Cols; col++)
            std::cout << m2[row][col] << " ";
        std::cout << (row == Rows / 2 ? "  =   " : "      ");
        for (int col=0; col < Cols; col++)
            std::cout << out[row][col] << " ";
        std::cout << std::endl;
    }
}
#endif

int main() {
#ifdef STAGE_1
    std::cout << "\n--- Stage 1: Matrix template class definition, constructor, operator<< ---" << std::endl;

    Matrix<char, 3, 3> char_matrix = {{'a', 'b', 'c'}, {'d', 'e', 'f'}, {'g', 'h', 'i'}};
    std::cout << "Matrix 3x3 of char from {{'a', 'b', 'c'}, {'d', 'e', 'f'}, {'g', 'h', 'i'}}:" << std::endl;
    std::cout << "---------" << std::endl;
    std::cout << char_matrix;
    std::cout << "---------" << std::endl;

    Matrix<int, 1, 2> int_matrix = {{1001, 1002}};
    std::cout << "Matrix 1x2 of int from {{1001, 1002}}:" << std::endl;
    std::cout << "---------" << std::endl;
    std::cout << int_matrix;
    std::cout << "---------" << std::endl;

    Matrix<float, 3, 1> float_matrix = {{1.1f}, {2.2f}, {3.3f}};
    std::cout << "Matrix 3x1 of float from {{1.1f}, {2.2f}, {3.3f}}:" << std::endl;
    std::cout << "---------" << std::endl;
    std::cout << float_matrix;
    std::cout << "---------" << std::endl;

    Matrix<int, 3, 3> int_matrix_misaligned = {{1, 2, 3}, {4, 5, 6, 7}, {8, 9}, {2}};
    std::cout << "Matrix int 3x3 from {{1, 2, 3}, {4, 5, 6, 7}, {8, 9}, {2}}:" << std::endl;
    std::cout << "---------" << std::endl;
    std::cout << int_matrix_misaligned;
    std::cout << "---------" << std::endl;

    Matrix<char, 3, 2> char_matrix_misaligned = {{'a', 'b', 'c'}, {'d'}};
    std::cout << "Matrix char 3x2 from {{'a', 'b', 'c'}, {'d'}}:" << std::endl;
    std::cout << "---------" << std::endl;
    std::cout << char_matrix_misaligned;
    std::cout << "---------" << std::endl;
#endif

#ifdef STAGE_2
    std::cout << "\n--- Stage 2: Matrix operator[], operator+, operator -, transpose() ---" << std::endl;

    Matrix<float, 2, 3> m1 = {{1, 2, 10}, {4, 5, 2}};
    std::cout << "Matrix m1:" << std::endl;
    std::cout << "---------" << std::endl;
    std::cout << m1;
    std::cout << "---------" << std::endl;
    std::cout << "Element of index (0, 2) of Matrix m1: " << m1[0][2] << std::endl;
    m1[0][2] = 3;
    std::cout << "Matrix m1 after change:" << std::endl;
    std::cout << "---------" << std::endl;
    std::cout << m1;
    std::cout << "---------" << std::endl;
    std::cout << "Element of index (0, 2) of Matrix m1 after change: " << m1[0][2] << std::endl;


    const Matrix<float, 2, 3> m2 = {{1, 0, -1}, {0, -1, 2}};
    std::cout << "Matrix m2:" << std::endl;
    std::cout << "---------" << std::endl;
    std::cout << m2;
    std::cout << "---------" << std::endl;
    std::cout << "Element of index (1, 2) of Matrix m2: " << m2[1][2] << std::endl;

    auto m_result = m1 + m2;
    std::cout << "Operator+ (m1+m2):" << std::endl;
    std::cout << "------------------------------" << std::endl;
    print_matrix_operator(m1, m2, m_result, '+');

    m_result = m1 - m2;
    std::cout << "Operator- (m1-m2):" << std::endl;
    std::cout << "------------------------------" << std::endl;
    print_matrix_operator(m1, m2, m_result, '-');

    std::cout << "Transpose of m_result matrix:" << std::endl;
    std::cout << "---------" << std::endl;
    std::cout << m_result.transpose();
    std::cout << "---------" << std::endl;
#endif

#ifdef STAGE_3
    std::cout << "\n--- Stage 3: SquareMatrix derived class, calculateDeterminant(), getDet(), identity() ---" << std::endl;
    SquareMatrix<float, 3> sq_3 = {{2, 4, 1}, {4, 0, 8}, {6, 4, 2}};
    std::cout << "Square matrix sq_3: " << std::endl;
    std::cout << "---------" << std::endl;
    std::cout << sq_3;
    std::cout << "---------" << std::endl;
    std::cout << "Matrix sq_3 determinant: " << sq_3.getDet() << std::endl;
    std::cout << "Matrix sq_3 transpose: "<< std::endl;
    std::cout << "---------" << std::endl;
    std::cout << sq_3.transpose();
    std::cout << "---------" << std::endl;
    std::cout << "Square matrix 3x3 identity: "<< std::endl;
    auto m_id_3 = SquareMatrix<int, 3>::identity();
    std::cout << "---------" << std::endl;
    std::cout << m_id_3;
#endif

#ifdef STAGE_4
    std::cout << "\n--- Stage 4: SquareMatrix specialization for 2x2 matrices ---" << std::endl;

    SquareMatrix<float, 2> sq_2 = {{1, 2}, {4, 5}};
    std::cout << "Square matrix sq_2: " << std::endl;
    std::cout << "---------" << std::endl;
    std::cout << sq_2;
    std::cout << "---------" << std::endl;
    std::cout << "Matrix sq_2 determinant: " << sq_2.getDet() << std::endl;
    std::cout << "Matrix sq_2 transpose: "<< std::endl;
    std::cout << "---------" << std::endl;
    std::cout << sq_2.transpose();
    std::cout << "---------" << std::endl;

    std::cout << "Square matrix 2x2 identity: "<< std::endl;
    auto m_id_2 = SquareMatrix<int, 2>::identity();
    std::cout << "---------" << std::endl;
    std::cout << m_id_2;
#endif
    return 0;
}