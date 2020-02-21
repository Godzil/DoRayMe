/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Shape unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <shape.h>
#include <testshape.h>
#include <matrix.h>
#include <transformation.h>
#include <gtest/gtest.h>

TEST(ShapeTest, The_default_transformation)
{
    TestShape s = TestShape();
    ASSERT_EQ(s.transformMatrix, Matrix4().identity());
}

TEST(ShapeTest, Assigning_a_transformation)
{
    TestShape s = TestShape();

    s.setTransform(translation(2, 3, 4));

    ASSERT_EQ(s.transformMatrix, translation(2, 3, 4));
}

TEST(ShapeTest, The_default_material)
{
    TestShape s = TestShape();

    ASSERT_EQ(s.material, Material());
}

TEST(ShapeTest, Assigning_a_material)
{
    TestShape s = TestShape();
    Material m = Material();
    m.ambient = 1;

    s.material = m;

    ASSERT_EQ(s.material, m);
}

TEST(ShapeTest, Intersecting_a_scaled_shape_with_a_ray)
{
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    TestShape s = TestShape();

    s.setTransform(scaling(2, 2, 2));
    Intersect xs = s.intersect(r);

    ASSERT_EQ(s.localRay.origin, Point(0, 0, -2.5));
    ASSERT_EQ(s.localRay.direction, Vector(0, 0, 0.5));
}

TEST(ShapeTest, Intersecting_a_translated_shape_with_a_ray)
{
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    TestShape s = TestShape();

    s.setTransform(translation(5, 0, 0));
    Intersect xs = s.intersect(r);

    ASSERT_EQ(s.localRay.origin, Point(-5, 0, -5));
    ASSERT_EQ(s.localRay.direction, Vector(0, 0, 1));
}

TEST(ShapeTest, Computing_the_normal_on_a_translated_shape)
{
    TestShape s = TestShape();
    s.setTransform(translation(0, 1, 0));
    Tuple n = s.normalAt(Point(0, 1.70711, -0.70711));

    /* Temporary lower the precision */
    set_equal_precision(0.00001);

    ASSERT_EQ(n, Vector(0, 0.70711, -0.70711));

    set_equal_precision(FLT_EPSILON);
}

TEST(ShapeTest, Computing_the_normal_on_a_tranformed_shape)
{
    TestShape s = TestShape();
    s.setTransform(scaling(1, 0.5, 1) * rotationZ(M_PI / 5));
    Tuple n = s.normalAt(Point(0, sqrt(2)/2, -sqrt(2)/2));

    /* Temporary lower the precision */
    set_equal_precision(0.00001);

    ASSERT_EQ(n, Vector(0, 0.97014, -0.24254));

    set_equal_precision(FLT_EPSILON);
}