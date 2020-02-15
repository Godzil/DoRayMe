/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Matric unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <matrix.h>
#include <tuple.h>
#include <math.h>
#include <gtest/gtest.h>


TEST(MatrixTest, Constructing_and_inspecting_a_4x4_Matrix)
{
    double values[] = {1,    2,    3,    4,
                       5.5,  6.5,  7.5,  8.5,
                       9,    10,   11,   12,
                       13.5, 14.5, 15.5, 16.5};

    Matrix4 m = Matrix4(values);

    ASSERT_EQ(m.get(0, 0), 1);
    ASSERT_EQ(m.get(0, 3), 4);
    ASSERT_EQ(m.get(1, 0), 5.5);
    ASSERT_EQ(m.get(1, 2), 7.5);
    ASSERT_EQ(m.get(2, 2), 11);
    ASSERT_EQ(m.get(3, 0), 13.5);
    ASSERT_EQ(m.get(3, 2), 15.5);
}

TEST(MatrixTest, A_2x2_matric_ought_to_be_representable)
{
    double values[] = {-3, 5,
                        1, -2};

    Matrix2 m = Matrix2(values);

    ASSERT_EQ(m.get(0, 0), -3);
    ASSERT_EQ(m.get(0, 1), 5);
    ASSERT_EQ(m.get(1, 0), 1);
    ASSERT_EQ(m.get(1, 1), -2);
}

TEST(MatrixTest, A_3x3_matric_ought_to_be_representable)
{
    double values[] = {-3, 5, 0,
                       1,  -2, -7,
                       0,  1,  1};

    Matrix3 m = Matrix3(values);

    ASSERT_EQ(m.get(0, 0), -3);
    ASSERT_EQ(m.get(1, 1), -2);
    ASSERT_EQ(m.get(2, 2), 1);
}

TEST(MatrixTest, Matrix_equality_with_identical_matrix)
{
    double values1[] = {1, 2, 3, 4,
                        5, 6, 7, 8,
                        9, 8, 7, 6,
                        5, 4, 3, 2};

    double values2[] = {1, 2, 3, 4,
                        5, 6, 7, 8,
                        9, 8, 7, 6,
                        5, 4, 3, 2};
    Matrix4 A = Matrix4(values1);
    Matrix4 B = Matrix4(values2);

    ASSERT_EQ(A, B);
}

TEST(MatrixTest, Matrix_equality_with_different_matrix)
{
    double values1[] = {1, 2, 3, 4,
                        5, 6, 7, 8,
                        9, 8, 7, 6,
                        5, 4, 3, 2};

    double values2[] = {2, 3, 4, 5,
                        6, 7, 8, 9,
                        8, 7, 6, 5,
                        4, 3, 2, 1};
    Matrix4 A = Matrix4(values1);
    Matrix4 B = Matrix4(values2);

    ASSERT_NE(A, B);
}

TEST(MatrixTest, Multiplying_two_matrices)
{
    double values1[] = {1, 2, 3, 4,
                        5, 6, 7, 8,
                        9, 8, 7, 6,
                        5, 4, 3, 2};

    double values2[] = {-2, 1, 2, 3,
                        3, 2, 1, -1,
                        4, 3, 6, 5,
                        1, 2, 7, 8};

    double results[] = {20, 22, 50, 48,
                        44, 54, 114, 108,
                        40, 58, 110, 102,
                        16, 26, 46, 42};

    Matrix4 A = Matrix4(values1);
    Matrix4 B = Matrix4(values2);


    ASSERT_EQ(A * B, Matrix4(results));
}

TEST(MatrixTest, A_matrix_multiplyed_by_a_tuple)
{
    double valuesA[] = {1, 2, 3, 4,
                        2, 4, 4, 2,
                        8, 6, 4, 1,
                        0, 0, 0, 1};

    Matrix4 A = Matrix4(valuesA);
    Tuple b = Tuple(1, 2, 3, 1);

    ASSERT_EQ(A * b, Tuple(18, 24, 33, 1));
}

TEST(MatrixTest, Multiplying_a_matrix_by_the_identity_matrix)
{
    double valuesA[] = {0, 1, 2, 4,
                        1, 2, 4, 8,
                        2, 4, 8, 16,
                        4, 8, 16, 32};

    Matrix4 A = Matrix4(valuesA);
    Matrix ident = Matrix4().identity();

    ASSERT_EQ(A * ident, A);
}

