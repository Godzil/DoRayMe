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
    floor.material.pattern = new CheckersPattern(Colour(1, 1, 1), Colour(0, 0, 0));
    floor.setTransform(translation(0, -10, 0));
    w.addObject(&floor);


    Sphere glassBall = Sphere();
    glassBall.material.shininess = 300;
    glassBall.material.transparency = 1;
    glassBall.material.refractiveIndex = 1.52;
    glassBall.material.diffuse = 0.1;
    w.addObject(&glassBall);

    Sphere airBall = Sphere();
    airBall.setTransform(scaling(0.5, 0.5, 0.5));
    airBall.material.shininess = 300;
    airBall.material.transparency = 1;
    airBall.material.refractiveIndex = 1.0009;
    airBall.material.diffuse = 0.1;
    w.addObject(&airBall);

   /* Add light */
    Light light = Light(POINT_LIGHT, Point(20, 10, 0), Colour(0.7, 0.7, 0.7));
    w.addLight(&light);

    /* Set the camera */
    Camera camera = Camera(1000, 1000, M_PI / 3);

    camera.setTransform(viewTransform(Point(0, 2.5, 0),
                                      Point(0, 0, 0),
                                      Vector(1, 0, 0)));

    /* Now render it */
    Canvas image = camera.render(w);

    image.SaveAsPNG("ch11_refraction.png");

    return 0;
}