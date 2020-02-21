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
#include <plane.h>


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

TEST(WorldTest, There_is_no_shadow_when_nothing_is_collinear_with_point_and_light)
{
    World w = DefaultWorld();
    Tuple p = Point(0, 10, 0);

    ASSERT_FALSE(w.isShadowed(p));
}

TEST(WorldTest, The_shadow_when_an_object_is_between_the_point_and_the_light)
{
    World w = DefaultWorld();
    Tuple p = Point(10, -10, 10);

    ASSERT_TRUE(w.isShadowed(p));
}

TEST(WorldTest, There_is_no_shadow_whne_an_object_is_behing_the_light)
{
    World w = DefaultWorld();
    Tuple p = Point(-20, 20, -20);

    ASSERT_FALSE(w.isShadowed(p));
}

TEST(WorldTest, There_is_no_shadow_when_an_object_is_behing_the_point)
{
    World w = DefaultWorld();
    Tuple p = Point(-2, 2, -2);

    ASSERT_FALSE(w.isShadowed(p));
}

TEST(WorldTest, Shade_hit_is_given_an_intersection_in_shadow)
{
    World w = World();

    Light l = Light(POINT_LIGHT, Point(0, 0, -10), Colour(1, 1, 1));
    w.addLight(&l);

    Sphere s1 = Sphere();

    w.addObject(&s1);

    Sphere s2 = Sphere();
    s2.setTransform(translation(0, 0, 10));

    w.addObject(&s2);

    Ray r = Ray(Point(0, 0, 5), Vector(0, 0, 1));
    Intersection i = Intersection(4, &s2);
    Computation comps = i.prepareComputation(r);
    Tuple c = w.shadeHit(comps);

    ASSERT_EQ(c, Colour(0.1, 0.1, 0.1));
};

TEST(WorldTest, The_reflected_colour_for_a_non_reflective_material)
{
    World w = DefaultWorld();
    Ray r = Ray(Point(0, 0, 0), Vector(0, 0, 1));

    Shape *shape = w.getObject(1); /* The second object */
    shape->material.ambient = 1; /* We use this to get a predictable colour */

    Intersection i = Intersection(1, shape);

    Computation comps = i.prepareComputation(r);
    Colour colour = w.reflectColour(comps);

    ASSERT_EQ(colour, Colour(0, 0, 0));
}

TEST(WorldTest, The_reflected_colour_for_a_reflective_material)
{
    World w = DefaultWorld();
    Plane shape = Plane();
    shape.material.reflective = 0.5;
    shape.setTransform(translation(0, -1, 0));
    w.addObject(&shape);

    Ray r = Ray(Point(0, 0, -3), Vector(0, -sqrt(2)/2, sqrt(2)/2));

    Intersection i = Intersection(sqrt(2), &shape);

    Computation comps = i.prepareComputation(r);
    Colour colour = w.reflectColour(comps);

    /* Temporary lower the precision */
    set_equal_precision(0.00002);

    ASSERT_EQ(colour, Colour(0.19032, 0.2379, 0.14274));

    set_equal_precision(FLT_EPSILON);
}

TEST(WorldTest, Shade_hit_with_a_reflective_material)
{
    World w = DefaultWorld();
    Plane shape = Plane();
    shape.material.reflective = 0.5;
    shape.setTransform(translation(0, -1, 0));
    w.addObject(&shape);

    Ray r = Ray(Point(0, 0, -3), Vector(0, -sqrt(2)/2, sqrt(2)/2));

    Intersection i = Intersection(sqrt(2), &shape);

    Computation comps = i.prepareComputation(r);
    Tuple colour = w.shadeHit(comps);

    /* Temporary lower the precision */
    set_equal_precision(0.00005);

    ASSERT_EQ(colour, Colour(0.87677, 0.92436, 0.82918));

    set_equal_precision(FLT_EPSILON);
}

TEST(WorldTest, Colour_at_with_mutually_reflective_surfaces)
{
    World w = World();

    Light l = Light(POINT_LIGHT, Point(0, 0, 0), Colour(1, 1, 1));

    w.addLight(&l);

    Plane lower = Plane();
    lower.material.reflective = 1;
    lower.setTransform(translation(0, -1, 0));

    Plane higher = Plane();
    higher.material.reflective = 1;
    higher.setTransform(translation(0, 1, 0));

    w.addObject(&lower);
    w.addObject(&higher);

    Ray r = Ray(Point(0, 0, 0), Vector(0, 1, 0));

    /* It should just exit, we don't care about the actual colour */
    w.colourAt(r);
}

TEST(WorldTest, The_reflected_colour_at_the_maximum_recursion_depth)
{
    World w = DefaultWorld();
    Plane shape = Plane();
    shape.material.reflective = 0.5;
    shape.setTransform(translation(0, -1, 0));
    w.addObject(&shape);

    Ray r = Ray(Point(0, 0, -3), Vector(0, -sqrt(2)/2, sqrt(2)/2));
    Intersection i = Intersection(sqrt(2), &shape);

    Computation comps = i.prepareComputation(r);
    Tuple colour = w.reflectColour(comps, 0);

    /* Temporary lower the precision */
    ASSERT_EQ(colour, Colour(0, 0, 0));
}