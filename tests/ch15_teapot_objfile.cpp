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
    Light light1 = Light(POINT_LIGHT, Point(50, 100, 20), Colour(.5, .5, .5));
    w.addLight(&light1);
    Light light2 = Light(POINT_LIGHT, Point(2, 50, 100), Colour(.5, .5, .5));
    w.addLight(&light2);

    /* ----------------------------- */

    /* Floor */
    Plane p = Plane();
    CheckersPattern checkered = CheckersPattern(Colour(0.35, 0.35, 0.35), Colour(0.4, 0.4, 0.4));
    p.material.pattern = &checkered;
    p.material.ambient = 1;
    p.material.diffuse = 0;
    p.material.specular = 0;
    p.material.reflective = 0.1;
    w.addObject(&p);

    Plane p2 = Plane();
    p2.setTransform(translation(0, 0, -10) * rotationX(M_PI/2));
    p2.material.pattern = &checkered;
    p2.material.ambient = 1;
    p2.material.diffuse = 0;
    p2.material.specular = 0;
    w.addObject(&p2);

    OBJFile teapot = OBJFile("teapot-low.obj");
    teapot.setTransform(translation(7, 0, 3) * rotationY(M_PI*23/22) * rotationX(-M_PI/2) * scaling(0.3, 0.3, 0.3));
    teapot.material.colour = Colour(1, 0.3, 0.2);
    teapot.material.shininess = 5;
    teapot.material.specular = 0.4;
    w.addObject(&teapot);

    OBJFile teapot2 = OBJFile("teapot-lowtri.obj");
    teapot2.setTransform(translation(-7, 0, 3) * rotationY(-M_PI*46/22) * rotationX(-M_PI/2) * scaling(0.3, 0.3, 0.3));
    teapot2.material.colour = Colour(1, 0.3, 0.2);
    teapot2.material.shininess = 5;
    teapot2.material.specular = 0.4;
    w.addObject(&teapot2);

    OBJFile teapot3= OBJFile("teapot.obj");
    teapot3.setTransform(translation(0, 0, -5) * rotationY(-M_PI) * rotationX(-M_PI/2) * scaling(0.4, 0.4, 0.4));
    teapot3.material.colour = Colour(0.3, 1, 0.2);
    teapot3.material.shininess = 5;
    teapot3.material.specular = 0.4;
    teapot3.material.reflective = 0.5;
    w.addObject(&teapot3);

    /* ----------------------------- */

    /* Set the camera */
    Camera camera = Camera(80, 40, M_PI/2);
    camera.setTransform(viewTransform(Point(0, 7, 13),
                                      Point(0, 1, 0),
                                      Vector(0, 1, 0)));

    /* Now render it */
    Canvas image = camera.render(w, 5);

    image.SaveAsPNG("ch15_teapot_objfile.png");

    return 0;
}