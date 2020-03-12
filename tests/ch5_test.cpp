/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Render test for chapter 5 "Put it together".
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <ray.h>
#include <sphere.h>
#include <colour.h>
#include <canvas.h>
#include <transformation.h>

int main()
{
    int x, y;
    Canvas c = Canvas(100, 100);

    Sphere s = Sphere();
    Colour red = Colour(1, 0, 0);

    Point cameraOrigin = Point(0, 0, -5);
    double wallDistance = 10;
    double wallSize = 7;
    double pixelSize = wallSize / c.width;
    for(y = 0; y < c.height; y++)
    {
        double worldY = (wallSize / 2) - pixelSize * y;
        for(x = 0; x < c.width; x++)
        {
            double worldX = -(wallSize / 2) + pixelSize * x;
            Point position = Point(worldX, worldY, wallDistance);
            Ray r = Ray(cameraOrigin, (position - cameraOrigin).normalise());
            Intersect xs;
            s.intersect(r, xs);

            if (!xs.hit().nothing())
            {
                c.putPixel(x, y, red);
            }
        }
    }

    c.SaveAsPNG("ch5_test.png");
    return 0;
}