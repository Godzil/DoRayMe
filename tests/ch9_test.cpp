/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Render test for chapter 5 "Put it together".
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
#include <transformation.h>

int main()
{
    /* First we need to construct the world */
    Plane floor = Plane();
    floor.material.colour = Colour(1, 0.9, 0.9);
    floor.material.specular = 0;

    Sphere middle = Sphere();
    middle.setTransform(translation(-0.5, 1, 0.5));
    middle.material.colour = Colour(0.1, 1, 0.5);
    middle.material.diffuse = 0.7;
    middle.material.specular = 0.3;

    Sphere right = Sphere();
    right.setTransform(translation(1.5, 0.5, -0.5) * scaling(0.5, 0.5, 0.5));
    right.material.colour = Colour(0.5, 1, 0.1);
    right.material.diffuse = 0.7;
    right.material.specular = 0.3;

    Sphere left = Sphere();
    left.setTransform(translation(-1.5, 0.33, -0.75) * scaling(0.33, 0.33, 0.33));
    left.material.colour = Colour(1, 0.8, 0.1);
    left.material.diffuse = 0.7;
    left.material.specular = 0.3;

    World w = World();

    w.addObject(&floor);
    w.addObject(&middle);
    w.addObject(&left);
    w.addObject(&right);

    /* Add light */
    Light light = Light(POINT_LIGHT, Point(-10, 10, -10), Colour(1, 1, 1));

    w.addLight(&light);

    /* Set the camera */
    Camera camera = Camera(100, 50, M_PI / 3);
    camera.setTransform(viewTransform(Point(0, 1.5, -5),
                                      Point(0, 1, 0),
                                      Vector(0, 1, 0)));

    /* Now render it */
    Canvas image = camera.render(w);

    image.SaveAsPNG("ch9_test.png");


    return 0;
}