/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Intersect unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <intersect.h>
#include <intersection.h>
#include <sphere.h>
#include <plane.h>
#include <transformation.h>
#include <gtest/gtest.h>

TEST(IntersectTest, Creating_an_intersect_and_do_some_check)
{
    Intersect i;

    ASSERT_EQ(i.count(), 0);

    i.add(Intersection(1.0, nullptr));
    i.add(Intersection(4.2, nullptr));

    ASSERT_EQ(i.count(), 2);

    ASSERT_EQ(i[0].t, 1.0);
    ASSERT_EQ(i[1].t, 4.2);
}

TEST(IntersectTest, An_intersection_encapsulate_t_and_object)
{
    Sphere s = Sphere();
    Intersection i = Intersection(3.5, &s);

    ASSERT_EQ(i.t, 3.5);
    ASSERT_EQ(i.object, (Shape *)&s);
}

TEST(IntersectTest, Aggregating_intersections)
{
    Sphere s = Sphere();
    Intersection i1 = Intersection(1, &s);
    Intersection i2 = Intersection(2, &s);

    Intersect xs = Intersect();
    xs.add(i1);
    xs.add(i2);

    ASSERT_EQ(xs.count(), 2);
    ASSERT_EQ(xs[0].t, 1);
    ASSERT_EQ(xs[1].t, 2);
}

TEST(IntersectTest, Intersect_sets_the_object_on_the_intersection)
{
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s = Sphere();
    Intersect xs = s.intersect(r);

    ASSERT_EQ(xs.count(), 2);
    ASSERT_EQ(xs[0].object, (Shape *)&s);
    ASSERT_EQ(xs[1].object, (Shape *)&s);
}

TEST(IntersectTest, The_hit_when_all_intersection_have_positive_t)
{
    Sphere s = Sphere();
    Intersect xs = Intersect();

    Intersection i1 = Intersection(1, &s);
    Intersection i2 = Intersection(2, &s);

    xs.add(i1);
    xs.add(i2);

    Intersection i = xs.hit();

    ASSERT_EQ(i, i1);
}

TEST(IntersectTest, The_hit_when_some_intersection_have_negative_t)
{
    Sphere s = Sphere();
    Intersect xs = Intersect();

    Intersection i1 = Intersection(-1, &s);
    Intersection i2 = Intersection(2, &s);
    Intersection i3 = Intersection(12, &s);

    xs.add(i1);
    xs.add(i2);
    xs.add(i3);

    Intersection i = xs.hit();

    ASSERT_EQ(i, i2);
}

TEST(IntersectTest, The_hit_when_all_intersection_have_negative_t)
{
    Sphere s = Sphere();
    Intersect xs = Intersect();

    Intersection i1 = Intersection(-2, &s);
    Intersection i2 = Intersection(-1, &s);

    xs.add(i1);
    xs.add(i2);

    Intersection i = xs.hit();

    ASSERT_TRUE(i.nothing());
}

TEST(IntersectTest, The_hit_is_always_the_lowest_nonnegative_intersection)
{
    Sphere s = Sphere();
    Intersect xs = Intersect();

    Intersection i1 = Intersection(5, &s);
    Intersection i2 = Intersection(7, &s);
    Intersection i3 = Intersection(-3, &s);
    Intersection i4 = Intersection(2, &s);

    xs.add(i1);
    xs.add(i2);
    xs.add(i3);
    xs.add(i4);

    Intersection i = xs.hit();

    ASSERT_EQ(i, i4);
}

TEST(IntersectTest, Precomputing_the_state_of_an_intersection)
{
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere shape = Sphere();
    Intersection i = Intersection(4, &shape);

    Computation comps = i.prepareComputation(r);

    ASSERT_EQ(comps.t, i.t);
    ASSERT_EQ(comps.object, i.object);
    ASSERT_EQ(comps.hitPoint, Point(0, 0, -1));
    ASSERT_EQ(comps.eyeVector, Vector(0, 0, -1));
    ASSERT_EQ(comps.normalVector, Vector(0, 0, -1));

}

TEST(IntersectTest, The_hit_when_an_intersection_occurs_on_the_outside)
{
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere shape = Sphere();
    Intersection i = Intersection(4, &shape);

    Computation comps = i.prepareComputation(r);

    ASSERT_EQ(comps.inside, false);
}

TEST(IntersectTest, The_hit_when_an_intersection_occurs_on_the_inside)
{
    Ray r = Ray(Point(0, 0, 0), Vector(0, 0, 1));
    Sphere shape = Sphere();
    Intersection i = Intersection(1, &shape);

    Computation comps = i.prepareComputation(r);
    ASSERT_EQ(comps.hitPoint, Point(0, 0, 1));
    ASSERT_EQ(comps.eyeVector, Vector(0, 0, -1));
    ASSERT_EQ(comps.inside, true);

    /* Normal vector would have been (0, 0, 1); but is inverted ! */

    ASSERT_EQ(comps.normalVector, Vector(0, 0, -1));
}

TEST(IntersectTest, The_hit_should_offset_the_point)
{
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere shape = Sphere();
    shape.setTransform(translation(0, 0, 1));

    Intersection i = Intersection(5, &shape);

    Computation comps = i.prepareComputation(r);

    /* Normal vector would have been (0, 0, 1); but is inverted ! */

    ASSERT_LT(comps.overHitPoint.z, -getEpsilon() / 2);
    ASSERT_GT(comps.hitPoint.z, comps.overHitPoint.z);
}

TEST(IntersectTest, Precomputing_the_reflection_vector)
{
    Plane s = Plane();
    Ray r = Ray(Point(0, 1, -1), Vector(0, -sqrt(2) / 2, sqrt(2) / 2));
    Intersection i = Intersection(sqrt(2), &s);

    Computation comps = i.prepareComputation(r);

    ASSERT_EQ(comps.reflectVector, Vector(0, sqrt(2) / 2, sqrt(2) / 2));
}