#include "s21_matrix_oop.h"

namespace s_21 {
S21Matrix::S21Matrix() : S21Matrix(5, 5){};

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument(
        "The number of rows or cols cannot be less than 1");
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

S21Matrix::~S21Matrix() {
  FreeMemory();
  rows_ = 0;
  cols_ = 0;
}

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

}  // namespace s_21
