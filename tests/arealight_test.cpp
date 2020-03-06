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
#include <group.h>
#include <cone.h>

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
    Light light1 = Light(AREA_LIGHT, Point(-1, 2, 4),
            Vector(2, 0, 0), 8,
            Vector(0, 2, 0), 8,
            Colour(1.5, 1.5, 1.5),
            true);
    w.addLight(&light1);


    /* ----------------------------- */

    /* Cube that pretend to be the light */
    Cube c = Cube();
    c.material.colour = Colour(1.5, 1.5, 1.5);
    c.material.ambient = 1;
    c.material.diffuse = 0;
    c.material.specular = 0;
    c.dropShadow = false;
    c.setTransform(translation(0, 3, 4) * scaling(1, 1, 0.01));
    w.addObject(&c);

    Plane p = Plane();
    p.material.colour = Colour(1, 1, 1);
    p.material.ambient = 0.025;
    p.material.diffuse = 0.67;
    p.material.specular = 0;
    w.addObject(&p);

    Sphere s1 = Sphere();
    s1.setTransform(translation(0.5, 0.5,0) * scaling(0.5, 0.5, 0.5));
    s1.material.colour = Colour(1, 0, 0);
    s1.material.ambient = 0.1;
    s1.material.specular = 0;
    s1.material.diffuse = 0.6;
    s1.material.reflective = 0.3;
    w.addObject(&s1);

    Sphere s2 = Sphere();
    s2.setTransform(translation(-0.25, 0.33,0) * scaling(0.33, 0.33, 0.33));
    s2.material.colour = Colour(0.5, 0.5, 1);
    s2.material.ambient = 0.1;
    s2.material.specular = 0;
    s2.material.diffuse = 0.6;
    s2.material.reflective = 0.3;
    w.addObject(&s2);

    /* ----------------------------- */

    /* Set the camera */
    Camera camera = Camera(40, 16, 0.7854);
    camera.setTransform(viewTransform(Point(-3, 1, 2.5),
                                      Point(0, 0.5, 0),
                                      Vector(0, 1, 0)));

    /* Now render it */
    Canvas image = camera.render(w, 5);

    image.SaveAsPNG("arealight_test.png");

    return 0;
}