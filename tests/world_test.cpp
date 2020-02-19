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

