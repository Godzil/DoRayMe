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

    s.material.colour = Colour(1, 0.2, 1);


    Light light = Light(POINT_LIGHT, Point(-10, 10, -10), Colour(1, 1, 1));

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
            Intersect xs = s.intersect(r);

            Intersection hit = xs.hit();

            if (!hit.nothing())
            {
                Tuple hitPoint = r.position(hit.t);
                Tuple hitNormalVector = hit.object->normalAt(hitPoint);
                Tuple eye = -r.direction;
                Colour pixelColour = hit.object->material.lighting(light, hitPoint, eye, hitNormalVector);

                c.putPixel(x, y, pixelColour);
            }

        }
    }
    c.SaveAsPNG("ch6_test.png");
    return 0;
}