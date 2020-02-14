/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Canvas unit tests
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <colour.h>
#include <canvas.h>
#include <math.h>
#include <gtest/gtest.h>

TEST(CanvasTest, Creating_a_canvas)
{
    Canvas c = Canvas(10, 20);
    int x, y;
    ASSERT_EQ(c.width, 10);
    ASSERT_EQ(c.height, 20);
    for(y = 0; y < 20; y++)
    {
        for(x = 0; x < 10; x++)
        {
            ASSERT_EQ(c.get_pixel(x, y), Colour(0, 0, 0));
        }
    }
}

TEST(CanvasTest, Test_Writing_pixels_to_a_canvas_Test)
{
    Canvas c = Canvas(10, 20);
    Colour red = Colour(1, 0, 0);

    c.put_pixel(2, 3, red);

    ASSERT_EQ(c.get_pixel(2, 3), red);

}

TEST(CanvasTest, Save_a_PNG_file)
{
    Canvas c = Canvas(5, 3);
    Colour c1 = Colour(1.5, 0, 0);
    Colour c2 = Colour(0, 0.5, 0);
    Colour c3 = Colour(-0.5, 0, 1);

    c.put_pixel(0, 0, c1);
    c.put_pixel(2, 1, c2);
    c.put_pixel(4, 2, c3);

    ASSERT_TRUE(c.SaveAsPNG("Save_a_PNG_file.png"));

}