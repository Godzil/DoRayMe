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
#include <sphere.h>
#include <plane.h>
#include <cube.h>
#include <cylinder.h>
#include <material.h>
#include <colour.h>
#include <canvas.h>
#include <camera.h>

#include <pattern.h>
#include <strippattern.h>
#include <gradientpattern.h>
#include <checkerspattern.h>
#include <ringpattern.h>

#include <transformation.h>

int main()
{
    World w = World();

    /* Add light */
    Light light = Light(POINT_LIGHT, Point(1, 6.9, -4.9), Colour(1, 1, 1));
    w.addLight(&light);

    /* ----------------------------- */

    /* The floor / ceiling */
    Plane floor = Plane();
    floor.material.pattern = new CheckersPattern(Colour(0.5, 0.5, 0.5), Colour(0.75, 0.75, 0.75));
    floor.material.pattern->setTransform(rotationY(0.3) * scaling(0.25, 0.25, 0.25));
    w.addObject(&floor);

    /* ----------------------------- */

    Cylinder cyl1 = Cylinder();
    cyl1.minCap = 0;
    cyl1.maxCap = 0.75;
    cyl1.isClosed = true;
    cyl1.setTransform(translation(-1, 0, 1) * scaling(0.5, 1, 0.5));
    cyl1.material.colour = Colour(0, 0, 0.6);
    cyl1.material.diffuse = 0.1;
    cyl1.material.specular = 0.9;
    cyl1.material.shininess = 300;
    cyl1.material.reflective = 0.9;
    w.addObject(&cyl1);

    /* ----------------------------- */

    /* Concentrics */
    Cylinder cons1 = Cylinder();
    cons1.minCap = 0;
    cons1.maxCap = 0.2;
    cons1.isClosed = false;
    cons1.setTransform(translation(1, 0, 0) * scaling(0.8, 1, 0.8));
    cons1.material.colour = Colour(1, 1, 0.3);
    cons1.material.ambient = 0.1;
    cons1.material.diffuse = 0.8;
    cons1.material.specular = 0.9;
    cons1.material.shininess = 300;
    w.addObject(&cons1);

    Cylinder cons2 = Cylinder();
    cons2.minCap = 0;
    cons2.maxCap = 0.3;
    cons2.isClosed = false;
    cons2.setTransform(translation(1, 0, 0) * scaling(0.6, 1, 0.6));
    cons2.material.colour = Colour(1, 0.9, 0.4);
    cons2.material.ambient = 0.1;
    cons2.material.diffuse = 0.8;
    cons2.material.specular = 0.9;
    cons2.material.shininess = 300;
    w.addObject(&cons2);

    Cylinder cons3 = Cylinder();
    cons3.minCap = 0;
    cons3.maxCap = 0.4;
    cons3.isClosed = false;
    cons3.setTransform(translation(1, 0, 0) * scaling(0.4, 1, 0.4));
    cons3.material.colour = Colour(1, 0.8, 0.5);
    cons3.material.ambient = 0.1;
    cons3.material.diffuse = 0.8;
    cons3.material.specular = 0.9;
    cons3.material.shininess = 300;
    w.addObject(&cons3);

    Cylinder cons4 = Cylinder();
    cons4.minCap = 0;
    cons4.maxCap = 0.5;
    cons4.isClosed = true;
    cons4.setTransform(translation(1, 0, 0) * scaling(0.2, 1, 0.2));
    cons4.material.colour = Colour(1, 0.7, 0.6);
    cons4.material.ambient = 0.1;
    cons4.material.diffuse = 0.8;
    cons4.material.specular = 0.9;
    cons4.material.shininess = 300;
    w.addObject(&cons4);

    /* ----------------------------- */

    /* decoratives cylinders */
    Cylinder deco1 = Cylinder();
    deco1.minCap = 0;
    deco1.maxCap = 0.3;
    deco1.isClosed = true;
    deco1.setTransform(translation(0, 0, -0.75) * scaling(0.05, 1, 0.05));
    deco1.material.colour = Colour(1, 0, 0);
    deco1.material.ambient = 0.1;
    deco1.material.diffuse = 0.9;
    deco1.material.specular = 0.9;
    deco1.material.shininess = 300;
    w.addObject(&deco1);

    Cylinder deco2 = Cylinder();
    deco2.minCap = 0;
    deco2.maxCap = 0.3;
    deco2.isClosed = true;
    deco2.setTransform(translation(0, 0, -2.25) * rotationY(-0.15) * translation(0, 0, 1.5) * scaling(0.05, 1, 0.05));
    deco2.material.colour = Colour(1, 1, 0);
    deco2.material.ambient = 0.1;
    deco2.material.diffuse = 0.9;
    deco2.material.specular = 0.9;
    deco2.material.shininess = 300;
    w.addObject(&deco2);

    Cylinder deco3 = Cylinder();
    deco3.minCap = 0;
    deco3.maxCap = 0.3;
    deco3.isClosed = true;
    deco3.setTransform(translation(0, 0, -2.25) * rotationY(-0.3) * translation(0, 0, 1.5) * scaling(0.05, 1, 0.05));
    deco3.material.colour = Colour(0, 1, 0);
    deco3.material.ambient = 0.1;
    deco3.material.diffuse = 0.9;
    deco3.material.specular = 0.9;
    deco3.material.shininess = 300;
    w.addObject(&deco3);

    Cylinder deco4 = Cylinder();
    deco4.minCap = 0;
    deco4.maxCap = 0.3;
    deco4.isClosed = true;
    deco4.setTransform(translation(0, 0, -2.25) * rotationY(-0.45) * translation(0, 0, 1.5) * scaling(0.05, 1, 0.05));
    deco4.material.colour = Colour(0, 1, 1);
    deco4.material.ambient = 0.1;
    deco4.material.diffuse = 0.9;
    deco4.material.specular = 0.9;
    deco4.material.shininess = 300;
    w.addObject(&deco4);

    /* ----------------------------- */

    /* glass cylinder */
    Cylinder glassCylinder = Cylinder();
    glassCylinder.minCap = 0.0001;
    glassCylinder.maxCap = 0.5;
    glassCylinder.isClosed = true;
    glassCylinder.setTransform(translation(0, 0, -1.5) * scaling(0.33, 1, 0.33));
    glassCylinder.material.colour = Colour(0.25, 0, 0);
    glassCylinder.material.diffuse = 0.1;
    glassCylinder.material.specular = 0.9;
    glassCylinder.material.shininess = 300;
    glassCylinder.material.reflective = 0.9;
    glassCylinder.material.transparency = 0.9;
    glassCylinder.material.refractiveIndex = 1.5;
    w.addObject(&glassCylinder);

    /* ----------------------------- */

    /* Set the camera */
    Camera camera = Camera(400, 200, 0.314);
    camera.setTransform(viewTransform(Point(8, 3.5, -9),
                                      Point(0, 0.3, 0),
                                      Vector(0, 1, 0)));

    /* Now render it */
    Canvas image = camera.render(w, 20);

    image.SaveAsPNG("ch13_test.png");

    return 0;
}