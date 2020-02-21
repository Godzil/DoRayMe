/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Pattern unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */

#include <pattern.h>
#include <strippattern.h>
#include <gradientpattern.h>
#include <ringpattern.h>
#include <testpattern.h>
#include <transformation.h>
#include <colour.h>
#include <sphere.h>
#include <gtest/gtest.h>
#include <material.h>

Colour black = Colour(0, 0, 0);
Colour white = Colour(1, 1, 1);

TEST(PatternTest, Creating_a_stripe_pattern)
{
    StripPattern p = StripPattern(white, black);

    ASSERT_EQ(p.a, white);
    ASSERT_EQ(p.b, black);
}

TEST(PatternTest, A_strip_pattern_is_constant_in_y)
{
    StripPattern p = StripPattern(white, black);

    ASSERT_EQ(p.patternAt(Point(0, 0, 0)), white);
    ASSERT_EQ(p.patternAt(Point(0, 1, 0)), white);
    ASSERT_EQ(p.patternAt(Point(0, 2, 0)), white);
}

TEST(PatternTest, A_strip_pattern_is_constant_in_z)
{
    StripPattern p = StripPattern(white, black);

    ASSERT_EQ(p.patternAt(Point(0, 0, 0)), white);
    ASSERT_EQ(p.patternAt(Point(0, 0, 1)), white);
    ASSERT_EQ(p.patternAt(Point(0, 0, 2)), white);
}

TEST(PatternTest, A_strip_pattern_alternate_in_x)
{
    StripPattern p = StripPattern(white, black);

    ASSERT_EQ(p.patternAt(Point(0, 0, 0)), white);
    ASSERT_EQ(p.patternAt(Point(0.9, 0, 0)), white);
    ASSERT_EQ(p.patternAt(Point(1, 0, 0)), black);
    ASSERT_EQ(p.patternAt(Point(-0.1, 0, 0)), black);
    ASSERT_EQ(p.patternAt(Point(-1, 0, 0)), black);
    ASSERT_EQ(p.patternAt(Point(-1.1, 0, 0)), white);
}

TEST(PatternTest, Lightning_with_a_pattern_applied)
{
    Sphere s = Sphere();
    Material m;
    StripPattern p = StripPattern(white, black);
    m.pattern = &p;
    m.ambient = 1;
    m.diffuse = 0;
    m.specular = 0;

    Tuple eyev = Vector(0, 0, -1);
    Tuple normalv = Vector(0, 0, -1);
    Light light = Light(POINT_LIGHT, Point(0, 0, -10), Colour(1, 1, 1));

    Colour c1 = m.lighting(light, Point(0, 9, 0), eyev, normalv, &s, false);
    Colour c2 = m.lighting(light, Point(1, 1, 0), eyev, normalv, &s, false);

    ASSERT_EQ(c1, Colour(1, 1, 1));
    ASSERT_EQ(c2, Colour(0, 0, 0));
}

TEST(PatternTest, Stripe_with_an_object_transformation)
{
    Sphere s = Sphere();
    s.setTransform(scaling(2, 2, 2));
    StripPattern pattern = StripPattern(white, black);
    Colour c = pattern.patternAtObject(&s, Point(1.5, 0, 0));

    ASSERT_EQ(c, white);
}

TEST(PatternTest, Stripe_with_a_pattern_transformation)
{
    Sphere s = Sphere();
    StripPattern pattern = StripPattern(white, black);
    pattern.setTransform(scaling(2, 2, 2));
    Colour c = pattern.patternAtObject(&s, Point(1.5, 0, 0));

    ASSERT_EQ(c, white);
}

TEST(PatternTest, Stripe_with_both_an_object_and_a_pattern_transformation)
{
    Sphere s = Sphere();
    s.setTransform(scaling(2, 2, 2));
    StripPattern pattern = StripPattern(white, black);
    pattern.setTransform(translation(0.5, 0, 0));

    Colour c = pattern.patternAtObject(&s, Point(2.5, 0, 0));

    ASSERT_EQ(c, white);
}

TEST(PatternTest, The_default_pattern_transformation)
{
    TestPattern pattern = TestPattern();

    ASSERT_EQ(pattern.transformMatrix, Matrix4().identity());
}

TEST(PatternTest, Assigning_a_transformation)
{
    TestPattern pattern = TestPattern();
    pattern.setTransform(translation(1, 2, 3));

    ASSERT_EQ(pattern.transformMatrix, translation(1, 2, 3));
}

TEST(PatternTest, A_pattern_with_an_object_transformation)
{
    Sphere s = Sphere();
    s.setTransform(scaling(2, 2, 2));
    TestPattern pattern = TestPattern();

    Colour c = pattern.patternAtObject(&s, Point(2, 3, 4));

    ASSERT_EQ(c, Colour(1, 1.5, 2));
}

TEST(PatternTest, A_pattern_with_a_pattern_transformation)
{
    Sphere s = Sphere();
    TestPattern pattern = TestPattern();
    pattern.setTransform(scaling(2, 2, 2));

    Colour c = pattern.patternAtObject(&s, Point(2, 3, 4));

    ASSERT_EQ(c, Colour(1, 1.5, 2));
}

TEST(PatternTest, A_pattern_with_an_object_and_a_pattern_transformation)
{
    Sphere s = Sphere();
    s.setTransform(scaling(2, 2, 2));
    TestPattern pattern = TestPattern();
    pattern.setTransform(translation(0.5, 1, 1.5));

    Colour c = pattern.patternAtObject(&s, Point(2.5, 3, 3.5));

    ASSERT_EQ(c, Colour(0.75, 0.5, 0.25));
}

TEST(PatternTest, A_gradient_linearly_interpolates_betweens_colors)
{
    GradientPattern pattern = GradientPattern(white, black);

    ASSERT_EQ(pattern.patternAt(Point(0.25, 0, 0)), Colour(0.75, 0.75, 0.75));
    ASSERT_EQ(pattern.patternAt(Point(0.5, 0, 0)), Colour(0.5, 0.5, 0.5));
    ASSERT_EQ(pattern.patternAt(Point(0.75, 0, 0)), Colour(0.25, 0.25, 0.25));
}

TEST(PatternTest, A_ring_should_extend_in_both_x_and_z)
{
    RingPattern pattern = RingPattern(white, black);

}
