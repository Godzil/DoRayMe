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

TEST(IntersectTest, Finding_n1_and_n2_at_various_intersections)
{
    int i;
    double n1_res[6] = { 1.0, 1.5, 2.0, 2.5, 2.5, 1.5 };
    double n2_res[6] = { 1.5, 2.0, 2.5, 2.5, 1.5, 1.0 };

    GlassSphere A = GlassSphere();
    A.setTransform(scaling(2, 2, 2));
    A.material.refractiveIndex = 1.5;

    GlassSphere B = GlassSphere();
    B.setTransform(translation(0, 0, -0.25));
    B.material.refractiveIndex = 2.0;

    GlassSphere C = GlassSphere();
    C.setTransform(translation(0, 0, 0.25));
    C.material.refractiveIndex = 2.5;

    Ray r = Ray(Point(0, 0, -4), Vector(0, 0, 1));
    Intersect xs = Intersect();
    xs.add(Intersection(2.0, &A));
    xs.add(Intersection(2.75, &B));
    xs.add(Intersection(3.25, &C));
    xs.add(Intersection(4.75, &B));
    xs.add(Intersection(5.25, &C));
    xs.add(Intersection(6, &A));

    for(i = 0; i < xs.count(); i++)
    {
        Intersection inter = xs[i];
        Computation comps = inter.prepareComputation(r, &xs);
        ASSERT_EQ(comps.n1, n1_res[i]);
        ASSERT_EQ(comps.n2, n2_res[i]);
    }
}

TEST(IntersectTest, The_under_point_is_offset_below_the_surface)
{
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    GlassSphere shape = GlassSphere();
    shape.setTransform(translation(0, 0, 1));

    Intersection i = Intersection(5, &shape);
    Intersect xs = Intersect();
    xs.add(i);

    Computation comps = i.prepareComputation(r, &xs);

    ASSERT_TRUE(double_equal(comps.underHitPoint.z, getEpsilon() / 2));
    ASSERT_LT(comps.hitPoint.z, comps.underHitPoint.z);
}

TEST(IntersectTest, The_Schlick_approximation_under_total_internal_reflection)
{
    GlassSphere shape = GlassSphere();

    Ray r = Ray(Point(0, 0, sqrt(2)/2), Vector(0, 1, 0));
    Intersect xs = Intersect();
    xs.add(Intersection(-sqrt(2)/2, &shape));
    xs.add(Intersection(sqrt(2)/2, &shape));

    Computation comps = xs[1].prepareComputation(r, &xs);
    double reflectance = comps.schlick();

    ASSERT_EQ(reflectance, 1.0);
}

TEST(IntersectTest, The_Schlick_approximation_with_a_perpendicular_viewing_angle)
{
    GlassSphere shape = GlassSphere();

    Ray r = Ray(Point(0, 0, 0), Vector(0, 1, 0));
    Intersect xs = Intersect();
    xs.add(Intersection(-1, &shape));
    xs.add(Intersection(1, &shape));

    Computation comps = xs[1].prepareComputation(r, &xs);
    double reflectance = comps.schlick();

    ASSERT_TRUE(double_equal(reflectance, 0.04));
}

TEST(IntersectTest, The_Schlick_approximation_with_small_angle_and_n2_gt_n1)
{
    GlassSphere shape = GlassSphere();

    Ray r = Ray(Point(0, 0.99, -2), Vector(0, 0, 1));
    Intersect xs = Intersect();
    xs.add(Intersection(1.8589, &shape));

    Computation comps = xs[0].prepareComputation(r, &xs);
    double reflectance = comps.schlick();

    /* Temporary lower the precision */
    set_equal_precision(0.00001);

    ASSERT_TRUE(double_equal(reflectance, 0.48873));

    set_equal_precision(FLT_EPSILON);
}