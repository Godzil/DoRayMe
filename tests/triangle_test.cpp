/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Triangle unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <triangle.h>
#include <math.h>
#include <gtest/gtest.h>

TEST(TriangleTest, Construcring_a_triangle)
{
    Point p1 = Point(0, 1, 0);
    Point p2 = Point(-1, 0, 0);
    Point p3 = Point(1, 0, 0);

    Triangle t = Triangle(p1, p2, p3);

    ASSERT_EQ(t.p1, p1);
    ASSERT_EQ(t.p2, p2);
    ASSERT_EQ(t.p3, p3);
    ASSERT_EQ(t.e1, Vector(-1, -1, 0));
    ASSERT_EQ(t.e2, Vector(1, -1, 0));
    ASSERT_EQ(t.normal, Vector(0, 0, -1));
}

TEST(TriangleTest, Finding_the_normal_on_a_triangle)
{
    Triangle t = Triangle(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));

    Tuple n1 = t.normalAt(Point(0, 0.5, 0));
    Tuple n2 = t.normalAt(Point(-0.5, 0.75, 0));
    Tuple n3 = t.normalAt(Point(0.5, 0.25, 0));

    ASSERT_EQ(n1, t.normal);
    ASSERT_EQ(n2, t.normal);
    ASSERT_EQ(n3, t.normal);
}

TEST(TriangleTest, Intersecting_a_ray_parallel_to_the_triangle)
{
    Triangle t = Triangle(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));
    Ray r = Ray(Point(0, -1, -2), Vector(0, 1, 0));

    Intersect xs; t.intersect(r, xs);

    ASSERT_EQ(xs.count(), 0);
}

TEST(TriangleTest, A_ray_miss_the_p1_p3_edge)
{
    Triangle t = Triangle(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));
    Ray r = Ray(Point(1, 1, -2), Vector(0, 0, 1));

    Intersect xs; t.intersect(r, xs);

    ASSERT_EQ(xs.count(), 0);
}

TEST(TriangleTest, A_ray_miss_the_p1_p2_edge)
{
    Triangle t = Triangle(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));
    Ray r = Ray(Point(-1, 1, -2), Vector(0, 0, 1));

    Intersect xs; t.intersect(r, xs);

    ASSERT_EQ(xs.count(), 0);
}

TEST(TriangleTest, A_ray_miss_the_p2_p3_edge)
{
    Triangle t = Triangle(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));
    Ray r = Ray(Point(0, -1, -2), Vector(0, 0, 1));

    Intersect xs; t.intersect(r, xs);

    ASSERT_EQ(xs.count(), 0);
}

TEST(TriangleTest, A_ray_strikes_a_triangle)
{
    Triangle t = Triangle(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));
    Ray r = Ray(Point(0, .5, -2), Vector(0, 0, 1));

    Intersect xs; t.intersect(r, xs);

    ASSERT_EQ(xs.count(), 1);
    EXPECT_EQ(xs[0].t, 2);
}

TEST(TriangleTest, A_triangle_has_a_bounding_box)
{
    Triangle t = Triangle(Point(-3, 7, 2), Point(6, 2, -4), Point(2, -1, -1));

    BoundingBox res = t.getBounds();

    ASSERT_EQ(res.min, Point(-3, -1, -4));
    ASSERT_EQ(res.max, Point(6, 7, 2));
}
