/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Render test for OBJ File using teapots in chapter 15.
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <world.h>
#include <light.h>
#include <plane.h>
#include <material.h>
#include <colour.h>
#include <canvas.h>
#include <camera.h>
#include <objfile.h>

#include <pattern.h>
#include <strippattern.h>
#include <gradientpattern.h>
#include <checkerspattern.h>
#include <ringpattern.h>

#include <transformation.h>

int main()
{
    World w = World();

    /* Add lights */
    Light light1 = Light(POINT_LIGHT, Point(0, 20, 2), Colour(1, 1, 1));
    w.addLight(&light1);
    Light light2 = Light(POINT_LIGHT, Point(0, 2, 20), Colour(1, 1, 1));
    w.addLight(&light2);

    /* ----------------------------- */

    /* Floor */
    Plane p = Plane();
    CheckersPattern checkered = CheckersPattern(Colour(0.35, 0.35, 0.35), Colour(0.4, 0.4, 0.4));
    p.material.pattern = &checkered;
    p.material.ambient = 1;
    p.material.diffuse = 0;
    p.material.specular = 0;
    w.addObject(&p);

    Plane p2 = Plane();
    p2.setTransform(translation(0, 0, -10) * rotationX(M_PI/2));
    p2.material.pattern = &checkered;
    p2.material.ambient = 1;
    p2.material.diffuse = 0;
    p2.material.specular = 0;
    w.addObject(&p2);

    OBJFile teapot = OBJFile("teapot-low.obj");
    teapot.setTransform(rotationY(M_PI) * rotationX(-M_PI/2) * scaling(0.4, 0.4, 0.4));
    teapot.material.colour = Colour(1, 0.2, 0.1);
    teapot.material.ambient = 0.2;
    teapot.material.specular = 0.2;
    teapot.material.diffuse = 20;
    w.addObject(&teapot);

    /* ----------------------------- */

    FILE *fpOut = fopen("teapot_worlddump.json", "wt");
    if (fpOut)
    {
        w.dumpMe(fpOut);
        fclose(fpOut);
    }

    /* ----------------------------- */

    /* Set the camera */
    Camera camera = Camera(800, 400, M_PI/2);
    camera.setTransform(viewTransform(Point(0, 7, 13),
                                      Point(0, 1, 0),
                                      Vector(0, 1, 0)));

    /* Now render it */
    Canvas image = camera.render(w, 5);

    image.SaveAsPNG("ch15_teapot_objfile.png");

    return 0;
}