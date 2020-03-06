/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Plane unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */

#include <ray.h>
#include <shape.h>
#include <plane.h>
#include <material.h>
#include <transformation.h>
#include <gtest/gtest.h>

TEST(PlaneTest, The_normal_of_a_plane_is_constant_everywhere)
{
    Plane p = Plane();
    Tuple n1 = p.normalAt(Point(0, 0, 0));
    Tuple n2 = p.normalAt(Point(10, 0, -10));
    Tuple n3 = p.normalAt(Point(-5, 0, 0150));

    ASSERT_EQ(n1, Vector(0, 1, 0));
    ASSERT_EQ(n2, Vector(0, 1, 0));
    ASSERT_EQ(n3, Vector(0, 1, 0));
}

TEST(PlaneTest, Intersect_with_a_ray_parallel_to_the_plane)
{
    Plane p = Plane();
    Ray r = Ray(Point(0, 10, 0), Vector(0, 0, 1));

    Intersect xs = p.intersect(r);

    ASSERT_EQ(xs.count(), 0);
}

TEST(PlaneTest, Intersect_with_a_coplanar_ray)
{
    Plane p = Plane();
    Ray r = Ray(Point(0, 0, 0), Vector(0, 0, 1));

    Intersect xs = p.intersect(r);

    ASSERT_EQ(xs.count(), 0);
}

TEST(PlaneTest, A_ray_intersecting_a_plane_from_above)
{
    Plane p = Plane();
    Ray r = Ray(Point(0, 1, 0), Vector(0, -1, 0));

    Intersect xs = p.intersect(r);

    ASSERT_EQ(xs.count(), 1);
    ASSERT_EQ(xs[0].t, 1);
    ASSERT_EQ(xs[0].object, &p);
}

TEST(PlaneTest, A_ray_intersecting_a_plane_from_below)
{
    Plane p = Plane();
    Ray r = Ray(Point(0, -1, 0), Vector(0, 1, 0));

    Intersect xs = p.intersect(r);

    ASSERT_EQ(xs.count(), 1);
    ASSERT_EQ(xs[0].t, 1);
    ASSERT_EQ(xs[0].object, &p);
}

TEST(PlaneTest, The_bounding_box_of_a_plane)
{
    Plane t = Plane();
    BoundingBox res = t.getBounds();

    ASSERT_FALSE(res.min.isRepresentable());
    ASSERT_FALSE(res.max.isRepresentable());
}

TEST(PlaneTest, A_plane_have_infinite__bounds)
{
    Plane t = Plane();

    ASSERT_FALSE(t.haveFiniteBounds());
}