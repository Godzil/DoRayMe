/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Material unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <material.h>
#include <math.h>
#include <colour.h>
#include <testshape.h>
#include <gtest/gtest.h>

TEST(MaterialTest, The_default_material)
{
    Material m = Material();

    ASSERT_EQ(m.colour, Colour(1, 1, 1));
    ASSERT_EQ(m.ambient, 0.1);
    ASSERT_EQ(m.diffuse, 0.9);
    ASSERT_EQ(m.specular, 0.9);
    ASSERT_EQ(m.shininess, 200.0);
}

// This is used by the next tests
static Material m = Material();
static Point position = Point(0, 0, 0);

TEST(MaterialTest, Lighting_with_the_eye_between_the_light_and_the_surface)
{
    TestShape t = TestShape();
    Vector eyev = Vector(0, 0, -1);
    Vector normalv = Vector(0, 0, -1);
    Light light = Light(POINT_LIGHT, Point(0, 0, -10), Colour(1, 1, 1));

    Colour result = m.lighting(light, position, eyev, normalv, &t);

    ASSERT_EQ(result, Colour(1.9, 1.9, 1.9));
}

TEST(MaterialTest, Lighting_with_the_eye_between_the_light_and_the_surface_eye_offset_by_45)
{
    TestShape t = TestShape();
    Vector eyev = Vector(0, -sqrt(2)/2, -sqrt(2)/2);
    Vector normalv = Vector(0, 0, -1);
    Light light = Light(POINT_LIGHT, Point(0, 0, -10), Colour(1, 1, 1));

    Colour result = m.lighting(light, position, eyev, normalv, &t);

    ASSERT_EQ(result, Colour(1.0, 1.0, 1.0));
}

TEST(MaterialTest, Lighting_with_the_eye_opposite_surface_light_offset_45)
{
    TestShape t = TestShape();
    Vector eyev = Vector(0, 0, -1);
    Vector normalv = Vector(0, 0, -1);
    Light light = Light(POINT_LIGHT, Point(0, 10, -10), Colour(1, 1, 1));

    Colour result = m.lighting(light, position, eyev, normalv, &t);

    set_equal_precision(0.0001);

    ASSERT_EQ(result, Colour(0.7364, 0.7364, 0.7364));

    set_equal_precision(FLT_EPSILON);
}

TEST(MaterialTest, Lighting_with_the_eye_in_the_path_of_the_reflection_vector)
{
    TestShape t = TestShape();
    Vector eyev = Vector(0, -sqrt(2)/2, -sqrt(2)/2);
    Vector normalv = Vector(0, 0, -1);
    Light light = Light(POINT_LIGHT, Point(0, 10, -10), Colour(1, 1, 1));

    Colour result = m.lighting(light, position, eyev, normalv, &t);

    set_equal_precision(0.0001);

    ASSERT_EQ(result, Colour(1.6364, 1.6364, 1.6364));

    set_equal_precision(FLT_EPSILON);
}

TEST(MaterialTest, Lighting_with_the_light_behind_the_surface)
{
    TestShape t = TestShape();
    Vector eyev = Vector(0, 0, -1);
    Vector normalv = Vector(0, 0, -1);
    Light light = Light(POINT_LIGHT, Point(0, 0, 10), Colour(1, 1, 1));

    Colour result = m.lighting(light, position, eyev, normalv, &t);

    ASSERT_EQ(result, Colour(0.1, 0.1, 0.1));
}

TEST(MaterialTest, Lighting_with_the_surface_in_shadow)
{
    TestShape t = TestShape();
    Vector eyev = Vector(0, 0, -1);
    Vector normalv = Vector(0, 0, -1);
    Light light = Light(POINT_LIGHT, Point(0, 0, -10), Colour(1, 1, 1));
    bool inShadow = true;

    Colour result = m.lighting(light, position, eyev, normalv, &t, inShadow);

    ASSERT_EQ(result, Colour(0.1, 0.1, 0.1));
}

TEST(MaterialTest, Reflectivity_for_the_default_material)
{
    Material m = Material();

    ASSERT_EQ(m.reflective, 0);
}

TEST(MaterialTest, Transparency_and_refractive_index_for_the_default_material)
{
    Material m = Material();

    ASSERT_EQ(m.transparency, 0.0);
    ASSERT_EQ(m.refractiveIndex, 1.0);
}