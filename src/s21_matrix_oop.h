//  created by sheritsh // Oleg Polovinko ※ School 21, Kzn

#ifndef CPP1_S21_MATRIXPLUS_SRC_S21_MATRIX_OOP_H_
#define CPP1_S21_MATRIXPLUS_SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <cstring>
#include <iostream>

namespace s_21 {
class S21Matrix {
 public:
  // Constructors

  S21Matrix();
  /**
   * @throws CreationError: The number of rows or cols cannot be less than 1
   */
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;

  // Assignment operators

  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other) noexcept;
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);

  // Destructor

  ~S21Matrix();

  // Getters and setters

  int GetRows() const;
  int GetCols() const;
  /**
   * @throws SettingRowsError: The number of rows cannot be less than 1
   */
  void SetRows(int rows);
  /**
   * @throws SettingColsError: The number of cols cannot be less than 1
   */
  void SetCols(int cols);

  // Overload operators

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(double num) const;
  friend S21Matrix operator*(double, S21Matrix& matrix);
  bool operator==(const S21Matrix& other);
  /**
   * @throws InvalidIndexError: Index is out of range
   */
  double& operator()(int row, int col);
  /**
   * @throws InvalidIndexError: Index is out of range
   */
  double& operator()(int row, int col) const;

  // Member functions

  bool EqMatrix(const S21Matrix& other);
  /**
   * @throws SumMatrixError: Matrices of different dimensions
   */
  void SumMatrix(const S21Matrix& other);
  /**
   * @throws SubMatrixError: Matrices of different dimensions
   */
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  /**
   * @throws MulMatrixError: Incorrect dimensions to multiply two matrices
   */
  void MulMatrix(const S21Matrix& other);

  S21Matrix Transpose();
  /**
   * @throws CalcComplementsError: The matrix must be square
   */
  S21Matrix CalcComplements();
  /**
   * @throws DeterminantError: The matrix must be square
   */
  double Determinant();
  /**
   * @throws InverseError: Incompatible matrix sizes to search inverse matrix
   */
  S21Matrix InverseMatrix();

 private:
  int rows_, cols_;
  double** matrix_;

  void AllocateMemory();
  void FreeMemory();
  void CopyValues(const S21Matrix& other);
  S21Matrix Minor(int ex_row, int ex_col);
  bool IsMatrixSameDimension(S21Matrix matrix);
  bool IsMatrixSquare();
};
}  // namespace s_21

#endif  // CPP1_S21_MATRIXPLUS_SRC_S21_MATRIX_OOP_H_