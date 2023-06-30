#include "unit_test.h"

namespace s_21 {
void S21MatrixTest::SetUp() {
  matrix_1x1 = new S21Matrix(1, 1);
  (*matrix_1x1)(0, 0) = 12;

  matrix_2x3 = new S21Matrix(2, 3);
  (*matrix_2x3)(0, 0) = -5.0;
  (*matrix_2x3)(0, 1) = 0.0;
  (*matrix_2x3)(0, 2) = 3.0;
  (*matrix_2x3)(1, 0) = -5.0;
  (*matrix_2x3)(1, 1) = 4.0;
  (*matrix_2x3)(1, 2) = 4.0;

  matrix_5x5 = new S21Matrix(5, 5);
  (*matrix_5x5)(0, 0) = -5.0;
  (*matrix_5x5)(0, 1) = 4.0;
  (*matrix_5x5)(0, 2) = 7.0;
  (*matrix_5x5)(1, 0) = 5.5;
  (*matrix_5x5)(1, 1) = 0;
  (*matrix_5x5)(1, 2) = 21.0;
  (*matrix_5x5)(2, 0) = 12;
  (*matrix_5x5)(2, 1) = 3;
  (*matrix_5x5)(2, 2) = 1997;

  matrix_12x21 = new S21Matrix(12, 21);
  FillMatrixWithRandomDouble(*matrix_12x21);

  matrix_21x21 = new S21Matrix(21, 21);
  FillMatrixWithRandomDouble(*matrix_21x21);
}

void S21MatrixTest::TearDown() {
  delete matrix_1x1;
  delete matrix_2x3;
  delete matrix_5x5;
  delete matrix_12x21;
  delete matrix_21x21;
}

void S21MatrixTest::FillMatrixWithRandomDouble(S21Matrix& matrix) {
  srand(time(nullptr));
  for (int i = 0; i < matrix.GetRows(); i++) {
    for (int j = 0; j < matrix.GetCols(); j++) {
      matrix(i, j) = rand() % 10;
    }
  }
}

void S21MatrixTest::PrintMatrix(const S21Matrix& matrix) {
  std::cout << "/------START-------/"
            << "\n";

  for (int i = 0; i < matrix.GetRows(); i++) {
    for (int j = 0; j < matrix.GetCols(); j++) {
      std::cout << matrix(i, j) << " ";
    }
    std::cout << "\n";
  }

  std::cout << "/------END-------/"
            << "\n";
}

// UNIT TEST START

// CONSTRUCTORS

TEST_F(S21MatrixTest, ConstructorNoParams) {
  S21Matrix matrix;
  EXPECT_EQ(5, matrix.GetRows());
  EXPECT_EQ(5, matrix.GetCols());
}

TEST_F(S21MatrixTest, ConstructorWithParams1) {
  S21Matrix matrix(3, 3);
  EXPECT_EQ(1, 1);
}

TEST_F(S21MatrixTest, ConstructorWithParams2) {
  S21Matrix matrix(3, 5);
  EXPECT_EQ(3, matrix.GetRows());
  EXPECT_EQ(5, matrix.GetCols());
}

TEST_F(S21MatrixTest, ConstructorWithParams3) {
  EXPECT_THROW(S21Matrix matrix(0, -2), std::invalid_argument);
}

TEST_F(S21MatrixTest, CopyConstructor1) {
  S21Matrix matrix(*matrix_12x21);
  EXPECT_EQ(12, matrix.GetRows());
  EXPECT_EQ(21, matrix.GetCols());
  EXPECT_EQ(12, (*matrix_12x21).GetRows());
  EXPECT_EQ(21, (*matrix_12x21).GetCols());
  EXPECT_EQ(1, matrix == *matrix_12x21);
}

TEST_F(S21MatrixTest, CopyConstructor2) {
  S21Matrix matrix;
  S21Matrix matrix_copy(matrix);
  EXPECT_EQ(5, matrix.GetRows());
  EXPECT_EQ(5, matrix.GetCols());
  EXPECT_EQ(5, matrix_copy.GetRows());
  EXPECT_EQ(5, matrix_copy.GetCols());
  EXPECT_EQ(1, matrix == matrix_copy);
}

TEST_F(S21MatrixTest, MoveConstructor1) {
  S21Matrix src_matrix;
  EXPECT_EQ(5, src_matrix.GetRows());
  EXPECT_EQ(5, src_matrix.GetCols());
  S21Matrix dst_matrix(std::move(src_matrix));
  EXPECT_EQ(0, src_matrix.GetRows());
  EXPECT_EQ(0, src_matrix.GetCols());
  EXPECT_EQ(5, dst_matrix.GetRows());
  EXPECT_EQ(5, dst_matrix.GetCols());
}

TEST_F(S21MatrixTest, MoveConstructor2) {
  S21Matrix src_matrix(*matrix_21x21);
  EXPECT_EQ(21, src_matrix.GetRows());
  EXPECT_EQ(21, src_matrix.GetCols());
  S21Matrix dst_matrix(std::move(src_matrix));
  EXPECT_EQ(0, src_matrix.GetRows());
  EXPECT_EQ(0, src_matrix.GetCols());
  EXPECT_EQ(21, dst_matrix.GetRows());
  EXPECT_EQ(21, dst_matrix.GetCols());
}

// ASSIGNMENT OPERATORS

TEST_F(S21MatrixTest, AssignmentOperator) {
  S21Matrix matrix;
  matrix = matrix;
  EXPECT_EQ(1, matrix == matrix);
}

TEST_F(S21MatrixTest, AssignmentOperator2) {
  S21Matrix matrix;
  matrix = *matrix_21x21;
  EXPECT_EQ(1, matrix == *matrix_21x21);
}

TEST_F(S21MatrixTest, AdditionAssignmentOperator1) {
  S21Matrix matrix(2, 3);
  matrix += (*matrix_2x3);
  EXPECT_EQ(1, matrix == *matrix_2x3);
}

TEST_F(S21MatrixTest, AdditionAssignmentOperator2) {
  S21Matrix matrix(21, 21);
  matrix += (*matrix_21x21);
  EXPECT_EQ(1, matrix == *matrix_21x21);
}

TEST_F(S21MatrixTest, AdditionAssignmentOperator3) {
  EXPECT_THROW((*matrix_1x1) += (*matrix_2x3), std::range_error);
}

TEST_F(S21MatrixTest, SubtractionAssignmentOperator1) {
  S21Matrix matrix(*matrix_12x21);
  S21Matrix empty_matrix(12, 21);
  EXPECT_EQ(1, matrix == *matrix_12x21);
  matrix -= *matrix_12x21;
  EXPECT_EQ(1, matrix == empty_matrix);
}

TEST_F(S21MatrixTest, SubtractionAssignmentOperator2) {
  S21Matrix matrix = (*matrix_5x5);
  S21Matrix empty_matrix(5, 5);
  EXPECT_EQ(1, matrix == *matrix_5x5);
  matrix -= *matrix_5x5;
  EXPECT_EQ(1, matrix == empty_matrix);
}

TEST_F(S21MatrixTest, SubtractionAssignmentOperator3) {
  EXPECT_THROW((*matrix_1x1) -= (*matrix_2x3), std::range_error);
}

TEST_F(S21MatrixTest, MultiplyAssignmentOperator1) {
  S21Matrix tmp_matrix(3, 2);
  tmp_matrix(0, 0) = 5.2;
  tmp_matrix(0, 1) = -3.0;
  tmp_matrix(1, 0) = 14.0;
  tmp_matrix(1, 1) = 18;
  tmp_matrix(2, 0) = 3.14;
  tmp_matrix(2, 1) = 5.10;

  tmp_matrix *= (*matrix_2x3);
  EXPECT_DOUBLE_EQ(-11, tmp_matrix(0, 0));
  EXPECT_DOUBLE_EQ(-12, tmp_matrix(0, 1));
  EXPECT_DOUBLE_EQ(3.6, tmp_matrix(0, 2));
  EXPECT_DOUBLE_EQ(-160, tmp_matrix(1, 0));
  EXPECT_DOUBLE_EQ(72, tmp_matrix(1, 1));
  EXPECT_DOUBLE_EQ(114, tmp_matrix(1, 2));
  EXPECT_DOUBLE_EQ(-41.2, tmp_matrix(2, 0));
  EXPECT_DOUBLE_EQ(20.4, tmp_matrix(2, 1));
  EXPECT_DOUBLE_EQ(29.82, tmp_matrix(2, 2));
}

TEST_F(S21MatrixTest, MultiplyAssignmentOperator2) {
  S21Matrix matrix = (*matrix_2x3);
  matrix *= 3.14;
  EXPECT_DOUBLE_EQ(-15.7, matrix(0, 0));
  EXPECT_DOUBLE_EQ(0, matrix(0, 1));
  EXPECT_DOUBLE_EQ(9.42, matrix(0, 2));
  EXPECT_DOUBLE_EQ(-15.7, matrix(1, 0));
  EXPECT_DOUBLE_EQ(12.56, matrix(1, 1));
  EXPECT_DOUBLE_EQ(12.56, matrix(1, 2));
}

TEST_F(S21MatrixTest, MultiplyAssignmentOperator3) {
  EXPECT_THROW((*matrix_1x1) *= (*matrix_2x3), std::range_error);
}

// GETTERS AND SETTERS

TEST_F(S21MatrixTest, GetRows) {
  S21Matrix test;
  EXPECT_EQ(5, test.GetRows());
}

TEST_F(S21MatrixTest, GetRows2) { EXPECT_EQ(12, (*matrix_12x21).GetRows()); }

TEST_F(S21MatrixTest, GetCols1) {
  S21Matrix test;
  EXPECT_EQ(5, test.GetCols());
}

TEST_F(S21MatrixTest, GetCols2) { EXPECT_EQ(21, (*matrix_12x21).GetCols()); }

TEST_F(S21MatrixTest, SetRows) {
  S21Matrix matrix(10, 12);
  matrix.SetRows(3);
  EXPECT_EQ(3, matrix.GetRows());
}

TEST_F(S21MatrixTest, SetRowsException) {
  EXPECT_THROW((*matrix_1x1).SetCols(-4), std::invalid_argument);
}

TEST_F(S21MatrixTest, SetCols) {
  S21Matrix matrix(10, 12);
  matrix.SetCols(6);
  EXPECT_EQ(6, matrix.GetCols());
}

TEST_F(S21MatrixTest, SetColsException) {
  EXPECT_THROW((*matrix_2x3).SetCols(0), std::invalid_argument);
}

// OVERLOAD OPERATORS

TEST_F(S21MatrixTest, SumOperator) {
  S21Matrix matrix;
  S21Matrix filled_matrix;
  FillMatrixWithRandomDouble(filled_matrix);
  matrix = matrix + filled_matrix;
  EXPECT_EQ(1, matrix == filled_matrix);
}

TEST_F(S21MatrixTest, SumOperatorException) {
  EXPECT_THROW((*matrix_1x1) + (*matrix_21x21), std::range_error);
}

TEST_F(S21MatrixTest, SubOperator) {
  S21Matrix matrix;
  S21Matrix filled_matrix;
  FillMatrixWithRandomDouble(filled_matrix);
  filled_matrix = filled_matrix - filled_matrix;
  EXPECT_EQ(1, matrix == filled_matrix);
}

TEST_F(S21MatrixTest, SubOperatorException) {
  EXPECT_THROW((*matrix_1x1) - (*matrix_21x21), std::range_error);
}

TEST_F(S21MatrixTest, MulMatrixOperator) {
  S21Matrix tmp_matrix(3, 2);
  tmp_matrix(0, 0) = 5.2;
  tmp_matrix(0, 1) = -3.0;
  tmp_matrix(1, 0) = 14.0;
  tmp_matrix(1, 1) = 18;
  tmp_matrix(2, 0) = 3.14;
  tmp_matrix(2, 1) = 5.10;

  S21Matrix res_matrix = tmp_matrix * (*matrix_2x3);
  EXPECT_DOUBLE_EQ(-11, res_matrix(0, 0));
  EXPECT_DOUBLE_EQ(-12, res_matrix(0, 1));
  EXPECT_DOUBLE_EQ(3.6, res_matrix(0, 2));
  EXPECT_DOUBLE_EQ(-160, res_matrix(1, 0));
  EXPECT_DOUBLE_EQ(72, res_matrix(1, 1));
  EXPECT_DOUBLE_EQ(114, res_matrix(1, 2));
  EXPECT_DOUBLE_EQ(-41.2, res_matrix(2, 0));
  EXPECT_DOUBLE_EQ(20.4, res_matrix(2, 1));
  EXPECT_DOUBLE_EQ(29.82, res_matrix(2, 2));
}

TEST_F(S21MatrixTest, MultMatrixOperatorException) {
  EXPECT_THROW((*matrix_1x1) * (*matrix_21x21), std::range_error);
}

TEST_F(S21MatrixTest, MulNumOperator) {
  S21Matrix matrix = (*matrix_2x3);
  matrix = matrix * 3.14;
  EXPECT_DOUBLE_EQ(-15.7, matrix(0, 0));
  EXPECT_DOUBLE_EQ(0, matrix(0, 1));
  EXPECT_DOUBLE_EQ(9.42, matrix(0, 2));
  EXPECT_DOUBLE_EQ(-15.7, matrix(1, 0));
  EXPECT_DOUBLE_EQ(12.56, matrix(1, 1));
  EXPECT_DOUBLE_EQ(12.56, matrix(1, 2));
}

TEST_F(S21MatrixTest, NumMulOperator) {
  S21Matrix matrix = (*matrix_2x3);
  matrix = 3.14 * matrix;
  EXPECT_DOUBLE_EQ(-15.7, matrix(0, 0));
  EXPECT_DOUBLE_EQ(0, matrix(0, 1));
  EXPECT_DOUBLE_EQ(9.42, matrix(0, 2));
  EXPECT_DOUBLE_EQ(-15.7, matrix(1, 0));
  EXPECT_DOUBLE_EQ(12.56, matrix(1, 1));
  EXPECT_DOUBLE_EQ(12.56, matrix(1, 2));
}

TEST_F(S21MatrixTest, EqOperator) {
  EXPECT_EQ(1, (*matrix_21x21) == (*matrix_21x21));
}

TEST_F(S21MatrixTest, ParenthesesOperator) {
  S21Matrix matrix;
  matrix(3, 2) = 322;
  EXPECT_EQ(322, matrix(3, 2));
}

TEST_F(S21MatrixTest, ParenthesesOperatorException) {
  S21Matrix matrix;
  EXPECT_THROW(matrix(-4, 6), std::out_of_range);
}

// MEMBER FUNCTIONS

TEST_F(S21MatrixTest, Transpose1) {
  S21Matrix reference_matrix(3, 2);
  S21Matrix transposed_matrix(reference_matrix.Transpose());
  EXPECT_EQ(2, transposed_matrix.GetRows());
  EXPECT_EQ(3, transposed_matrix.GetCols());
}

TEST_F(S21MatrixTest, Transpose2) {
  S21Matrix transposed_matrix((*matrix_21x21).Transpose());
  EXPECT_EQ(21, transposed_matrix.GetRows());
  EXPECT_EQ(21, transposed_matrix.GetCols());
}

TEST_F(S21MatrixTest, CalcComplements) {
  S21Matrix matrix(3, 3);
  S21Matrix reference_matrix(3, 3);
  matrix(0, 0) = 1, matrix(0, 1) = 2, matrix(0, 2) = 3;
  matrix(1, 0) = 0, matrix(1, 1) = 4, matrix(1, 2) = 2;
  matrix(2, 0) = 5, matrix(2, 1) = 2, matrix(2, 2) = 1;
  reference_matrix(0, 0) = 0, reference_matrix(0, 1) = 10;
  reference_matrix(0, 2) = -20, reference_matrix(1, 0) = 4;
  reference_matrix(1, 1) = -14, reference_matrix(1, 2) = 8;
  reference_matrix(2, 0) = -8, reference_matrix(2, 1) = -2;
  reference_matrix(2, 2) = 4;
  S21Matrix complements_matrix(matrix.CalcComplements());
  EXPECT_EQ(1, complements_matrix == reference_matrix);
}

TEST_F(S21MatrixTest, CalcComplementsException) {
  EXPECT_THROW((*matrix_12x21).CalcComplements(), std::range_error);
}

TEST_F(S21MatrixTest, Determinant1) {
  EXPECT_EQ(12, (*matrix_1x1).Determinant());
}

TEST_F(S21MatrixTest, Determinant2) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 3, matrix(0, 1) = 6;
  matrix(1, 0) = 9, matrix(1, 1) = 12;
  EXPECT_DOUBLE_EQ(-18, matrix.Determinant());
}

