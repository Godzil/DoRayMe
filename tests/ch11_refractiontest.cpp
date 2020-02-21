/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Render test for reflection in chapter 11.
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <world.h>
#include <light.h>
#include <sphere.h>
#include <plane.h>
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

    /* First we need to construct the world */
    Plane floor = Plane();
    floor.material.specular = 0;
    floor.material.pattern = new CheckersPattern(Colour(1, 1, 1), Colour(0, 0, 0));
    floor.material.pattern->setTransform(scaling(0.7, 0.7, 0.7));
    floor.setTransform(translation(0, -3, 0));
    w.addObject(&floor);

    /* Add some more reflective spheres */
    Sphere glassBall = Sphere();
    glassBall.setTransform(scaling(1.5, 1.5, 1.5));
    glassBall.material.refractiveIndex = 1.5;
    glassBall.material.transparency = 1.0;
    w.addObject(&glassBall);

    Sphere airBubble = Sphere();
    airBubble.setTransform( scaling(0.9, 0.9, 0.9));
    airBubble.material.specular = 0;
    airBubble.material.ambient = 0;
    airBubble.material.refractiveIndex = 1.00029;
    airBubble.material.transparency = 1.0;
    w.addObject(&airBubble);

    /* Add light */
    Light light = Light(POINT_LIGHT, Point(-10, 20, -10), Colour(1, 1, 1));

    w.addLight(&light);

    /* Set the camera */
    Camera camera = Camera(1000, 1000, M_PI / 3);
#if 0
    camera.setTransform(viewTransform(Point(0, 1.5, -5),
                                      Point(0, 1, 0),
                                      Vector(0, 1, 0)));
#else
    camera.setTransform(viewTransform(Point(0, 3.6, 0),
                                      Point(0, 0, 0),
                                      Vector(0, 0, 1)));
#endif
    /* Now render it */
    Canvas image = camera.render(w);

    image.SaveAsPNG("ch11_refractiontest.png");


    return 0;
}