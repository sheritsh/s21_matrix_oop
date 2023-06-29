#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_

#include <cmath>
#include <cstring>
#include <iostream>

constexpr double EPS = 1e-7;

namespace s_21 {
class S21Matrix {
 public:
  // Constructors
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;

  // Assignment operators
  S21Matrix& operator=(const S21Matrix& other) noexcept;
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(double num);

  // Destructor
  ~S21Matrix();

  // Getter and setter
  int getRows() const;
  int getCols() const;
  void setRows(int rows);
  void setCols(int cols);

  // Overload operators
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(double num) const;
  bool operator==(const S21Matrix& other);

  // Member functions
  bool EqMatrix(const S21Matrix& other);
  /**
   * @brief sum of two matrices
   * @throw different matrix dimensions
   */
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);

  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

 private:
  int rows_, cols_;
  double** matrix_;
  S21Matrix Minor(int ex_row, int ex_col);
  void AllocateMemory();
  void FreeMemory();
};
}  // namespace s_21

#endif  // S21_MATRIX_OOP_H_