TEST(MatrixTest, Multiplying_the_identity_matrix_by_a_tuple)
{
    Tuple a = Tuple(1, 2, 3, 4);
    Matrix ident = Matrix4().identity();

    ASSERT_EQ(ident * a, a);
}

TEST(MatrixTest, Transposing_a_matrix)
{
    double valuesA[] = {0, 9, 3, 0,
                        9, 8, 0, 8,
                        1, 8, 5, 3,
                        0, 0, 5, 8};

    double results[] = {0, 9, 1, 0,
                        9, 8, 8, 0,
                        3, 0, 5, 5,
                        0, 8, 3, 8};

    Matrix A = Matrix4(valuesA);

    ASSERT_EQ(A.transpose(), Matrix4(results));
}

TEST(MatrixTest, Transposing_this_identity_matrix)
{
    Matrix ident = Matrix4().identity();

    ASSERT_EQ(ident.transpose(), ident);
}

TEST(MatrixTest, Calculating_the_determinant_of_a_2x2_matrix)
{
    double valuesA[] = { 1, 5,
                         -3, 2 };
    Matrix2 A = Matrix2(valuesA);

    ASSERT_EQ(A.determinant(), 17);
}

TEST(MatrixTest, A_submatrix_of_a_3x3_matrix_is_a_2x2_matrix)
{
    double valuesA[] = { 1, 5, 0,
                         -3, 2, 7,
                         0, 6, -3 };
    double results[] = { -3, 2,
                         0, 6 };
    Matrix3 A = Matrix3(valuesA);

    ASSERT_EQ(A.submatrix(0, 2), Matrix2(results));
}

TEST(MatrixTest, A_submatrix_of_a_4x4_matrix_is_a_3x3_matrix)
{
    double valuesA[] = { -6, 1, 1, 6,
                         -8, 5, 8, 6,
                         -1, 0, 8, 2,
                         -7, 1, -1, 1 };
    double results[] = { -6, 1, 6,
                         -8, 8, 6,
                         -7,-1, 1 };
    Matrix4 A = Matrix4(valuesA);

    ASSERT_EQ(A.submatrix(2, 1), Matrix3(results));
}

TEST(MatrixTest, Calculate_a_minor_of_a_3x3_matrix)
{
    double valuesA[] = { 3, 5, 0,
                         2, -1, -7,
                         6, -1, 5 };

    Matrix3 A = Matrix3(valuesA);

    Matrix B = A.submatrix(1, 0);

    ASSERT_EQ(B.determinant(), 25);
    ASSERT_EQ(A.minor(1, 0), 25);
}

TEST(MatrixTest, Calculating_a_cofactor_of_a_3x3_matrix)
{
    double valuesA[] = { 3, 5, 0,
                         2, -1, -7,
                         6, -1, 5 };

    Matrix3 A = Matrix3(valuesA);

    ASSERT_EQ(A.minor(0, 0), -12);
    ASSERT_EQ(A.cofactor(0, 0), -12);
    ASSERT_EQ(A.minor(1, 0), 25);
    ASSERT_EQ(A.cofactor(1, 0), -25);
}

TEST(MatrixTest, Calculating_the_determinant_of_a_3x3_matrix)
{
    double valuesA[] = { 1, 2, 6,
                         -5, 8, -4,
                         2, 6, 4 };

    Matrix A = Matrix3(valuesA);

    ASSERT_EQ(A.cofactor(0, 0), 56);
    ASSERT_EQ(A.cofactor(0, 1), 12);
    ASSERT_EQ(A.minor(0, 2), -46);
    ASSERT_EQ(A.determinant(), -196);
}

TEST(MatrixTest, Calculating_the_determinant_of_a_4x4_matrix)
{
    double valuesA[] = { -2, -8, 3, 5,
                         -3, 1, 7, 3,
                         1, 2, -9, 6,
                         -6, 7, 7, -9 };

    Matrix A = Matrix4(valuesA);

    ASSERT_EQ(A.cofactor(0, 0), 690);
    ASSERT_EQ(A.cofactor(0, 1), 447);
    ASSERT_EQ(A.cofactor(0, 2),  210);
    ASSERT_EQ(A.minor(0, 3), -51);
    ASSERT_EQ(A.determinant(), -4071);
}

