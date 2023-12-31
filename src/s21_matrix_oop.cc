#include "s21_matrix_oop.h"

namespace s_21 {
// CONSTRUCTORS

S21Matrix::S21Matrix() : S21Matrix(5, 5){};

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument(
        "CreationError: The number of rows or cols cannot be less than 1");
  }
  AllocateMemory();
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  AllocateMemory();
  CopyValues(other);
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

// ASSIGNMENT OPERATORS

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    FreeMemory();
    rows_ = other.rows_;
    cols_ = other.cols_;
    AllocateMemory();
    CopyValues(other);
  }

  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this != &other) {
    FreeMemory();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;

    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }

  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

// DESTRUCTOR

S21Matrix::~S21Matrix() { FreeMemory(); }

// GETTERS AND SETTERS

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetRows(int rows) {
  if (rows <= 0) {
    throw std::invalid_argument(
        "SettingRowsError: The number of rows cannot be less than 1");
  }

  S21Matrix tmp(rows, cols_);
  int rows_range = rows < rows_ ? rows : rows_;
  for (int i = 0; i < rows_range; i++) {
    for (int j = 0; j < cols_; j++) {
      tmp.matrix_[i][j] = matrix_[i][j];
    }
  }

  *this = tmp;
}

void S21Matrix::SetCols(int cols) {
  if (cols <= 0) {
    throw std::invalid_argument(
        "SettingColsError: The number of cols cannot be less than 1");
  }

  S21Matrix tmp(rows_, cols);
  int cols_range = cols < cols_ ? cols : cols_;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_range; j++) {
      tmp.matrix_[i][j] = matrix_[i][j];
    }
  }

  *this = tmp;
}

// OVERLOAD OPERATORS

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix res_matrix(*this);
  res_matrix.SumMatrix(other);
  return res_matrix;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix res_matrix(*this);
  res_matrix.SubMatrix(other);
  return res_matrix;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix res_matrix(*this);
  res_matrix.MulMatrix(other);
  return res_matrix;
}

S21Matrix S21Matrix::operator*(double num) const {
  S21Matrix res_matrix(*this);
  res_matrix.MulNumber(num);
  return res_matrix;
}

S21Matrix operator*(double num, S21Matrix& matrix) { return matrix * num; }

bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); }

double& S21Matrix::operator()(int row, int col) {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_) {
    throw std::out_of_range("InvalidIndexError: Index is out of range");
  }

  return matrix_[row][col];
}

double& S21Matrix::operator()(int row, int col) const {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_) {
    throw std::out_of_range("InvalidIndexError: Index is out of range");
  }

  return matrix_[row][col];
}

// MEMBER FUNCTIONS

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  return std::memcmp(matrix_ + rows_, other.matrix_ + rows_, rows_ * cols_) ==
             0 &&
         IsMatrixSameDimension(other);
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (!IsMatrixSameDimension(other)) {
    throw std::range_error("SumMatrixError: Matrices of different dimensions");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (!IsMatrixSameDimension(other)) {
    throw std::range_error("SubMatrixError: Matrices of different dimensions");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::range_error(
        "MulMatrixError: Incorrect dimensions to multiply two matrices");
  }

  S21Matrix res_matrix(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      double sum = 0;
      for (int k = 0; k < cols_; k++) {
        sum += matrix_[i][k] * other.matrix_[k][j];
      }
      res_matrix.matrix_[i][j] = sum;
    }
  }

  *this = res_matrix;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix transposed_matrix(cols_, rows_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      transposed_matrix.matrix_[j][i] = matrix_[i][j];
    }
  }

  return transposed_matrix;
}

S21Matrix S21Matrix::CalcComplements() {
  if (!IsMatrixSquare()) {
    throw std::range_error("CalcComplementsError: The matrix must be square");
  }

  S21Matrix res_matrix(rows_, cols_);
  if (rows_ == 1) {
    res_matrix.matrix_[0][0] = matrix_[0][0];
  } else {
    for (int i = 0; i < rows_; i++) {
      int sign = i % 2 == 0 ? 1 : -1;
      for (int j = 0; j < cols_; j++) {
        S21Matrix minor(Minor(i, j));
        res_matrix.matrix_[i][j] = sign * minor.Determinant();
        sign = -sign;
      }
    }
  }

  return res_matrix;
}

double S21Matrix::Determinant() {
  if (!IsMatrixSquare()) {
    throw std::range_error("DeterminantError: The matrix must be square");
  }

  double det = 0;
  if (rows_ == 1) {
    det = matrix_[0][0];
  } else if (rows_ == 2) {
    det = matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
  } else {
    int sign = 1;
    for (int i = 0; i < cols_; i++) {
      S21Matrix minor(Minor(0, i));
      det += sign * matrix_[0][i] * minor.Determinant();
      sign = -sign;
    }
  }

  return det;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();
  if (!Determinant() || !IsMatrixSquare()) {
    throw std::range_error(
        "InverseError: Incompatible matrix sizes to search inverse matrix");
  }

  S21Matrix res_matrix(rows_, cols_);
  if (rows_ == 1) {
    res_matrix.matrix_[0][0] = 1.0 / matrix_[0][0];
  } else {
    res_matrix = CalcComplements().Transpose();
    res_matrix.MulNumber(1 / det);
  }

  return res_matrix;
}

// PRIVATE MEMBER FUNCTIONS

void S21Matrix::AllocateMemory() {
  // allocating one block of memory for everything at once
  matrix_ = new double*[rows_ + rows_ * cols_]();
  // pointer to start values ​​after pointers
  double* start = (double*)(matrix_ + rows_);
  // indexing our matrix
  int iteration_limit = rows_ <= cols_ ? cols_ : rows_;
  for (int i = 0; i < iteration_limit; i++) {
    matrix_[i] = start + i * cols_;
  }
  std::memset(start, 0, rows_ * cols_);
}

void S21Matrix::FreeMemory() {
  if (matrix_) {
    delete[] matrix_;
  }
}

void S21Matrix::CopyValues(const S21Matrix& other) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix S21Matrix::Minor(int ex_row, int ex_col) {
  S21Matrix minor(rows_ - 1, cols_ - 1);

  for (int i = 0, minor_row = 0; i < rows_; i++) {
    if (i != ex_row) {
      for (int j = 0, minor_col = 0; j < cols_; j++) {
        if (j != ex_col) {
          minor.matrix_[minor_row][minor_col] = matrix_[i][j];
          minor_col++;
        }
      }
      minor_row++;
    }
  }

  return minor;
}

bool S21Matrix::IsMatrixSameDimension(S21Matrix matrix) {
  return (rows_ == matrix.rows_ && cols_ == matrix.cols_);
}

bool S21Matrix::IsMatrixSquare() { return (cols_ == rows_); }

}  // namespace s_21
