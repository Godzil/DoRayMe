/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Light unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <light.h>
#include <math.h>
#include <colour.h>
#include <tuple.h>
#include <gtest/gtest.h>

TEST(LightTest, A_point_lighthas_a_position_and_intensity)
{
    Colour intensity = Colour(1, 1, 1);
    Point position = Point(0, 0, 0);

    Light light = Light(POINT_LIGHT, position, intensity);

    ASSERT_EQ(light.position, position);
    ASSERT_EQ(light.intensity, intensity);
}