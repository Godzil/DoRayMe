/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Render test for CSG in chapter 16.
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
#include <group.h>
#include <cone.h>
#include <csg.h>

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
    Light light1 = Light(POINT_LIGHT, Point(100, 100, -100), Colour(1, 1, 1));
    w.addLight(&light1);

    /* ----------------------------- */

    /* White background */
    Plane p = Plane();
    p.setTransform(translation(0, 0, 100) *  rotationX(1.5708));
    p.material.colour = Colour(1, 1, 1);
    p.material.ambient = 1;
    p.material.diffuse = 0;
    p.material.specular = 0;
    w.addObject(&p);


    Cylinder c1 = Cylinder();
    c1.minCap = -2;
    c1.maxCap = 2;
    c1.isClosed = true;
    c1.material.colour = Colour(1, 0, 0);
    c1.setTransform(scaling(0.4, 1, 0.4));
    c1.materialSet = true;

    Cylinder c2 = Cylinder();
    c2.minCap = -2;
    c2.maxCap = 2;
    c2.isClosed = true;
    c2.material.colour = Colour(0, 1, 0);
    c2.setTransform(rotationX(M_PI/2) * scaling(0.4, 1, 0.4));
    c2.materialSet = true;

    CSG leaf1 = CSG(CSG::UNION, &c1, &c2);

    Cylinder c3 = Cylinder();
    c3.minCap = -2;
    c3.maxCap = 2;
    c3.isClosed = true;
    c3.material.colour = Colour(0, 0, 1);
    c3.setTransform(rotationZ(M_PI/2) * scaling(0.4, 1, 0.4));
    c3.materialSet = true;

    CSG leaf2 = CSG(CSG::UNION, &leaf1, &c3);

    Cube cb = Cube();
    //cb.materialSet = true;
    //cb.material.reflective = 1;

    Sphere sp = Sphere();
    sp.setTransform(scaling(1.35, 1.35, 1.35));
    CSG leaf3 = CSG(CSG::INTERSECTION, &sp, &cb);

    CSG leaf4 = CSG(CSG::DIFFERENCE, &leaf3, &leaf2);

    w.addObject(&leaf4);

    /* ----------------------------- */

    /* Set the camera */
    Camera camera = Camera(800, 400, M_PI / 2);
    camera.setTransform(viewTransform(Point(-4, 4, -9),
                                      Point(0, 1, 0),
                                      Vector(0, 1, 0)));

    /* Now render it */
    Canvas image = camera.render(w, 5);

    image.SaveAsPNG("ch16_test.png");

    return 0;
}