TEST_F(S21MatrixTest, DeterminantException) {
  EXPECT_THROW((*matrix_12x21).Determinant(), std::range_error);
}

TEST_F(S21MatrixTest, InverseMatrix1) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 21;
  S21Matrix reference_matrix(1, 1);
  reference_matrix(0, 0) = 1.0 / 21.0;
  EXPECT_EQ(1, matrix.InverseMatrix() == reference_matrix);
}

TEST_F(S21MatrixTest, InverseMatrix2) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 2, matrix(0, 1) = 5, matrix(0, 2) = 7;
  matrix(1, 0) = 6, matrix(1, 1) = 3, matrix(1, 2) = 4;
  matrix(2, 0) = 5, matrix(2, 1) = -2, matrix(2, 2) = -3;
  S21Matrix ref_matrix(3, 3);
  ref_matrix(0, 0) = 1, ref_matrix(0, 1) = -1, ref_matrix(0, 2) = 1;
  ref_matrix(1, 0) = -38, ref_matrix(1, 1) = 41, ref_matrix(1, 2) = -34;
  ref_matrix(2, 0) = 27, ref_matrix(2, 1) = -29, ref_matrix(2, 2) = 24;
  EXPECT_EQ(1, matrix.InverseMatrix() == ref_matrix);
}

TEST_F(S21MatrixTest, InverseMatrixException) {
  EXPECT_THROW((*matrix_12x21).InverseMatrix(), std::range_error);
}

// UNIT TEST END

}  // namespace s_21

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
