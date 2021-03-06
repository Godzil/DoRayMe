/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Transformations unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <transformation.h>
#include <tuple.h>
#include <math.h>
#include <gtest/gtest.h>

TEST(TransformationTest, Multiplying_by_a_translation_matrix)
{
   Matrix transform = translation(5, -3, 2);
   Point p = Point(-3, 4, 5);
   
   ASSERT_EQ(transform * p, Point(2, 1, 7));
}

TEST(TransformationTest, Multiplying_by_the_inverse_of_a_translation_matrix)
{
   Matrix transform = translation(5, -3, 2);
   Matrix inv = transform.inverse();
   
   Point p = Point(-3, 4, 5);
   
   ASSERT_EQ(inv * p, Point(-8, 7, 3));
}

TEST(TransformationTest, Translation_does_not_affect_vectors)
{
   Matrix transform = translation(5, -3, 2);
   
   Vector v = Vector(-3, 4, 5);
   
   ASSERT_EQ(transform * v, Vector(-3, 4, 5));
}

TEST(TransformationTest, A_scaling_matrix_applied_to_a_point)
{
   Matrix transform = scaling(2, 3, 4);
   
   Point p = Point(-4, 6, 8);
   
   ASSERT_EQ(transform * p, Point(-8, 18, 32));
}

TEST(TransformationTest, A_scaling_matrix_applied_to_a_vector)
{
   Matrix transform = scaling(2, 3, 4);
   
   Vector v = Vector(-4, 6, 8);
   
   ASSERT_EQ(transform * v, Vector(-8, 18, 32));
}

TEST(TransformationTest, Multiplaying_by_the_inverse_of_a_scaling_matrix)
{
   Matrix transform = scaling(2, 3, 4);
   Matrix inv = transform.inverse();
   
   Vector v = Vector(-4, 6, 8);
   
   ASSERT_EQ(inv * v, Vector(-2, 2, 2));
}

TEST(TransformationTest, Reflexion_is_scaling_by_a_negative_value)
{
   Matrix transform = scaling(-1, 1, 1);
   
   Point p = Point(2, 3, 4);
   
   ASSERT_EQ(transform * p, Point(-2, 3, 4));
}

TEST(TransformationTest, Rotating_a_point_around_the_X_axis)
{
   Point p = Point(0, 1, 0);
   Matrix half_quarter = rotationX(M_PI / 4.);
   Matrix full_quarter = rotationX(M_PI / 2.);
   
   ASSERT_EQ(half_quarter * p, Point(0, sqrt(2)/2, sqrt(2)/2));
   ASSERT_EQ(full_quarter * p, Point(0, 0, 1));
}

TEST(TransformationTest, The_inverse_of_an_x_rotation_rotates_in_the_opposite_direction)
{
   Point p = Point(0, 1, 0);
   Matrix half_quarter = rotationX(M_PI / 4.);
   Matrix inv = half_quarter.inverse();
   
   ASSERT_EQ(inv * p, Point(0, sqrt(2)/2, -sqrt(2)/2));
}

TEST(TransformationTest, Rotating_a_point_around_the_Y_axis)
{
   Point p = Point(0, 0, 1);
   Matrix half_quarter = rotationY(M_PI / 4.);
   Matrix full_quarter = rotationY(M_PI / 2.);
   
   ASSERT_EQ(half_quarter * p, Point(sqrt(2)/2, 0, sqrt(2)/2));
   ASSERT_EQ(full_quarter * p, Point(1, 0, 0));
}

TEST(TransformationTest, Rotating_a_point_around_the_Z_axis)
{
   Point p = Point(0, 1, 0);
   Matrix half_quarter = rotationZ(M_PI / 4.);
   Matrix full_quarter = rotationZ(M_PI / 2.);
   
   ASSERT_EQ(half_quarter * p, Point(-sqrt(2)/2, sqrt(2)/2, 0));
   ASSERT_EQ(full_quarter * p, Point(-1, 0, 0));
}

TEST(TransformationTest, A_shearing_transformation_moves_x_in_proportion_to_y)
{
    Matrix transform = shearing(1, 0, 0, 0, 0, 0);
    Point p = Point(2, 3, 4);

    ASSERT_EQ(transform * p, Point(5, 3, 4));
}

