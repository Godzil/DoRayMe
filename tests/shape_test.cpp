/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Shape unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <shape.h>
#include <testshape.h>
#include <matrix.h>
#include <group.h>
#include <sphere.h>
#include <transformation.h>
#include <gtest/gtest.h>

TEST(ShapeTest, The_default_transformation)
{
    TestShape s = TestShape();
    ASSERT_EQ(s.transformMatrix, Matrix4().identity());
}

TEST(ShapeTest, Assigning_a_transformation)
{
    TestShape s = TestShape();

    s.setTransform(translation(2, 3, 4));

    ASSERT_EQ(s.transformMatrix, translation(2, 3, 4));
}

TEST(ShapeTest, The_default_material)
{
    TestShape s = TestShape();

    ASSERT_EQ(s.material, Material());
}

TEST(ShapeTest, Assigning_a_material)
{
    TestShape s = TestShape();
    Material m = Material();
    m.ambient = 1;

    s.material = m;

    ASSERT_EQ(s.material, m);
}

TEST(ShapeTest, Intersecting_a_scaled_shape_with_a_ray)
{
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    TestShape s = TestShape();

    s.setTransform(scaling(2, 2, 2));
    Intersect xs = s.intersect(r);

    ASSERT_EQ(s.localRay.origin, Point(0, 0, -2.5));
    ASSERT_EQ(s.localRay.direction, Vector(0, 0, 0.5));
}

TEST(ShapeTest, Intersecting_a_translated_shape_with_a_ray)
{
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    TestShape s = TestShape();

    s.setTransform(translation(5, 0, 0));
    Intersect xs = s.intersect(r);

    ASSERT_EQ(s.localRay.origin, Point(-5, 0, -5));
    ASSERT_EQ(s.localRay.direction, Vector(0, 0, 1));
}

TEST(ShapeTest, Computing_the_normal_on_a_translated_shape)
{
    TestShape s = TestShape();
    s.setTransform(translation(0, 1, 0));
    Tuple n = s.normalAt(Point(0, 1.70711, -0.70711));

    /* Temporary lower the precision */
    set_equal_precision(0.00001);

    ASSERT_EQ(n, Vector(0, 0.70711, -0.70711));

    set_equal_precision(FLT_EPSILON);
}

TEST(ShapeTest, Computing_the_normal_on_a_tranformed_shape)
{
    TestShape s = TestShape();
    s.setTransform(scaling(1, 0.5, 1) * rotationZ(M_PI / 5));
    Tuple n = s.normalAt(Point(0, sqrt(2)/2, -sqrt(2)/2));

    /* Temporary lower the precision */
    set_equal_precision(0.00001);

    ASSERT_EQ(n, Vector(0, 0.97014, -0.24254));

    set_equal_precision(FLT_EPSILON);
}

TEST(ShapeTest, A_shape_has_a_parent_attribute)
{
    TestShape s = TestShape();

    ASSERT_EQ(s.parent, nullptr);
}

TEST(TestShape, Converting_a_point_from_world_to_object_space)
{
    Group g1 = Group();
    g1.setTransform(rotationY(M_PI / 2));
    Group g2 = Group();
    g2.setTransform(scaling(2, 2, 2));
    g1.addObject(&g2);
    Sphere s = Sphere();
    s.setTransform(translation(5, 0, 0));
    g2.addObject(&s);

    Tuple p = s.worldToObject(Point(-2, 0, -10));

    ASSERT_EQ(p, Point(0, 0, -1));
}

TEST(TestShape, Converting_a_normal_form_object_to_world_space)
{
    Group g1 = Group();
    g1.setTransform(rotationY(M_PI / 2));
    Group g2 = Group();
    g2.setTransform(scaling(1, 2, 3));
    g1.addObject(&g2);
    Sphere s = Sphere();
    s.setTransform(translation(5, 0, 0));
    g2.addObject(&s);

    Tuple p = s.normalToWorld(Vector(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));

    /* Temporary lower the precision */
    set_equal_precision(0.0001);

    ASSERT_EQ(p, Vector(0.2857, 0.4286, -0.8571));

    set_equal_precision(FLT_EPSILON);
}


TEST(TestShape, Finding_the_normal_on_a_child_object)
{
    Group g1 = Group();
    g1.setTransform(rotationY(M_PI / 2));
    Group g2 = Group();
    g2.setTransform(scaling(1, 2, 3));
    g1.addObject(&g2);
    Sphere s = Sphere();
    s.setTransform(translation(5, 0, 0));
    g2.addObject(&s);

    Tuple p = s.normalAt(Point(1.7321, 1.1547, -5.5774));

    /* Temporary lower the precision */
    set_equal_precision(0.0001);

    ASSERT_EQ(p, Vector(0.2857, 0.4286, -0.8571));

    set_equal_precision(FLT_EPSILON);
}

TEST(TestShape, Test_the_bouding_box_of_the_test_shape)
{
    TestShape t = TestShape();
    BoundingBox b = BoundingBox(Point(-1, -1, -1), Point(1, 1, 1));

    BoundingBox res = t.getBounds();

    ASSERT_EQ(res.min, b.min);
    ASSERT_EQ(res.max, b.max);
}
