/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Smooth Triangle unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <smoothtriangle.h>
#include <math.h>
#include <gtest/gtest.h>

class SmoothTriTest : public SmoothTriangle
{
public:
    SmoothTriTest(Point p1, Point p2, Point p3, Vector n1, Vector n2, Vector n3) : SmoothTriangle(p1, p2, p3, n1, n2, n3) {};
    Intersect doLocalIntersect(Ray ray)
    {
        return this->localIntersect(ray);
    };

    Tuple doLocalNormalAt(Tuple point, Intersection *hit)
    {
      return this->localNormalAt(point, hit);
    };
};

Point p1 = Point(0, 1, 0);
Point p2 = Point(-1, 0, 0);
Point p3 = Point(1, 0, 0);
Vector n1 = Vector(0, 1, 0);
Vector n2 = Vector(-1, 0, 0);
Vector n3 = Vector(1, 0, 0);

SmoothTriTest tri = SmoothTriTest(p1, p2, p3, n1, n2, n3);

TEST(SmoothTriangleTest, Construcring_a_smooth_triangle)
{
    ASSERT_EQ(tri.p1, p1);
    ASSERT_EQ(tri.p2, p2);
    ASSERT_EQ(tri.p3, p3);
    ASSERT_EQ(tri.n1, n1);
    ASSERT_EQ(tri.n2, n2);
    ASSERT_EQ(tri.n3, n3);
}

TEST(SmoothTriangleTest, An_intersection_with_a_smooth_triangle_stores_u_v)
{
    Ray r = Ray(Point(-0.2, 0.3, -2), Vector(0, 0, 1));

    Intersect xs = tri.doLocalIntersect(r);

    ASSERT_TRUE(double_equal(xs[0].u, 0.45));
    ASSERT_TRUE(double_equal(xs[0].v, 0.25));
}

TEST(SmoothTriangleTest, A_smooth_triangle_uses_u_v_to_interpolate_the_normal)
{
    Intersection i = Intersection(1, &tri, 0.45, 0.25);

    Tuple n = tri.doLocalNormalAt(Point(0, 0, 0), &i);

    /* Temporary lower the precision */
    set_equal_precision(0.00001);

    ASSERT_EQ(n, Vector(-0.5547, 0.83205, 0));

    set_equal_precision(FLT_EPSILON);
}

TEST(SmoothTriangleTest, Preparing_a_normal_on_a_smooth_triangle)
{
    Intersection i = Intersection(1, &tri, 0.45, 0.25);

    Tuple n = tri.normalAt(Point(0, 0, 0), &i);

    /* Temporary lower the precision */
    set_equal_precision(0.00001);

    ASSERT_EQ(n, Vector(-0.5547, 0.83205, 0));

    set_equal_precision(FLT_EPSILON);
}
