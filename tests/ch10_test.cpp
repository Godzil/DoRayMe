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

#include <pattern.h>
#include <strippattern.h>
#include <gradientpattern.h>

#include <transformation.h>

int main()
{
    /* First we need to construct the world */
    Plane floor = Plane();
    floor.material.specular = 0;
    floor.material.pattern = new StripPattern(Colour(1, 0.9, 0.9), Colour(1, 0.2, 0.2));

    Plane wall = Plane();
    wall.material.specular = 0;
    wall.material.pattern = new StripPattern(Colour(1, 0.9, 0.9), Colour(1, 0.2, 0.2));
    wall.material.pattern->setTransform(translation(0, 0, 1) * rotationY(M_PI/4));
    wall.setTransform(translation(0, 0, 5) * rotationX(M_PI/2));

    Sphere middle = Sphere();
    middle.setTransform(translation(-0.5, 1, 0.5));
    middle.material.diffuse = 0.7;
    middle.material.specular = 0.3;
    middle.material.pattern = new StripPattern(Colour(0.1, 1, 0.5), Colour(0, 0.2, 0.2));
    middle.material.pattern->setTransform((rotationZ(M_PI/4) * rotationY(M_PI/5) * scaling(0.2, 0.2, 0.2)));

    Sphere right = Sphere();
    right.setTransform(translation(1.5, 0.5, -0.5) * scaling(0.5, 0.5, 0.5));
    right.material.diffuse = 0.7;
    right.material.specular = 0.3;
    right.material.pattern = new StripPattern(Colour(0.5, 1, 0.1), Colour(0, 0, 0));
    right.material.pattern->setTransform((scaling(0.1, 0.1, 0.1)));

    Sphere left = Sphere();
    left.setTransform(translation(-1.5, 0.33, -0.75) * scaling(0.33, 0.33, 0.33));
    left.material.diffuse = 0.7;
    left.material.specular = 0.3;
    left.material.pattern = new GradientPattern(Colour(1, 0.8, 0.1), Colour(0.1, 0.1, 1));
    left.material.pattern->setTransform(translation(1.5, 0, 0) * scaling(2.1, 2, 2) * rotationY(-M_PI/4));

    World w = World();

    w.addObject(&floor);
    w.addObject(&wall);
    w.addObject(&middle);
    w.addObject(&left);
    w.addObject(&right);

    /* Add light */
    Light light = Light(POINT_LIGHT, Point(-10, 10, -10), Colour(1, 1, 1));

    w.addLight(&light);

    /* Set the camera */
    Camera camera = Camera(1920, 1080, M_PI / 3);
    camera.setTransform(viewTransform(Point(0, 1.5, -5),
                                      Point(0, 1, 0),
                                      Vector(0, 1, 0)));

    /* Now render it */
    Canvas image = camera.render(w);

    image.SaveAsPNG("ch10_test.png");


    return 0;
}