/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Colour unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <colour.h>
#include <math.h>
#include <gtest/gtest.h>

TEST(ColourTest, Color_is_tuple)
{
    Colour c = Colour(-0.5, 0.4, 1.7);

    ASSERT_EQ(c.red(), -0.5);
    ASSERT_EQ(c.green(), 0.4);
    ASSERT_EQ(c.blue(), 1.7);
}

TEST(ColourTest, Adding_colours)
{
    Colour c1 = Colour(0.9, 0.6, 0.75);
    Colour c2 = Colour(0.7, 0.1, 0.25);

    ASSERT_EQ(c1 + c2, Colour(1.6, 0.7, 1.0));
}

TEST(ColourTest, Substracting_colours)
{
    Colour c1 = Colour(0.9, 0.6, 0.75);
    Colour c2 = Colour(0.7, 0.1, 0.25);

    ASSERT_EQ(c1 - c2, Colour(0.2, 0.5, 0.5));
}

TEST(ColourTest, Multiplying_colour_by_a_scalar)
{
    Colour c = Colour(0.2, 0.3, 0.4);

    ASSERT_EQ(c * 2, Colour(0.4, 0.6, 0.8));
}

TEST(ColourTest, Multiplying_colours)
{
    Colour c1 = Colour(1, 0.2, 0.4);
    Colour c2 = Colour(0.9, 1, 0.1);

    ASSERT_EQ(c1 * c2, Colour(0.9, 0.2, 0.04));
}