/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Tuples unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <tuple.h>
#include <math.h>
#include <gtest/gtest.h>

TEST(TupleTest, Tuple_With_w_equal_1_and_is_point)
{
    Tuple a = Tuple(4.3, -4.2, 3.1, 1.0);

    ASSERT_EQ(a.x, 4.3);
    ASSERT_EQ(a.y, -4.2);
    ASSERT_EQ(a.z, 3.1);
    ASSERT_EQ(a.w, 1.0);
    ASSERT_TRUE(a.isPoint());
    ASSERT_FALSE(a.isVector());
}

TEST(TupleTest, Two_tuples_are_equal)
{
    Tuple a = Tuple(1, 2, 3, 4);
    Tuple b = Tuple(1, 2, 3, 4);
    Tuple c = Tuple(4, 3, 2, 1);
    Tuple d = Tuple(1, 2, 3, 5);
    Tuple e = Tuple(1, 2, 5, 5);
    Tuple f = Tuple(1, 5, 5, 5);

    ASSERT_EQ(a, b);
    ASSERT_NE(a, c);
    ASSERT_NE(a, d);
    ASSERT_NE(a, e);
    ASSERT_NE(a, f);
}

TEST(TupleTest, Tuple_With_w_equal_0_and_is_vector)
{
    Tuple a = Tuple(4.3, -4.2, 3.1, 0.0);

    ASSERT_EQ(a.x, 4.3);
    ASSERT_EQ(a.y, -4.2);
    ASSERT_EQ(a.z, 3.1);
    ASSERT_EQ(a.w, 0.0);
    ASSERT_FALSE(a.isPoint());
    ASSERT_TRUE(a.isVector());
}

TEST(TupleTest, Point_create_tuples_with_w_equal_1)
{
    Tuple a = Point(4, -4, 3);

    ASSERT_EQ(a, Tuple(4, -4, 3, 1));
}

TEST(TupleTest, Vector_create_tuples_with_w_equal_0)
{
    Tuple a = Vector(4, -4, 3);

    ASSERT_EQ(a, Tuple(4, -4, 3, 0));
}

TEST(TupleTest, Adding_two_tuples)
{
    Tuple a1 = Tuple(3, -2, 5, 1);
    Tuple a2 = Tuple(-2, 3, 1, 0);

    ASSERT_EQ(a1 + a2, Tuple(1, 1, 6, 1));
}

TEST(TupleTest, Substracting_two_points)
{
    Point p1 = Point(3, 2, 1);
    Point p2 = Point(5, 6, 7);

    ASSERT_EQ(p1 - p2, Vector(-2, -4, -6));
}

TEST(TupleTest, Substracting_a_vector_from_a_point)
{
    Point p = Point(3, 2, 1);
    Vector v = Vector(5, 6, 7);

    ASSERT_EQ(p - v, Point(-2, -4, -6));
}

TEST(TupleTest, Substracting_two_vectors)
{
    Vector v1 = Vector(3, 2, 1);
    Vector v2 = Vector(5, 6, 7);

    ASSERT_EQ(v1 - v2, Vector(-2, -4, -6));
}

TEST(TupleTest, Substracting_a_vector_from_zero_vector)
{
    Vector zero = Vector(0, 0, 0);
    Vector v = Vector(1, -2, 3);

    ASSERT_EQ(zero - v, Vector(-1, 2, -3));
}

TEST(TupleTest, Negating_a_tuple)
{
    Tuple a = Tuple(1, -2, 3, -4);

    ASSERT_EQ(-a, Tuple(-1, 2, -3, 4));
}

TEST(TupleTest, Multiplying_a_tuple_by_a_scalar)
{
    Tuple a = Tuple(1, -2, 3, -4);

    ASSERT_EQ(a * 3.5, Tuple(3.5, -7, 10.5, -14));
}

TEST(TupleTest, Multiplying_a_tuple_by_a_fraction)
{
    Tuple a = Tuple(1, -2, 3, -4);

    ASSERT_EQ(a * 0.5, Tuple(0.5, -1, 1.5, -2));
}

TEST(TupleTest, Dividing_a_tuple_by_a_scalar)
{
    Tuple a = Tuple(1, -2, 3, -4);

    ASSERT_EQ(a / 2, Tuple(0.5, -1, 1.5, -2));
}

TEST(TupleTest, Computing_the_magnitude_of_vector_1_0_0)
{
    Vector v = Vector(1, 0, 0);

    ASSERT_EQ(v.magnitude(), 1);
}

TEST(TupleTest, Computing_the_magnitude_of_vector_0_1_0)
{
    Vector v = Vector(0, 1, 0);

    ASSERT_EQ(v.magnitude(), 1);
}

TEST(TupleTest, Computing_the_magnitude_of_vector_0_0_1)
{
    Vector v = Vector(0, 0, 1);

    ASSERT_EQ(v.magnitude(), 1);
}

TEST(TupleTest, Computing_the_magnitude_of_vector_1_2_3)
{
    Vector v = Vector(1, 2, 3);

    ASSERT_EQ(v.magnitude(), sqrt(14));
}

TEST(TupleTest, Computing_the_magnitude_of_vector_n1_n2_n3)
{
    Vector v = Vector(-1, -2, -3);

    ASSERT_EQ(v.magnitude(), sqrt(14));
}

TEST(TupleTest, Nomilise_vector_4_0_0_give_1_0_0)
{
    Vector v = Vector(4, 0, 0);

    ASSERT_EQ(v.normalise(), Vector(1, 0, 0));
}

TEST(TupleTest, Nomilise_vector_1_2_3)
{
    Vector v = Vector(1, 2, 3);

    ASSERT_EQ(v.normalise(), Vector(1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14)));
}

TEST(TupleTest, Dot_product_of_two_tuples)
{
    Vector a = Vector(1, 2, 3);
    Vector b = Vector(2, 3, 4);

    ASSERT_EQ(a.dot(b), 20);
}

TEST(TupleTest, Cross_product_of_two_vector)
{
    Vector a = Vector(1, 2, 3);
    Vector b = Vector(2, 3, 4);

    ASSERT_EQ(a.cross(b), Vector(-1, 2, -1));
    ASSERT_EQ(b.cross(a), Vector(1, -2, 1));
}

TEST(TupleTest, Reflecting_a_vector_approaching_at_45)
{
    Vector v = Vector(1, -1, 0); /* Vector */
    Vector n = Vector(0, 1, 0); /* Normal */

    Tuple r = v.reflect(n);

    ASSERT_EQ(r, Vector(1, 1, 0));
}

TEST(TupleTest, Reflecting_a_vector_off_a_slanted_surface)
{
    Vector v = Vector(0, -1, 0); /* Vector */
    Vector n = Vector(sqrt(2)/2, sqrt(2)/2, 0); /* Normal */

    Tuple r = v.reflect(n);

    ASSERT_EQ(r, Vector(1, 0, 0));
}