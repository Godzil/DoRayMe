/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Render test for reflection in chapter 13.
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <world.h>
#include <light.h>
#include <plane.h>
#include <colour.h>
#include <canvas.h>
#include <camera.h>
#include <triangle.h>
#include <group.h>
#include <time.h>

#include <transformation.h>

double frand(double max)
{
    return max * (rand() / ((double) RAND_MAX));
}

int main()
{
    World w = World();

    /* Add lights */
    Light light1 = Light(POINT_LIGHT, Point(10000, 10000, -10000), Colour(0.25, 0.25, 0.25));
    w.addLight(&light1);
    Light light2 = Light(POINT_LIGHT, Point(-10000, 10000, -10000), Colour(0.25, 0.25, 0.25));
    w.addLight(&light2);
    Light light3 = Light(POINT_LIGHT, Point(10000, -10000, -10000), Colour(0.25, 0.25, 0.25));
    w.addLight(&light3);
    Light light4 = Light(POINT_LIGHT, Point(-10000, -10000, -10000), Colour(0.25, 0.25, 0.25));
    w.addLight(&light4);

    /* ----------------------------- */

    /* White background */
    Plane p = Plane();
    p.setTransform(translation(0, 0, 100) *  rotationX(1.5708));
    p.material.colour = Colour(1, 1, 1);
    p.material.ambient = 1;
    p.material.diffuse = 0;
    p.material.specular = 0;
    w.addObject(&p);

    /* ----------------------------- */

    Group g = Group();

    srand(10); /* Force the seed to a known value */

    int i;
    Point p1, p2, p3;
    /* Let's add a bunche of "random" triangles */
    for (i = 0; i < 10; i++)
    {
        p1.x = 7-frand(14);
        p1.y = 7-frand(14);
        p1.z = 7-frand(14);
        p2.x = 7-frand(14);
        p2.y = 7-frand(14);
        p2.z = 7-frand(14);
        p3.x = 7-frand(14);
        p3.y = 7-frand(14);
        p3.z = 7-frand(14);

        Triangle *tri = new Triangle(p1, p2, p3);
        tri->material.colour.x = frand(1); // red
        tri->material.colour.y = frand(1); // green
        tri->material.colour.z = frand(1); // blue

        //tri->material.refractiveIndex = frand(2);
        //tri->material.transparency = frand(1);
        //tri->material.shininess = frand(300);
        //tri->material.specular = frand(1);
        //tri->material.ambient = frand(1);
        tri->material.reflective = frand(1);
        //tri->material.diffuse = frand(1);


        g.addObject(tri);
    }

    g.setTransform(rotationX(3.14));

    w.addObject(&g);

    /* ----------------------------- */

    FILE *fpOut = fopen("triangles_world.json", "wt");
    if (fpOut)
    {
        w.dumpMe(fpOut);
        fclose(fpOut);
    }

    /* ----------------------------- */

    /* Set the camera */
    Camera camera = Camera(500, 500, M_PI/1.5);
    camera.setTransform(viewTransform(Point(0, 0, -9),
                                      Point(0, 0, 0),
                                      Vector(0, 1, 0)));

    /* Now render it */
    Canvas image = camera.render(w, 5);

    image.SaveAsPNG("triangle_rendertest.png");

    return 0;
}