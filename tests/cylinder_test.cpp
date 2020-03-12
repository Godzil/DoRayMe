/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Cylinder unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <intersect.h>
#include <intersection.h>
#include <cylinder.h>
#include <transformation.h>
#include <gtest/gtest.h>

TEST(CylinderTest, A_ray_miss_a_cylinder)
{
    Cylinder cyl = Cylinder();

    Point Origins[] = {
            Point(1, 0, 0),
            Point(0, 0, 0),
            Point(0, 0, -5),
    };

    Vector Directions[] = {
            Vector(0, 1, 0),
            Vector(0, 1, 0),
            Vector(1, 1, 1),
    };

    int i;
    for(i = 0; i < 3; i++)
    {
        Tuple direction = Directions[i].normalise();
        Ray r = Ray(Origins[i], direction);

        Intersect xs; cyl.intersect(r, xs);

        ASSERT_EQ(xs.count(), 0);
    }
}

TEST(CylinderTest, A_ray_hit_a_cylinder)
{
    Cylinder cyl = Cylinder();

    Point Origins[] = {
            Point(1, 0, -5),
            Point(0, 0, -5),
            Point(0.5, 0, -5),
    };

    Vector Directions[] = {
            Vector(0, 0, 1),
            Vector(0, 0, 1),
            Vector(0.1, 1, 1),
    };

    double t0s[] = { 5, 4, 6.80798 };
    double t1s[] = { 5, 6, 7.08872 };

    int i;
    for(i = 0; i < 3; i++)
    {
        Tuple direction = Directions[i].normalise();
        Ray r = Ray(Origins[i], direction);

        Intersect xs; cyl.intersect(r, xs);

        /* Temporary lower the precision */
        set_equal_precision(0.00001);

        ASSERT_EQ(xs.count(), 2);
        EXPECT_TRUE(double_equal(xs[0].t, t0s[i]));
        EXPECT_TRUE(double_equal(xs[1].t, t1s[i]));

        set_equal_precision(FLT_EPSILON);
    }
}

TEST(CylinderTest, Normal_vector_on_a_cylinder)
{
    Cylinder cyl = Cylinder();

    Point HitPointss[] = {
            Point(1, 0, 0),
            Point(0, 5, -1),
            Point(0, -2, 1),
            Point(-1, 1, 0),
    };

    Vector Normals[] = {
            Vector(1, 0, 0),
            Vector(0, 0, -1),
            Vector(0, 0, 1),
            Vector(-1, 0, 0),
    };

    int i;
    for(i = 0; i < 4; i++)
    {
        ASSERT_EQ(cyl.normalAt(HitPointss[i]), Normals[i]);
    }
}

TEST(CylinderTest, The_default_minimum_and_maximum_for_a_cylinder)
{
    Cylinder cyl = Cylinder();
    ASSERT_EQ(cyl.minCap, -INFINITY);
    ASSERT_EQ(cyl.maxCap, INFINITY);
}

TEST(CylinderTest, Intersecting_a_constrained_cylinder)
{
    Point Origins[] = {
            Point(0, 1.5, 0),
            Point(0, 3, -5),
            Point(0, 0, -5),
            Point(0, 2, -5),
            Point(0, 1, -5),
            Point(0, 1.5, -2),
    };

    Vector Directions[] = {
            Vector(0.1, 1, 0),
            Vector(0, 0, 1),
            Vector(0, 0, 1),
            Vector(0, 0, 1),
            Vector(0, 0, 1),
            Vector(0., 0, 1),
    };

    uint32_t Counts[] = { 0, 0, 0, 0, 0, 2 };

    Cylinder cyl = Cylinder();
    cyl.minCap = 1;
    cyl.maxCap = 2;

    int i;
    for(i = 0; i < 6; i++)
    {
        Tuple direction = Directions[i].normalise();
        Ray r = Ray(Origins[i], direction);

        Intersect xs; cyl.intersect(r, xs);

        ASSERT_EQ(xs.count(), Counts[i]);
    }
}

TEST(CylinderTest, The_default_closed_value_for_a_cylinder)
{
    Cylinder cyl = Cylinder();
    ASSERT_EQ(cyl.isClosed, false);
}
TEST(CylinderTest, Intersecting_the_caps_of_a_close_cylinder)
{
    Point Origins[] = {
            Point(0, 3, 0),
            Point(0, 3, -2),
            Point(0, 4, -2),  /* Edge case */
            Point(0, 0, -5),
            Point(0, -1, -2), /* Edge case */
    };

    Vector Directions[] = {
            Vector(0, -1, 0),
            Vector(0, -1, 2),
            Vector(0, -1, 1),
            Vector(0, 1, 2),
            Vector(0, 1, 1),
     };

    uint32_t Counts[] = { 2, 2, 2, 2, 2 };

    Cylinder cyl = Cylinder();
    cyl.minCap = 1;
    cyl.maxCap = 2;
    cyl.isClosed = true;

    int i;
    for(i = 0; i < 5; i++)
    {
        Tuple direction = Directions[i].normalise();
        Ray r = Ray(Origins[i], direction);

        Intersect xs; cyl.intersect(r, xs);
        ASSERT_EQ(xs.count(), Counts[i]);
    }
}

TEST(CylinderTest, The_normal_on_a_cylinder_end_cap)
{
    Cylinder cyl = Cylinder();

    Point HitPointss[] = {
            Point(0, 1, 0),
            Point(0.5, 1, 0),
            Point(0, 1, 0.5),
            Point(0, 2, 0),
            Point(0.5, 2, 0),
            Point(0, 2, 0.5),
    };

    Vector Normals[] = {
            Vector(0, -1, 0),
            Vector(0, -1, 0),
            Vector(0, -1, 0),
            Vector(0, 1, 0),
            Vector(0, 1, 0),
            Vector(0, 1, 0),
    };

    cyl.minCap = 1;
    cyl.maxCap = 2;
    cyl.isClosed = true;

    int idx;
    for(idx = 0; idx < 6; idx++)
    {
        ASSERT_EQ(cyl.normalAt(HitPointss[idx]), Normals[idx]);
    }
}

TEST(CylinderTest, The_bounding_box_of_a_cut_cylinder)
{
    Cylinder t = Cylinder();
    BoundingBox b = BoundingBox(Point(-1, -10000, -1), Point(1, 10000, 1));
    t.minCap = -10000;
    t.maxCap = 10000;
    BoundingBox res = t.getBounds();

    ASSERT_EQ(res.min, b.min);
    ASSERT_EQ(res.max, b.max);
}

TEST(CylinderTest, The_bounding_box_of_a_uncut_cylinder)
{
    /* This one is tricky. Infinite size don't cope well with transformations */
    Cylinder t = Cylinder();
    BoundingBox res = t.getBounds();

    ASSERT_FALSE(res.min.isRepresentable());
    ASSERT_FALSE(res.max.isRepresentable());
}

TEST(CylinderTest, An_uncut_cylinder_have_infinite_bounds)
{
    Cylinder t = Cylinder();

    ASSERT_FALSE(t.haveFiniteBounds());
}

TEST(CylinderTest, A_cut_cylinder_have_finite_bounds)
{
    Cylinder t = Cylinder();
    t.minCap = -5;
    t.maxCap = 3;
    BoundingBox res = t.getBounds();
    ASSERT_TRUE(t.haveFiniteBounds());
    ASSERT_EQ(res.min, Point(-1, -5, -1));
    ASSERT_EQ(res.max, Point(1, 3, 1));
}