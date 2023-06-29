#include "s21_matrix_oop.h"

namespace s_21 {
// Constructors

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
  std::memcpy(matrix_, other.matrix_, rows_ + rows_ * cols_);
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

// Assignment operators

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    FreeMemory();
    rows_ = other.rows_;
    cols_ = other.cols_;
    AllocateMemory();
    std::memcpy(matrix_, other.matrix_, rows_ + rows_ * cols_);
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

S21Matrix& S21Matrix::operator*=(double num) {
  MulNumber(num);
  return *this;
}

// Destructor

S21Matrix::~S21Matrix() {
  FreeMemory();
  rows_ = 0;
  cols_ = 0;
}

// Getters and setters

int S21Matrix::getRows() const { return rows_; }

int S21Matrix::getCols() const { return cols_; }

void S21Matrix::setRows(int rows) {
  if (rows <= 0) {
    throw std::out_of_range(
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

void S21Matrix::setCols(int cols) {
  if (cols <= 0) {
    throw std::out_of_range(
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

// Overload operators

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

bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); }

double& S21Matrix::operator()(int row, int col) {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_) {
    throw std::out_of_range("InvalidIndexError: index is out of range");
  }

  return matrix_[row][col];
}

double S21Matrix::operator()(int row, int col) const {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_) {
    throw std::out_of_range("InvalidIndexError: index is out of range");
  }

  return matrix_[row][col];
}

// Member functions

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  return std::memcmp(matrix_, other.matrix_, rows_ + rows_ * cols_) == 0
             ? true
             : false;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (!IsMatrixSameDimension) {
    throw std::out_of_range("SumMatrixError: Matrices of different dimensions");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (!IsMatrixSameDimension) {
    throw std::out_of_range("SubMatrixError: Matrices of different dimensions");
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
    throw std::invalid_argument(
        "MultMatrixError: Incorrect dimensions to multiply two matrices");
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

S21Matrix S21Matrix::CalcComplements() {}

double S21Matrix::Determinant() {}

S21Matrix S21Matrix::InverseMatrix() {}

// Private member functions

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
}

void S21Matrix::FreeMemory() {
  if (matrix_) {
    delete[] matrix_;
  }
}

bool S21Matrix::IsMatrixSameDimension(S21Matrix first_matrix,
                                      S21Matrix second_matrix) {
  return (first_matrix.rows_ == second_matrix.rows_ &&
          first_matrix.cols_ == second_matrix.cols_);
}

}  // namespace s_21
