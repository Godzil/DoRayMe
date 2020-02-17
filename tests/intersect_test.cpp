/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Intersect unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <intersect.h>
#include <sphere.h>
#include <gtest/gtest.h>


TEST(IntersectTest, Creating_an_intersect_and_do_some_check)
{
    Intersect i;

    ASSERT_EQ(i.count(), 0);

    i.add(newIntersection(1.0, nullptr));
    i.add(newIntersection(4.2, nullptr));

    ASSERT_EQ(i.count(), 2);

    ASSERT_EQ(i[0]->t, 1.0);
    ASSERT_EQ(i[1]->t, 4.2);
}

TEST(IntersectTest, An_intersection_encapsulate_t_and_object)
{
    Sphere s = Sphere();
    Intersection *i = newIntersection(3.5, &s);

    ASSERT_EQ(i->t, 3.5);
    ASSERT_EQ(i->object, (Object *)&s);
}

TEST(IntersectTest, Aggregating_intersections)
{
    Sphere s = Sphere();
    Intersection *i1 = newIntersection(1, &s);
    Intersection *i2 = newIntersection(2, &s);

    Intersect xs = Intersect();
    xs.add(i1);
    xs.add(i2);

    ASSERT_EQ(xs.count(), 2);
    ASSERT_EQ(xs[0]->t, 1);
    ASSERT_EQ(xs[1]->t, 2);
}