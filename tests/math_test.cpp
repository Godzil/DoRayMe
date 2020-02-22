/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Math helper unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <math_helper.h>
#include <gtest/gtest.h>

TEST(MathTest, Default_epsilon)
{
    ASSERT_EQ(getEpsilon(), FLT_EPSILON);
}

TEST(MathTest, Check_setting_epsilon)
{
    set_equal_precision(0.00001);

    ASSERT_EQ(getEpsilon(), 0.00001);

    set_equal_precision(FLT_EPSILON);
}

TEST(MathTest, Check_double_equal_is_working)
{
    ASSERT_TRUE(double_equal(0 - DBL_EPSILON, 0));

    ASSERT_FALSE(double_equal(0 - FLT_EPSILON, 0));
    ASSERT_TRUE(double_equal(0 - FLT_EPSILON/2.0, 0));

    ASSERT_FALSE(double_equal(0 - 0.001, 0));
    ASSERT_FALSE(double_equal(0 - 0.00001, 0));
    ASSERT_FALSE(double_equal(0 - 0.000001, 0));

    set_equal_precision(0.00001);
    ASSERT_TRUE(double_equal(0 - FLT_EPSILON*2, 0));
    ASSERT_FALSE(double_equal(0 - 0.001, 0));
    ASSERT_FALSE(double_equal(0 - 0.00001, 0));
    ASSERT_TRUE(double_equal(0 - 0.000001, 0));

    set_equal_precision(FLT_EPSILON);
}



TEST(MathTest, Check_that_deg_to_rad_is_working)
{
    double angle180 = deg_to_rad(180);
    double angle90 = deg_to_rad(90);
    double angle270 = deg_to_rad(270);

    ASSERT_EQ(angle180, M_PI);
    ASSERT_EQ(angle90, M_PI / 2.);
    ASSERT_EQ(angle270, M_PI * 1.5);
}

TEST(MathTest, Min_is_working)
{
    ASSERT_EQ(min3(1, 2, 3), 1);
    ASSERT_EQ(min3(1, 3, 2), 1);
    ASSERT_EQ(min3(2, 1, 3), 1);
    ASSERT_EQ(min3(2, 3, 1), 1);
    ASSERT_EQ(min3(3, 1, 2), 1);
    ASSERT_EQ(min3(3, 2, 1), 1);

    ASSERT_EQ(min3(1, 2, 2), 1);
    ASSERT_EQ(min3(2, 1, 2), 1);
    ASSERT_EQ(min3(2, 2, 1), 1);

    ASSERT_EQ(min3(3, 2, 2), 2);
    ASSERT_EQ(min3(2, 3, 2), 2);
    ASSERT_EQ(min3(2, 2, 3), 2);

    ASSERT_EQ(min3(2, 2, 2), 2);
}

TEST(MathTest, Max_is_working)
{
    ASSERT_EQ(max3(1, 2, 3), 3);
    ASSERT_EQ(max3(1, 3, 2), 3);
    ASSERT_EQ(max3(2, 1, 3), 3);
    ASSERT_EQ(max3(2, 3, 1), 3);
    ASSERT_EQ(max3(3, 1, 2), 3);
    ASSERT_EQ(max3(3, 2, 1), 3);

    ASSERT_EQ(max3(1, 2, 2), 2);
    ASSERT_EQ(max3(2, 1, 2), 2);
    ASSERT_EQ(max3(2, 2, 1), 2);

    ASSERT_EQ(max3(3, 2, 2), 3);
    ASSERT_EQ(max3(2, 3, 2), 3);
    ASSERT_EQ(max3(2, 2, 3), 3);

    ASSERT_EQ(max3(2, 2, 2), 2);
}