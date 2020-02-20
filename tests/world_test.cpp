/*
 *  DoRayMe - a quick and dirty Raytracer
 *  World unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <world.h>
#include <light.h>
#include <sphere.h>
#include <material.h>
#include <transformation.h>
#include <worldbuilder.h>
#include <math.h>
#include <gtest/gtest.h>


TEST(WorldTest, Creating_a_world)
{
    World w;

    ASSERT_EQ(w.lightCount, 0);
    ASSERT_EQ(w.objectCount, 0);
}

TEST(WorldTest, The_default_world)
{
    World w = DefaultWorld();

    Light l = Light(POINT_LIGHT, Point(-10, 10, -10), Colour(1, 1, 1));
    Sphere s1 = Sphere();
    Sphere s2 = Sphere();
    Material s1Mat = Material();
    s1Mat.colour = Colour(0.8, 1.0, 0.6);
    s1Mat.diffuse = 0.7;
    s1Mat.specular = 0.2;
    s1.setMaterial(s1Mat);

    s2.setTransform(scaling(0.5, 0.5,0.5));

    ASSERT_TRUE(w.lightIsIn(l));
    ASSERT_TRUE(w.objectIsIn(s1));
    ASSERT_TRUE(w.objectIsIn(s2));
};

TEST(WorldTest, Intersect_a_world_with_a_ray)
{
    World w = DefaultWorld();
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));

    Intersect xs = w.intersect(r);

    ASSERT_EQ(xs.count(), 4);
    ASSERT_EQ(xs[0].t, 4);
    ASSERT_EQ(xs[1].t, 4.5);
    ASSERT_EQ(xs[2].t, 5.5);
    ASSERT_EQ(xs[3].t, 6);
}

TEST(WorldTest, Shading_an_intersection)
{
    World w = DefaultWorld();
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Shape *s = w.getObject(0);
    Intersection i = Intersection(4, s);
    Computation comps = i.prepareComputation(r);
    Tuple c = w.shadeHit(comps);

    /* Temporary lower the precision */
    set_equal_precision(0.00001);

    ASSERT_EQ(c, Colour(0.38066, 0.47583, 0.2855));

    set_equal_precision(FLT_EPSILON);
}

TEST(WorldTest, The_when_ray_miss)
{
    World w = DefaultWorld();
    Ray r = Ray(Point(0, 0, -5), Vector(0, 1, 0));
    Tuple c = w.colourAt(r);

    ASSERT_EQ(c, Colour(0, 0, 0));
}

TEST(WorldTest, The_when_ray_hit)
{
    World w = DefaultWorld();
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Tuple c = w.colourAt(r);

    /* Temporary lower the precision */
    set_equal_precision(0.00001);

    ASSERT_EQ(c, Colour(0.38066, 0.47583, 0.2855));

    set_equal_precision(FLT_EPSILON);
}

TEST(WorldTest, The_colour_with_an_intersection_behind_the_ray)
{
    World w = DefaultWorld();
    Shape *outer = w.getObject(0);
    outer->material.ambient = 1;
    Shape *inner = w.getObject(1);
    inner->material.ambient = 1;

    Ray r = Ray(Point(0, 0, 0.75), Vector(0, 0, -1));

    Tuple c = w.colourAt(r);

    ASSERT_EQ(c, inner->material.colour);
}