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

    Material wallMaterial = Material();
    wallMaterial.pattern = new StripPattern(Colour(0.45, 0.45, 0.45), Colour(0.55, 0.55, 0.55));
    wallMaterial.pattern->setTransform( scaling(0.25, 0.25, 0.25) * rotationY(1.5708));
    wallMaterial.ambient = 0;
    wallMaterial.diffuse = 0.4;
    wallMaterial.specular = 0;
    wallMaterial.reflective = 0.3;

    /* ----------------------------- */

    /* The flood */
    Plane floor = Plane();
    floor.setTransform(rotationY(0.31415));
    floor.material.pattern = new CheckersPattern(Colour(0.35, 0.35, 0.35), Colour(0.65, 0.65, 0.65));
    floor.material.specular = 0;
    floor.material.reflective = 0.4;
    w.addObject(&floor);

    /* the ceiling */
    Plane ceiling = Plane();
    ceiling.setTransform(translation(0, 5, 0));
    ceiling.material.colour = Colour(0.8, 0.8, 0.8);
    ceiling.material.ambient = 0.3;
    ceiling.material.specular = 0;
    w.addObject(&ceiling);

    /* West wall */
    Plane westWall = Plane();
    westWall.setTransform( translation(-5, 0, 0) * rotationZ(1.5708) * rotationY(1.5708));
    westWall.setMaterial(wallMaterial);
    w.addObject(&westWall);

    /* east wall */
    Plane eastWall = Plane();
    eastWall.setTransform( translation(5, 0, 0) * rotationZ(1.5708) * rotationY(1.5708));
    eastWall.setMaterial(wallMaterial);
    w.addObject(&eastWall);

    /* north wall */
    Plane northWall = Plane();
    northWall.setTransform( translation(0, 0, 5) * rotationX(1.5708));
    northWall.setMaterial(wallMaterial);
    w.addObject(&northWall);

    /* south wall */
    Plane southWall = Plane();
    southWall.setTransform( translation(0, 0, -5) * rotationX(1.5708));
    southWall.setMaterial(wallMaterial);
    w.addObject(&southWall);

    /* ----------------------------- */

    /* Background balls */
    Sphere bg1 = Sphere();
    bg1.setTransform(translation(4.6, 0.4, 1) * scaling(0.4, 0.4, 0.4));
    bg1.material.colour = Colour(0.8, 0.5, 0.3);
    bg1.material.shininess = 50;
    w.addObject(&bg1);

    Sphere bg2 = Sphere();
    bg2.setTransform(translation(4.7, 0.3, 0.4) * scaling(0.3, 0.3, 0.3));
    bg2.material.colour = Colour(0.9, 0.4, 0.5);
    bg2.material.shininess = 50;
    w.addObject(&bg2);

    Sphere bg3 = Sphere();
    bg3.setTransform(translation(-1, 0.5, 4.5) * scaling(0.5, 0.5, 0.5));
    bg3.material.colour = Colour(0.4, 0.9, 0.6);
    bg3.material.shininess = 50;
    w.addObject(&bg3);

    Sphere bg4 = Sphere();
    bg4.setTransform(translation(-1.7, 0.3, 4.7) * scaling(0.3, 0.3, 0.3));
    bg4.material.colour = Colour(0.4, 0.6, 0.9);
    bg4.material.shininess = 50;
    w.addObject(&bg4);

    /* Forground balls */

    /* Red sphere */
    Sphere redBall = Sphere();
    redBall.setTransform(translation(-0.6, 1, 0.6));
    redBall.material.colour = Colour(1, 0.3, 0.2);
    redBall.material.shininess = 5;
    redBall.material.specular = 0.4;
    w.addObject(&redBall);

    /* blue glass ball */
    Sphere blueGlassBall = Sphere();
    blueGlassBall.setTransform(translation(0.6, 0.7, -0.6) * scaling(0.7, 0.7, 0.7));
    blueGlassBall.material.colour = Colour(0, 0, 0.2);
    blueGlassBall.material.ambient = 0;
    blueGlassBall.material.diffuse = 0.4;
    blueGlassBall.material.specular = 0.9;
    blueGlassBall.material.shininess = 300;
    blueGlassBall.material.transparency = 0.9;
    blueGlassBall.material.refractiveIndex = 1.5;
    w.addObject(&blueGlassBall);

    /* green glass ball */
    Sphere greenGlassBall = Sphere();
    greenGlassBall.setTransform(translation(-0.7, 0.5, -0.8) * scaling(0.5, 0.5, 0.5));
    greenGlassBall.material.colour = Colour(0, 0.2, 0);
    greenGlassBall.material.ambient = 0;
    greenGlassBall.material.diffuse = 0.4;
    greenGlassBall.material.specular = 0.9;
    greenGlassBall.material.shininess = 300;
    greenGlassBall.material.transparency = 0.9;
    greenGlassBall.material.refractiveIndex = 1.5;
    w.addObject(&greenGlassBall);

    /* ----------------------------- */

    /* Add light */
    Light light = Light(POINT_LIGHT, Point(-4.9, 4.9, -1), Colour(1, 1, 1));
    w.addLight(&light);

    /* Set the camera */
    Camera camera = Camera(800, 400, 1.152);
    camera.setTransform(viewTransform(Point(-2.6, 1.5, -3.9),
                                      Point(-0.6, 1, -0.8),
                                      Vector(0, 1, 0)));

    /* Now render it */
    Canvas image = camera.render(w);

    image.SaveAsPNG("ch11_test.png");


    return 0;
}