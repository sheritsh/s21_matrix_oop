/* created by sheritsh // Oleg Polovinko ※ School 21, Kzn */

#ifndef CPP1_S21_MATRIXPLUS_SRC_TESTS_UNIT_TEST_H_
#define CPP1_S21_MATRIXPLUS_SRC_TESTS_UNIT_TEST_H_

#include <gtest/gtest.h>

#include <cmath>
#include <iostream>
#include <vector>

#include "../s21_matrix_oop.h"

namespace s_21 {

class S21MatrixTest : public testing::Test {
 protected:
  S21Matrix *matrix_1x1;
  S21Matrix *matrix_2x3;
  S21Matrix *matrix_5x5;
  S21Matrix *matrix_12x21;
  S21Matrix *matrix_21x21;

  void SetUp();
  void TearDown();
  void FillMatrixWithRandomDouble(S21Matrix &matrix);
  void PrintMatrix(const S21Matrix &matrix);
};

}  // namespace s_21

#endif  // CPP1_S21_MATRIXPLUS_SRC_TESTS_UNIT_TEST_H_
