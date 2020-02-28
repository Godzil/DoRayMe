/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Boundingbox unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Camera unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <math.h>
#include <math_helper.h>
#include <ray.h>
#include <transformation.h>
#include <stdint.h>
#include <boundingbox.h>
#include <gtest/gtest.h>

TEST(BoundingBoxTest, Creating_an_empty_bounding_box)
{
    BoundingBox bb;

    ASSERT_TRUE(bb.isEmpty());
    ASSERT_EQ(bb.min, Point(INFINITY, INFINITY, INFINITY));
    ASSERT_EQ(bb.max, Point(-INFINITY, -INFINITY, -INFINITY));
}

TEST(BoundingBoxTest, Crteating_a_bounding_box_with_volume)
{
    BoundingBox bb = BoundingBox(Point(-1, -2, -3), Point(3, 2, 1));

    ASSERT_FALSE(bb.isEmpty());
    ASSERT_EQ(bb.min, Point(-1, -2, -3));
    ASSERT_EQ(bb.max, Point(3, 2, 1));
}

TEST(BoundingBoxTest, Adding_on_bouding_to_an_empty_bounding_box)
{
    BoundingBox bb;

    bb | BoundingBox(Point(-1, -1, -1), Point(1, 1, 1));

    ASSERT_FALSE(bb.isEmpty());
    ASSERT_EQ(bb.min, Point(-1, -1, -1));
    ASSERT_EQ(bb.max, Point(1, 1, 1));
}

TEST(BoundingBoxTest, Adding_boudingbox_to_another)
{
    BoundingBox bb(Point(-1, -1, 0), Point(4, 0, 1));

    bb | BoundingBox(Point(-2, 0, -5), Point(4, 5, 0.5));

    ASSERT_FALSE(bb.isEmpty());
    ASSERT_EQ(bb.min, Point(-2, -1, -5));
    ASSERT_EQ(bb.max, Point(4, 5, 1));
}

TEST(BoundingBoxTest, Adding_points_to_an_empty_bounding_box)
{
    BoundingBox bb;

    bb | Point(-5, 2, 0);
    bb | Point(7, 0, -3);

    ASSERT_FALSE(bb.isEmpty());
    ASSERT_EQ(bb.min, Point(-5, 0, -3));
    ASSERT_EQ(bb.max, Point(7, 2, 0));
}

TEST(BoundingBoxTest, A_smaller_bb_should_fit_in_a_bigger)
{
    BoundingBox bigBb = BoundingBox(Point(-10, -10, -10), Point(10, 10, 10));

    BoundingBox smallBb = BoundingBox(Point(-2, -2, -2), Point(2, 2, 2));

    ASSERT_TRUE(bigBb.fitsIn(smallBb));
}

TEST(BoundingBoxTest, A_big_bb_should_not_fit_in_a_smaller)
{
    BoundingBox bigBb = BoundingBox(Point(-10, -10, -10), Point(10, 10, 10));

    BoundingBox smallBb = BoundingBox(Point(-2, -2, -2), Point(2, 2, 2));

    ASSERT_FALSE(smallBb.fitsIn(bigBb));
}