TEST(TransformationTest, A_shearing_transformation_moves_x_in_proportion_to_z)
{
    Matrix transform = shearing(0, 1, 0, 0, 0, 0);
    Point p = Point(2, 3, 4);

    ASSERT_EQ(transform * p, Point(6, 3, 4));
}

TEST(TransformationTest, A_shearing_transformation_moves_y_in_proportion_to_x)
{
    Matrix transform = shearing(0, 0, 1, 0, 0, 0);
    Point p = Point(2, 3, 4);

    ASSERT_EQ(transform * p, Point(2, 5, 4));
}

TEST(TransformationTest, A_shearing_transformation_moves_y_in_proportion_to_z)
{
    Matrix transform = shearing(0,  0, 0, 1, 0, 0);
    Point p = Point(2, 3, 4);

    ASSERT_EQ(transform * p, Point(2, 7, 4));
}

TEST(TransformationTest, A_shearing_transformation_moves_z_in_proportion_to_x)
{
    Matrix transform = shearing(0, 0, 0, 0, 1, 0);
    Point p = Point(2, 3, 4);

    ASSERT_EQ(transform * p, Point(2, 3, 6));
}

TEST(TransformationTest, A_shearing_transformation_moves_z_in_proportion_to_y)
{
    Matrix transform = shearing(0, 0, 0, 0, 0, 1);
    Point p = Point(2, 3, 4);

    ASSERT_EQ(transform * p, Point(2, 3, 7));
}

TEST(TransformationTest, Individual_trnasformations_are_applied_in_sequence)
{
    Point p = Point(1, 0, 1);
    Matrix A = rotationX(M_PI / 2.);
    Matrix B = scaling(5, 5, 5);
    Matrix C = translation(10, 5, 7);

    Tuple p2 = A * p;
    ASSERT_EQ(p2, Point(1, -1, 0));

    Tuple p3 = B * p2;
    ASSERT_EQ(p3, Point(5, -5, 0));

    Tuple p4 = C * p3;
    ASSERT_EQ(p4, Point(15, 0, 7));
}

TEST(TransformationTest, Chained_transformation_must_be_applied_in_reverse_order)
{
    Point p = Point(1, 0, 1);
    Matrix A = rotationX(M_PI / 2.);
    Matrix B = scaling(5, 5, 5);
    Matrix C = translation(10, 5, 7);

    Matrix T = C * B * A;
    ASSERT_EQ(T * p, Point(15, 0, 7));
}

TEST(TransformationTest, The_transformation_matrix_for_the_default_orientation)
{
    Tuple from = Point(0, 0, 0);
    Tuple to = Point(0, 0, -1);
    Tuple up = Vector(0, 1, 0);

    Matrix t = viewTransform(from, to, up);

    ASSERT_EQ(t, Matrix4().identity());
}


TEST(TransformationTest, A_view_transformation_matrix_looking_in_positive_z_direction)
{
    Tuple from = Point(0, 0, 0);
    Tuple to = Point(0, 0, 1);
    Tuple up = Vector(0, 1, 0);

    Matrix t = viewTransform(from, to, up);

    ASSERT_EQ(t, scaling(-1, 1, -1));
}

TEST(TransformationTest, The_view_transformation_move_the_world)
{
    Tuple from = Point(0, 0, 8);
    Tuple to = Point(0, 0, 0);
    Tuple up = Vector(0, 1, 0);

    Matrix t = viewTransform(from, to, up);

    ASSERT_EQ(t, translation(0, 0, -8));
}

TEST(TransformationTest, An_arbitrary_view_transformation)
{
    Tuple from = Point(1, 3, 2);
    Tuple to = Point(4, -2, 8);
    Tuple up = Vector(1, 1, 0);

    Matrix t = viewTransform(from, to, up);

    double values[] = {-0.50709, 0.50709,  0.67612, -2.36643,
                        0.76772, 0.60609,  0.12122, -2.82843,
                       -0.35857, 0.59761, -0.71714,  0.00000,
                        0.00000, 0.00000,  0.00000,  1.00000};

    /* Temporary lower the precision */
    set_equal_precision(0.00001);

    ASSERT_EQ(t, Matrix4(values));

    set_equal_precision(FLT_EPSILON);
}