TEST(MatrixTest, Testing_an_invertible_matrix_for_invertibility)
{
    double valuesA[] = { 6, 4, 4, 4,
                         5, 5, 7, 6,
                         4, -9, 3, -7,
                         9, 1, 7, -6 };
    Matrix A = Matrix4(valuesA);

    ASSERT_EQ(A.determinant(), -2120);
    ASSERT_TRUE(A.isInvertible());
}

TEST(MatrixTest, Testing_an_noninvertible_matrix_for_invertibility)
{
    double valuesA[] = { -4, 2, -2, -3,
                         9, 6, 2, 6,
                         0, -5, 1, -5,
                         0, 0, 0, 0 };
    Matrix A = Matrix4(valuesA);

    ASSERT_EQ(A.determinant(), 0);
    ASSERT_FALSE(A.isInvertible());
}

TEST(MatrixTest, Calculating_the_inverse_of_a_matrix)
{
    double valuesA[] = { -5, 2, 6, -8,
                         1, -5, 1, 8,
                         7, 7, -6, -7,
                         1, -3, 7, 4 };

    double results[] = {  0.21805, 0.45113, 0.24060, -0.04511,
                         -0.80827, -1.45677, -0.44361, 0.52068,
                         -0.07895, -0.22368, -0.05263, 0.19737,
                         -0.52256, -0.81391, -0.30075, 0.30639 };

    Matrix A = Matrix4(valuesA);
    Matrix B = A.inverse();

    ASSERT_EQ(A.determinant(), 532);
    ASSERT_EQ(A.cofactor(2, 3), -160);
    ASSERT_NEAR(B.get(3, 2), -160./532., DBL_EPSILON);
    ASSERT_EQ(A.cofactor(3, 2), 105);
    ASSERT_NEAR(B.get(2, 3), 105./532., DBL_EPSILON);

    /* Temporary lower the precision */
    set_equal_precision(0.00001);

    ASSERT_EQ(B, Matrix4(results));

    /* Revert to default */
    set_equal_precision(FLT_EPSILON);
}

TEST(MatrixTest, Calculating_the_inverse_of_another_matrix)
{
    double valuesA[] = {  8, -5,  9,  2,
                          7,  5,  6,  1,
                         -6,  0,  9,  6,
                         -3,  0, -9, -4 };

    double results[] = {  -0.15385, -0.15385, -0.28205, -0.53846,
                          -0.07692,  0.12308,  0.02564,  0.03077,
                           0.35897,  0.35897,  0.43590,  0.92308,
                          -0.69231, -0.69231, -0.76923, -1.92308 };

    Matrix A = Matrix4(valuesA);
    Matrix B = A.inverse();


    /* Temporary lower the precision */
    set_equal_precision(0.00001);

    ASSERT_EQ(B, Matrix4(results));

    /* Revert to default */
    set_equal_precision(FLT_EPSILON);
}

TEST(MatrixTest, Calculating_the_inverse_of_third_matrix)
{
    double valuesA[] = {  9,  3,  0,  9,
                         -5, -2, -6, -3,
                         -4,  9,  6,  4,
                         -7,  6,  6,  2 };

    double results[] = { -0.04074, -0.07778,  0.14444, -0.22222,
                         -0.07778,  0.03333,  0.36667, -0.33333,
                         -0.02901, -0.14630, -0.10926,  0.12963,
                          0.17778,  0.06667, -0.26667,  0.33333 };

    Matrix A = Matrix4(valuesA);
    Matrix B = A.inverse();


    /* Temporary lower the precision */
    set_equal_precision(0.00001);

    ASSERT_EQ(B, Matrix4(results));

    /* Revert to default */
    set_equal_precision(FLT_EPSILON);
}

TEST(MatrixTest, Multiplying_a_product_by_its_inverse)
{
    double valuesA[] = {  3, -9, 7, 3,
                          3, -8, 2, -9,
                          -4, 4, 4, 1,
                          -6, 5, -1, 1 };

    double valuesB[] = { 8, 2, 2, 2,
                        3, -1, 7, 0,
                        7, 0, 5, 4,
                        6, -2, 0, 5 };

    Matrix A = Matrix4(valuesA);
    Matrix B = Matrix4(valuesB);

    Matrix C = A * B;

    ASSERT_EQ(C * B.inverse(), A);
}