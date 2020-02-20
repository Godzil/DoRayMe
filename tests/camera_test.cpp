/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Camera unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <camera.h>
#include <math.h>
#include <math_helper.h>
#include <matrix.h>
#include <tuple.h>
#include <ray.h>
#include <world.h>
#include <canvas.h>
#include <colour.h>
#include <worldbuilder.h>
#include <transformation.h>
#include <stdint.h>
#include <gtest/gtest.h>

TEST(CameraTest, Constructing_a_camera)
{
    uint32_t hsize = 160;
    uint32_t vsize = 120;
    double field_of_view = M_PI / 2;

    Camera c = Camera(hsize, vsize, field_of_view);

    ASSERT_EQ(c.horizontalSize, 160);
    ASSERT_EQ(c.verticalSize, 120);
    ASSERT_TRUE(double_equal(c.fieldOfView, M_PI / 2));
    ASSERT_EQ(c.transformMatrix, Matrix4().identity());
}

TEST(CameraTest, Pixel_size_for_a_horizontal_canvas)
{
    Camera c = Camera(200, 125, M_PI / 2);

    ASSERT_TRUE(double_equal(c.pixelSize, 0.01));
}

TEST(CameraTest, Pixel_size_for_a_vertical_canvas)
{
    Camera c = Camera(125, 200, M_PI / 2);

    ASSERT_TRUE(double_equal(c.pixelSize, 0.01));
}

TEST(CameraTest, Constructing_a_ray_through_the_center_of_the_canvas)
{
    Camera c = Camera(201, 101, M_PI / 2);
    Ray r = c.rayForPixel(100, 50);

    ASSERT_EQ(r.origin, Point(0, 0, 0));
    ASSERT_EQ(r.direction, Vector(0, 0, -1));
}

TEST(CameraTest, Constructing_a_ray_through_a_corner_of_the_canvas)
{
    Camera c = Camera(201, 101, M_PI / 2);
    Ray r = c.rayForPixel(0, 0);

    ASSERT_EQ(r.origin, Point(0, 0, 0));

    /* Temporary lower the precision */
    set_equal_precision(0.00001);

    ASSERT_EQ(r.direction, Vector(0.66519, 0.33259, -0.66851));

    set_equal_precision(FLT_EPSILON);
}

TEST(CameraTest, Constructing_a_ray_when_the_camera_is_transformed)
{
    Camera c = Camera(201, 101, M_PI / 2);
    c.setTransform(rotationY(M_PI / 4) * translation(0, -2, 5));
    Ray r = c.rayForPixel(100, 50);

    ASSERT_EQ(r.origin, Point(0, 2, -5));
    ASSERT_EQ(r.direction, Vector(sqrt(2)/2, 0, -sqrt(2)/2));
}

TEST(CameraTest, Rendering_a_world_with_a_camera)
{
    World w = DefaultWorld();
    Camera c = Camera(11, 11, M_PI / 2);

    Tuple from = Point(0, 0, -5);
    Tuple to = Point(0, 0, 0);
    Tuple up = Vector(0, 1, 0);

    c.setTransform(viewTransform(from, to, up));

    Canvas image = c.render(w);

    /* Temporary lower the precision */
    /* We need to lower a lot as Canvas is not keeping the
     * floating point value, but a value between 0 and 255 per channel,
     * as it is storing the actual frame buffer, so there is a more big different
     * between the value.
     */
    set_equal_precision(0.005);

    Colour col = image.getPixel(5, 5);

    ASSERT_EQ(col, Colour(0.38066, 0.47583, 0.2855));

    set_equal_precision(FLT_EPSILON);
}