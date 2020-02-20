/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Shape unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <shape.h>
#include <matrix.h>
#include <transformation.h>
#include <gtest/gtest.h>

TEST(ShapeTest, The_default_transformation)
{
    Shape s = Shape();
    ASSERT_EQ(s.transformMatrix, Matrix4().identity());
}

TEST(ShapeTest, Assigning_a_transformation)
{
    Shape s = Shape();

    s.setTransform(translation(2, 3, 4));

    ASSERT_EQ(s.transformMatrix, translation(2, 3, 4));
}

TEST(ShapeTest, The_default_material)
{
    Shape s = Shape();

    ASSERT_EQ(s.material, Material());
}

TEST(ShapeTest, Assigning_a_material)
{
    Shape s = Shape();
    Material m = Material();
    m.ambient = 1;

    s.material = m;

    ASSERT_EQ(s.material, m);
}