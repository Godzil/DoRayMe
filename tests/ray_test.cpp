/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Ray unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <ray.h>
#include <gtest/gtest.h>


TEST(RayTest, Creating_a_ray_and_querying_it)
{
    Point origin = Point(1, 2, 3);
    Vector direction = Vector(4, 5, 6);

    Ray r = Ray(origin, direction);

    ASSERT_EQ(r.origin, origin);
    ASSERT_EQ(r.direction, direction);
}

TEST(RayTest, Computing_a_point_from_a_distance)
{
    Ray r = Ray(Point(2, 3, 4), Vector(1, 0, 0));

    ASSERT_EQ(r.position(0), Point(2, 3, 4));
    ASSERT_EQ(r.position(1), Point(3, 3, 4));
    ASSERT_EQ(r.position(-1), Point(1, 3, 4));
    ASSERT_EQ(r.position(2.5), Point(4.5, 3, 4));
}