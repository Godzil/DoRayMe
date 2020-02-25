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

TEST(BoundingBox, Default_boundingbox_is_not_set)
{
    BoundingBox bb;

    ASSERT_TRUE(bb.isEmpty());
    ASSERT_EQ(bb.min, Point(INFINITY, INFINITY, INFINITY));
    ASSERT_EQ(bb.max, Point(-INFINITY, -INFINITY, -INFINITY));
}

TEST(BoundingBox, Bounding_box_can_be_created_with_values)
{
    BoundingBox bb = BoundingBox(Point(-1, -1, -1), Point(1, 1, 1));

    ASSERT_FALSE(bb.isEmpty());
    ASSERT_EQ(bb.min, Point(-1, -1, -1));
    ASSERT_EQ(bb.max, Point(1, 1, 1));
}

TEST(BoundingBox, Cating_a_bb_to_an_empty_bb_reset_the_original_one)
{
    BoundingBox bb;

    bb | BoundingBox(Point(-1, -1, -1), Point(1, 1, 1));

    ASSERT_FALSE(bb.isEmpty());
    ASSERT_EQ(bb.min, Point(-1, -1, -1));
    ASSERT_EQ(bb.max, Point(1, 1, 1));
}

TEST(BoundingBox, Cating_a_bb_to_another_bb_expand_the_original_one_if_needed)
{
    BoundingBox bb(Point(-1, -1, -1), Point(1, 1, 1));

    bb | BoundingBox(Point(-2, 0, -5), Point(4, 5, 0.5));

    ASSERT_FALSE(bb.isEmpty());
    ASSERT_EQ(bb.min, Point(-2, -1, -5));
    ASSERT_EQ(bb.max, Point(4, 5, 1));
}

TEST(BoundingBox, A_smaller_bb_should_fit_in_a_bigger)
{
    BoundingBox bigBb = BoundingBox(Point(-10, -10, -10), Point(10, 10, 10));

    BoundingBox smallBb = BoundingBox(Point(-2, -2, -2), Point(2, 2, 2));

    ASSERT_TRUE(bigBb.fitsIn(smallBb));
}

TEST(BoundingBox, A_big_bb_should_not_fit_in_a_smaller)
{
    BoundingBox bigBb = BoundingBox(Point(-10, -10, -10), Point(10, 10, 10));

    BoundingBox smallBb = BoundingBox(Point(-2, -2, -2), Point(2, 2, 2));

    ASSERT_FALSE(smallBb.fitsIn(bigBb));
}
