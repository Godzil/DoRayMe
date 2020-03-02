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
    /* First we need to construct the world */
    Plane floor = Plane();
    floor.material.specular = 0;
    floor.material.pattern = new RingPattern(Colour(1, 0.9, 0.9), Colour(1, 0.2, 0.2));
    floor.material.reflective = 0.1;

    Plane wall = Plane();
    wall.material.specular = 0;
    wall.material.pattern = new StripPattern(Colour(1, 0.9, 0.9), Colour(1, 0.2, 0.2));
    wall.material.pattern->setTransform(translation(0, 0, 1) * rotationY(M_PI/4));
    wall.setTransform(translation(0, 0, 5) * rotationX(M_PI/2));

    Sphere middle = Sphere();
    middle.setTransform(translation(-0.7, 1, 0.6));
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
    right.material.reflective = 0.1;

    Sphere left = Sphere();
    left.setTransform(translation(-1.5, 0.33, -0.75) * scaling(0.33, 0.33, 0.33));
    left.material.diffuse = 0.7;
    left.material.specular = 0.3;
    left.material.pattern = new GradientPattern(Colour(1, 0.8, 0.1), Colour(0.1, 0.1, 1));
    left.material.pattern->setTransform(translation(1.5, 0, 0) * scaling(2.1, 2, 2) * rotationY(-M_PI/4));

    Sphere fourth = Sphere();
    fourth.setTransform(translation(.5, 0.25, 0.4) * scaling(0.3, 0.3, 0.3));
    fourth.material.diffuse = 0.7;
    fourth.material.specular = 0.3;
    fourth.material.pattern = new CheckersPattern(Colour(0.1, 0.8, 0.1), Colour(0.8, 1, 0.8));
    fourth.material.pattern->setTransform( scaling(0.2, 0.2, 0.2));
    fourth.material.reflective = 0.4;

    World w = World();

    w.addObject(&floor);
    w.addObject(&wall);
    w.addObject(&middle);
    w.addObject(&left);
    w.addObject(&right);
    w.addObject(&fourth);

    /* Add some more reflective spheres */
    Sphere ref1 = Sphere();
    ref1.setTransform(translation(1, 1, .4) * scaling(0.2, 0.2, 0.2));
    ref1.material.reflective = 1;
    ref1.material.colour = Colour(0.3, 0.7, 0.6);
    w.addObject(&ref1);

    Sphere ref2 = Sphere();
    ref2.setTransform(translation(1.5, 2, -.8) * scaling(0.2, 0.2, 0.2));
    ref2.material.reflective = 1;
    ref2.material.specular = 0.5;
    ref2.material.colour = Colour(0.3, 0.3, 0.3);
    w.addObject(&ref2);

    Sphere ref3 = Sphere();
    ref3.setTransform(translation(-2, 1.678, .4) * scaling(0.4, 0.4, 0.4));
    ref3.material.reflective = 1;
    ref3.material.specular = 0.5;
    w.addObject(&ref3);

    /* Add light */
    //Light light = Light(POINT_LIGHT, Point(-10, 10, -10), Colour(1, 1, 1));
    Light light = Light(AREA_LIGHT, Point(-9, 10, -9),
            Vector(2, 0, 0), 5,
            Vector(0, 2, 0), 5,

            Colour(1, 1, 1));

    w.addLight(&light);

#define WIDTH (100)
#define HEIGHT (50)

    /* Set the camera */
    Camera camera = Camera(WIDTH, HEIGHT, M_PI / 3);
    camera.setTransform(viewTransform(Point(0, 1.5, -5),
                                      Point(0, 1, 0),
                                      Vector(0, 1, 0)));
    /* Now render it */
    printf("Render full scene...\n");
    Canvas image = camera.render(w);
    image.SaveAsPNG("ch11_reflection.png");

    /* Let's try to zoom on the small reflective ball in the back */
    Camera camera2 = Camera(HEIGHT, HEIGHT, M_PI / 40);
    camera2.setTransform(viewTransform(Point(0, 1.5, -5),
                                      Point(1, 1, .4),
                                      Vector(0, 1, 0)));
    printf("Render reflective ball...\n");
    Canvas image2 = camera2.render(w);
    image2.SaveAsPNG("ch11_zooming_on_reflective_ball.png");

    /* Zooming on a reflexion on a reflective ball */
    Camera camera3 = Camera(HEIGHT, HEIGHT, M_PI / 600);
    camera3.setTransform(viewTransform(Point(0, 1.5, -5),
                                      Point(1.05, 1.063, .4),
                                      Vector(0, 1, 0)));
    printf("Render reflection on ball...\n");
    Canvas image3 = camera3.render(w);
    image3.SaveAsPNG("ch11_reflection_on_ball.png");

    return 0;
}