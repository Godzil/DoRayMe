/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Matric unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <matrix.h>
#include <tuples.h>
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