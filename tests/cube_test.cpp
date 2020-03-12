/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Cube unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <intersect.h>
#include <intersection.h>
#include <cube.h>
#include <transformation.h>
#include <gtest/gtest.h>

TEST(CubeTest, A_ray_intersects_a_cube)
{
    Cube c = Cube();

    Point Origins[] = {
            Point(5, 0.5, 0),
            Point(-5, 0.5, 0),
            Point(0.5, 5, 0),
            Point(0.5, -5, 0),
            Point(0.5, 0, 5),
            Point(0.5, 0, -5),
            Point(0, 0.5, 0),
    };

    Vector Directions[] = {
            Vector(-1, 0, 0),
            Vector(1, 0, 0),
            Vector(0, -1, 0),
            Vector(0, 1, 0),
            Vector(0, 0, -1),
            Vector(0, 0, 1),
            Vector(0, 0, 1),
    };

    double t1[] = { 4, 4, 4, 4, 4, 4, -1 };
    double t2[] = { 6, 6, 6, 6, 6, 6, 1 };

    int i;
    for(i = 0; i < 7; i++)
    {
        Ray r = Ray(Origins[i], Directions[i]);
        Intersect xs; c.intersect(r, xs);

        ASSERT_EQ(xs.count(), 2);
        EXPECT_EQ(xs[0].t, t1[i]);
        EXPECT_EQ(xs[1].t, t2[i]);
    }
}

TEST(CubeTest, A_ray_miss_a_cube)
{
    Cube c = Cube();

    Point Origins[] = {
            Point(-2, 0, 0),
            Point(0, -2, 0),
            Point(0, 0, -2),
            Point(2, 0, 2),
            Point(0, 2, 2),
            Point(2, 2, 0),
    };

    Vector Directions[] = {
            Vector(0.2673, 0.5345, 0.8018),
            Vector(0.8018, 0.2673, 0.5345),
            Vector(0.5345, 0.8018, 0.2673),
            Vector(0, 0, -1),
            Vector(0, -1, 0),
            Vector(-1, 0, 0),
    };

    int i;
    for(i = 0; i < 6; i++)
    {
        Ray r = Ray(Origins[i], Directions[i]);
        Intersect xs; c.intersect(r, xs);

        ASSERT_EQ(xs.count(), 0);
    }
}

TEST(CubeTest, The_normal_on_the_surface_of_a_cube)
{
    Cube c = Cube();

    Point HitPoints[] = {
            Point(1, 0.5, -0.8),
            Point(-1, -0.2, 0.9),
            Point(-0.4, 1, -0.1),
            Point(0.3, -1, -0.7),
            Point(-0.6, 0.3, 1),
            Point(0.4, 0.4, -1),
            Point(1, 1, 1),
            Point(-1, -1, -1),
    };

    Vector ExpectedNormals[] = {
            Vector(1, 0, 0),
            Vector(-1, 0, 0),
            Vector(0, 1, 0),
            Vector(0, -1, 0),
            Vector(0, 0, 1),
            Vector(0, 0, -1),
            Vector(1, 0, 0),
            Vector(-1, 0, 0),
    };

    int i;
    for(i = 0; i < 8; i++)
    {
        ASSERT_EQ(c.normalAt(HitPoints[i]), ExpectedNormals[i]);
    }
}

TEST(CubeTest, The_bounding_box_of_a_cube)
{
    Cube t = Cube();
    Tuple boxMin = Point(-1, -1, -1);
    Tuple boxMax = Point(1, 1, 1);

    BoundingBox res = t.getBounds();

    ASSERT_EQ(res.min, boxMin);
    ASSERT_EQ(res.max, boxMax);
}

TEST(CubeTest, A_cube_have_finite_bounds)
{
    Cube t = Cube();

    ASSERT_TRUE(t.haveFiniteBounds());
}