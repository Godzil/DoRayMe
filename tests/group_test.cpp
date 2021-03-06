/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Group unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <intersect.h>
#include <intersection.h>
#include <group.h>
#include <testshape.h>
#include <sphere.h>

#include <transformation.h>
#include <gtest/gtest.h>

TEST(GroupTest, Creating_a_new_group)
{
    Group g = Group();

    ASSERT_EQ(g.transformMatrix, Matrix4().identity());
    ASSERT_TRUE(g.isEmpty());
}

TEST(GroupTest, Adding_a_child_to_a_group)
{
    Group g = Group();
    TestShape s = TestShape();

    g.addObject(&s);

    ASSERT_FALSE(g.isEmpty());
    ASSERT_EQ(s.parent, &g);
    ASSERT_EQ(g[0], &s);
}

TEST(GroupTest, Intersecting_a_ray_with_an_empty_group)
{
    Group g = Group();
    Ray r = Ray(Point(0, 0, 0), Vector(0, 0, 1));
    Intersect xs; g.intersect(r, xs);
    ASSERT_EQ(xs.count(), 0);
}

TEST(GroupTest, Intersecting_a_ray_with_an_nonempty_group)
{
    Group g = Group();
    Sphere s1 = Sphere();
    Sphere s2 = Sphere();
    Sphere s3 = Sphere();

    s2.setTransform(translation(0, 0, -3));
    s3.setTransform(translation(5, 0, 0));

    g.addObject(&s1);
    g.addObject(&s2);
    g.addObject(&s3);

    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Intersect xs; g.intersect(r, xs);
    ASSERT_EQ(xs.count(), 4);
    EXPECT_EQ(xs[0].object, &s2);
    EXPECT_EQ(xs[1].object, &s2);
    EXPECT_EQ(xs[2].object, &s1);
    EXPECT_EQ(xs[3].object, &s1);
}

TEST(GroupTest, Intersecting_a_transformed_group)
{
    Group g = Group();
    Sphere s = Sphere();

    g.setTransform(scaling(2, 2, 2));
    s.setTransform(translation(5, 0, 0));

    g.addObject(&s);

    Ray r = Ray(Point(10, 0, -50), Vector(0, 0, 1));
    Intersect xs; g.intersect(r, xs);
    ASSERT_EQ(xs.count(), 2);
}

TEST(GroupTest, Group_bounding_box)
{
    Group g = Group();
    Sphere s = Sphere();

    g.setTransform(scaling(2, 2, 2));
    s.setTransform(translation(5, 0, 0));

    g.addObject(&s);

    BoundingBox b = BoundingBox(Point(8, -2, -2), Point(12, 2, 2));

    BoundingBox res = g.getBounds();

    ASSERT_EQ(res.min, b.min);
    ASSERT_EQ(res.max, b.max);
}

TEST(GroupTest, Removing_an_object)
{
    Group g = Group();
    Sphere s1 = Sphere();
    Sphere s2 = Sphere();
    Sphere s3 = Sphere();

    s1.setTransform(translation(-1, 0, 0));
    s2.setTransform(scaling(0.5, 0.5, 0.5));

    g.addObject(&s1);
    g.addObject(&s2);

    ASSERT_EQ(g.getObjectCount(), 2);
    ASSERT_EQ(*(g[0]), s1);
    ASSERT_EQ(*(g[1]), s2);

    g.removeObject(&s1);

    ASSERT_EQ(g.getObjectCount(), 1);
    ASSERT_EQ(*(g[0]), s2);
    ASSERT_EQ(g[1], nullptr);

    g.removeObject(&s3);
    ASSERT_EQ(g.getObjectCount(), 1);

    g.removeObject(&s2);
    ASSERT_EQ(g.getObjectCount(), 0);
    ASSERT_EQ(g[0], nullptr);
}

