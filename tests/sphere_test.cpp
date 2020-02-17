/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Sphere unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <ray.h>
#include <sphere.h>
#include <gtest/gtest.h>


TEST(SphereTest, A_ray_intersect_a_sphere_at_two_points)
{
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s = Sphere();
    Intersect xs = s.intersect(r);

    ASSERT_EQ(xs.count(), 2);
    ASSERT_EQ(xs[0]->t, 4.0);
    ASSERT_EQ(xs[1]->t, 6.0);
}

TEST(SphereTest, A_ray_intersect_a_sphere_at_a_tangent)
{
    Ray r = Ray(Point(0, 1, -5), Vector(0, 0, 1));
    Sphere s = Sphere();
    Intersect xs = s.intersect(r);

    ASSERT_EQ(xs.count(), 2);
    ASSERT_EQ(xs[0]->t, 5.0);
    ASSERT_EQ(xs[1]->t, 5.0);
}

TEST(SphereTest, A_ray_miss_a_sphere)
{
    Ray r = Ray(Point(0, 2, -5), Vector(0, 0, 1));
    Sphere s = Sphere();
    Intersect xs = s.intersect(r);

    ASSERT_EQ(xs.count(), 0);
}

TEST(SphereTest, A_ray_originate_inside_a_sphere)
{
    Ray r = Ray(Point(0, 0, 0), Vector(0, 0, 1));
    Sphere s = Sphere();
    Intersect xs = s.intersect(r);

    ASSERT_EQ(xs.count(), 2);
    ASSERT_EQ(xs[0]->t, -1.0);
    ASSERT_EQ(xs[1]->t, 1.0);
}

TEST(SphereTest, A_sphere_is_behind_a_ray)
{
    Ray r = Ray(Point(0, 0, 5), Vector(0, 0, 1));
    Sphere s = Sphere();
    Intersect xs = s.intersect(r);

    ASSERT_EQ(xs.count(), 2);
    ASSERT_EQ(xs[0]->t, -6.0);
    ASSERT_EQ(xs[1]->t, -4.0);
}