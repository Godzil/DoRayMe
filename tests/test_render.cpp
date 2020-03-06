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
    Light light = Light(POINT_LIGHT, Point(-5, 5, -5), Colour(1, 1, 1));
    w.addLight(&light);

    /* ----------------------------- */

    /* Environment */
    Plane p1 = Plane();
    p1.setTransform(translation(0, 0, 5) * rotationX(-M_PI/2));
    p1.material.pattern = new CheckersPattern(Colour(1, 1, 1), Colour(0.1, 0.1, 0.1));
    w.addObject(&p1);

    Plane p2 = Plane();
    p2.setTransform( translation(0, 0, -6) * rotationX(-M_PI/2) );
    p2.material.pattern = new CheckersPattern(Colour(1, 1, 1), Colour(0.1, 0.1, 0.1));
    w.addObject(&p2);

    Plane p3 = Plane();
    p3.setTransform(translation(-6, 0, 0) * rotationZ(M_PI/2) );
    p3.material.pattern = new CheckersPattern(Colour(1, 1, 1), Colour(0.1, 0.1, 0.1));
    w.addObject(&p3);

    Plane p4 = Plane();
    p3.setTransform(translation(6, 0, 0) * rotationZ(M_PI/2) );
    p3.material.pattern = new CheckersPattern(Colour(1, 1, 1), Colour(0.1, 0.1, 0.1));
    w.addObject(&p3);

    Plane p5 = Plane();
    p5.material.pattern = new CheckersPattern(Colour(1, 1, 1), Colour(0.1, 0.1, 0.1));
    w.addObject(&p5);

    /* ----------------------------- */

    /* Big Sphere */
    Sphere bigS = Sphere();
    bigS.setTransform(translation(-0.5, 1, 2) * scaling(2, 2, 2));
    bigS.material.colour = Colour(0, 0.4, 0.4);
    bigS.material.shininess = 50;
    bigS.material.specular = 1;
    bigS.material.reflective = 0.8;
    w.addObject(&bigS);

    /* Small Sphere */
    Sphere smaS = Sphere();
    smaS.setTransform(translation(2.2, 1, -1));
    smaS.material.colour = Colour(0.4, 0, 0.4);
    smaS.material.shininess = 50;
    smaS.material.specular = 1;
    smaS.material.reflective = 0.2;
    w.addObject(&smaS);

    /* Cylinder */
    Cylinder cyl = Cylinder();
    cyl.setTransform(translation(-3.5, 0, 1));
    cyl.isClosed = true;
    cyl.minCap = -1;
    cyl.maxCap = 3;
    cyl.material.colour = Colour(0.4, 1, 0.4);
    cyl.material.shininess = 20;
    cyl.material.specular = 1;
    cyl.material.reflective = 0.01;
    cyl.material.pattern = new GradientPattern(Colour(0.4, 1, 0.4), Colour(1.0, 0.2, 1.0));
    cyl.material.pattern->setTransform(scaling(1.1, 1.1, 1.1) * rotationY(M_PI / 2));
    w.addObject(&cyl);

    /* Cube */
    Cube cub = Cube();
    cub.setTransform(translation(0.6, 0.4, -1) * scaling(0.4, 0.4, 0.4) * rotationY(deg_to_rad(60)));
    cub.material.colour = Colour(1, 0, 0.4);
    cub.material.shininess = 50;
    cub.material.specular = 1;
    cub.material.reflective = 0.3;
    w.addObject(&cub);

    /* Glass cube */
    Cube gcub = Cube();
    gcub.setTransform(translation(-0.5, 0.6, -0.8) *  scaling(0.6, 0.6, 0.6) * rotationY(deg_to_rad(40)));
    gcub.dropShadow = false;
    gcub.material.colour = Colour(0, 0.4, 0.1);
    gcub.material.specular = 1;
    gcub.material.shininess = 400;
    gcub.material.ambient = 0.1;
    gcub.material.diffuse = 0.3;
    gcub.material.reflective = 1;
    gcub.material.transparency = 1;
    gcub.material.refractiveIndex = 0.3;
    w.addObject(&gcub);
    /* ----------------------------- */

    /* Set the camera */
    Camera camera = Camera(40, 10, deg_to_rad(90));
    camera.setTransform(viewTransform(Point(-2, 2.5, -3.5),
                                      Point(2, 0, 3),
                                      Vector(0, 1, 0)));

    /* Now render it */
    Canvas image = camera.render(w, 20);

    image.SaveAsPNG("test_renter.png");

    return 0;
}