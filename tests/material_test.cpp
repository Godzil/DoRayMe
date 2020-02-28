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
#include <world.h>
#include <worldbuilder.h>

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
    double lightLevel = 0.0;

    Colour result = m.lighting(light, position, eyev, normalv, &t, lightLevel);

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

TEST(MaterialTest, Equality_tests)
{
    Material m = Material();
    Material m2 = Material();

    ASSERT_EQ(m, m2);

    m.ambient = 42;
    ASSERT_NE(m, m2);
    m.ambient = m2.ambient;

    m.diffuse = 42;
    ASSERT_NE(m, m2);
    m.diffuse = m2.diffuse;

    m.specular = 42;
    ASSERT_NE(m, m2);
    m.specular = m2.specular;

    m.shininess = 42;
    ASSERT_NE(m, m2);
    m.shininess = m2.shininess;

    m.reflective = 42;
    ASSERT_NE(m, m2);
    m.reflective = m2.reflective;

    m.transparency = 42;
    ASSERT_NE(m, m2);
    m.transparency = m2.transparency;

    m.emissive = 42;
    ASSERT_NE(m, m2);
    m.emissive = m2.emissive;

    m.refractiveIndex = 42;
    ASSERT_NE(m, m2);
    m.refractiveIndex = m2.refractiveIndex;

    m.colour = Colour(32, 32, 32);
    ASSERT_NE(m, m2);
}

TEST(MaterialTest, lighting_uses_light_intensity_to_attenuate_colour)
{
    World w = DefaultWorld();
    Light *light = w.getLight(0);
    Shape *shape = w.getObject(0);

    light->position = Point(0, 0, -10);
    light->intensity = Colour(1, 1, 1);

    shape->material.ambient = 0.1;
    shape->material.diffuse = 0.9;
    shape->material.specular = 0;
    shape->material.colour = Colour(1, 1, 1);
    Tuple pt = Point(0, 0, -1);
    Tuple eyev = Vector(0, 0, -1);
    Tuple normalv = Vector(0, 0, -1);

    double testList[] = {
            1.0,
            0.5,
            0.0,
    };

    Colour testResult[] = {
            Colour(1, 1, 1),
            Colour(0.55, 0.55, 0.55),
            Colour(0.1, 0.1, 0.1),
    };

    int testCount = sizeof(testList)/sizeof((testList)[0]);
    int i;

    for(i = 0; i < testCount; i++)
    {
        ASSERT_EQ(shape->material.lighting(*light, pt, eyev, normalv, shape, testList[i]), testResult[i]);
    }

}