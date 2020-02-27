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
#include <triangle.h>
#include <stdio.h>

double frand(void)
{
    return rand() / ((double) RAND_MAX);
}

Shape *fir_branch()
{
    Group *ret = new Group();
    double length = 2;
    double radius = 0.025;
    int segments = 20;
    int perSegment = 24;

    Cylinder *branch = new Cylinder();
    branch->minCap = 0;
    branch->maxCap = length;
    branch->isClosed = true;
    branch->setTransform(scaling(radius, 1, radius));
    branch->material.colour = Colour(0.5, 0.35, 0.26);
    branch->material.ambient = 0.2;
    branch->material.specular = 0;
    branch->material.diffuse = 0.6;
    ret->addObject(branch);

    double seq_size = length / (segments - 1);
    double theta = 2.1 * M_PI / perSegment;
    double maxLenght = 20 * radius;

    int y, i;
    Triangle *needle;
    for(y = 0; y < segments; y++)
    {
        Group *subGroup = new Group();

        for(i = 0; i < perSegment; i++)
        {
            /* Each needle is a triangle */
            /* yBase is the y coordinate of the base of the triangle */
            double yBase = seq_size * y + frand() * seq_size;
            /* yTipe is the y coordinate of the tip of the triangle */
            double yTip = yBase - frand() * seq_size;
            /* yAndle is the angle (in radians) that the need shold be rotated
             * around the branch */
            double yAngle = i * theta + frand() * theta;
            /* How long is the needle? */
            double needleLenght = maxLenght / 2 * (1 + frand());
            /* How much is the needle offset fomr the center of the branch? */
            double ofs = radius / 2;
            Point p1 = Point(ofs, yBase, ofs);
            Point p2 = Point(-ofs, yBase, ofs);
            Point p3 = Point(0, yTip, needleLenght);
            needle = new Triangle(p1, p2, p3);
            needle->setTransform(rotationY(yAngle));
            needle->material.colour = Colour(0.26, 0.36, 0.16);
            needle->material.specular = 0.1;
            subGroup->addObject(needle);
        }
        ret->addObject(subGroup);
    }


    return ret;
}

int main()
{
    World w = World();

    printf("Preparing scene...\n");

    /* Add lights */
    Light light1 = Light(POINT_LIGHT, Point(-10, 10, -10), Colour(0.6, 0.6, 0.6));
    w.addLight(&light1);
    Sphere light1Sphere = Sphere();
    light1Sphere.dropShadow = false;
    light1Sphere.setTransform(translation(-10, 10, -10) * scaling(1.5, 1.5, 1.5));
    light1Sphere.material.colour = Colour(1, 1, 1);
    light1Sphere.material.ambient = 0.6;
    light1Sphere.material.diffuse = 0;
    light1Sphere.material.specular = 0;
    w.addObject(&light1Sphere);

    Light light2 = Light(POINT_LIGHT, Point(10, 10, -10), Colour(0.6, 0.6, 0.6));
    w.addLight(&light2);
    Sphere light2Sphere = Sphere();
    light2Sphere.dropShadow = false;
    light2Sphere.setTransform(translation(10, 10, -10) * scaling(1.5, 1.5, 1.5));
    light2Sphere.material.colour = Colour(1, 1, 1);
    light2Sphere.material.ambient = 0.6;
    light2Sphere.material.diffuse = 0;
    light2Sphere.material.specular = 0;
    w.addObject(&light2Sphere);

    Light light3 = Light(POINT_LIGHT, Point(-2, 1, -6), Colour(0.2, 0.1, 0.1));
    w.addLight(&light3);
    Sphere light3Sphere = Sphere();
    light3Sphere.dropShadow = false;
    light3Sphere.setTransform(translation(-2, 1, -6) * scaling(.4, .4, .4));
    light3Sphere.material.colour = Colour(1, 0.5, 0.5);
    light3Sphere.material.ambient = 0.6;
    light3Sphere.material.diffuse = 0;
    light3Sphere.material.specular = 0;
    w.addObject(&light3Sphere);

    Light light4 = Light(POINT_LIGHT, Point(-1, -2, -6), Colour(0.1, 0.2, 0.1));
    w.addLight(&light4);
    Sphere light4Sphere = Sphere();
    light4Sphere.dropShadow = false;
    light4Sphere.setTransform(translation(-1, -2, -16) * scaling(.4, .4, .4));
    light4Sphere.material.colour = Colour(0.5, 1, 0.5);
    light4Sphere.material.ambient = 0.6;
    light4Sphere.material.diffuse = 0;
    light4Sphere.material.specular = 0;
    w.addObject(&light4Sphere);

    Light light5 = Light(POINT_LIGHT, Point(3, -1, -6), Colour(0.2, 0.2, 0.2));
    w.addLight(&light5);
    Sphere light5Sphere = Sphere();
    light5Sphere.dropShadow = false;
    light5Sphere.setTransform(translation(3, -1, -6) * scaling(0.5, 0.5, 0.5));
    light5Sphere.material.colour = Colour(1, 1, 1);
    light5Sphere.material.ambient = 0.6;
    light5Sphere.material.diffuse = 0;
    light5Sphere.material.specular = 0;
    w.addObject(&light5Sphere);

    /* ----------------------------- */

    Sphere theBall = Sphere();
    theBall.material.colour = Colour(1, 0.25, 0.25);
    theBall.material.ambient = 0;
    theBall.material.specular = 0;
    theBall.material.diffuse = 0.5;
    theBall.material.reflective = 0.5;
    w.addObject(&theBall);

    Cylinder crown = Cylinder();
    crown.minCap = 0;
    crown.maxCap = 1;
    crown.setTransform(rotationZ(-0.1) * translation(0, 0.9, 0) * scaling(0.2, 0.3, 0.2));
    crown.material.pattern = new CheckersPattern(Colour(1, 1, 1), Colour(0.94, 0.94, 0.94));
    crown.material.pattern->setTransform(scaling(0.2, 0.2, 0.2));
    crown.material.ambient = 0.02;
    crown.material.diffuse = 0.7;
    crown.material.specular = 0.8;
    crown.material.shininess = 20;
    crown.material.reflective = 0.05;
    w.addObject(&crown);

    /* ----------------------------- */

    Shape *s;
    s = fir_branch();
    s->setTransform(translation(-1, -1, 0) * rotationY(0.349) * rotationX(-1.5708) * translation(0, -0.5, 0));
    w.addObject(s);

    s = fir_branch();
    s->setTransform(translation(-1, 1, 0) * rotationY(0.349) * rotationX(-1.5708) * translation(0, -0.5, 0));
    w.addObject(s);

    s = fir_branch();
    s->setTransform(translation(1, -1, 0) * rotationY(-0.349) * rotationX(-1.5708) * translation(0, -0.5, 0));
    w.addObject(s);

    s = fir_branch();
    s->setTransform(translation(1, 1, 0) * rotationY(-0.349) * rotationX(-1.5708) * translation(0, -0.5, 0));
    w.addObject(s);

    s = fir_branch();
    s->setTransform(translation(0.2, -1.25, 0) * rotationY(-0.349) * rotationX(-1.5708) * translation(0, -0.5, 0));
    w.addObject(s);

    s = fir_branch();
    s->setTransform(translation(-0.2, -1.25, 0) * rotationY(0.349) * rotationX(-1.5708) * translation(0, -0.5, 0));
    w.addObject(s);

    s = fir_branch();
    s->setTransform(translation(-1.2, 0.1, 0) * rotationY(0.5236) * rotationX(0.087) * rotationX(-1.5708) * translation(0, -0.5, 0));
    w.addObject(s);

    s = fir_branch();
    s->setTransform(translation(-1.2, -0.35, 0.5) * rotationY(0.5236) * rotationX(-0.1745) * rotationX(-1.5708) * translation(0, -0.5, 0));
    w.addObject(s);

    s = fir_branch();
    s->setTransform(translation(-0.2, 1.5, 0.25) * rotationY(-0.5236) * rotationX(0.087) * rotationX(-1.5708) * translation(0, -0.5, 0));
    w.addObject(s);

    s = fir_branch();
    s->setTransform(translation(1.3, 0.4, 0) * rotationY(-0.5236) * rotationX(-0.087) * rotationX(-1.5708) * translation(0, -0.5, 0));
    w.addObject(s);

    s = fir_branch();
    s->setTransform(translation(1.5, -0.5, 0) * rotationY(-0.1754) * rotationX(0.087) * rotationX(-1.5708) * translation(0, -0.5, 0));
    w.addObject(s);


    /* ----------------------------- */

    FILE *fpOut = fopen("christmas_worlddump.json", "wt");
    if (fpOut)
    {
        w.dumpMe(fpOut);
        fclose(fpOut);
    }
    /* ----------------------------- */


    /* Set the camera */
    Camera camera = Camera(40, 30, 1.047);
    camera.setTransform(viewTransform(Point(0, 0, -4),
                                      Point(0, 0, 0),
                                      Vector(0, 1, 0)));

    printf("And render!\n");
    /* Now render it */
    Canvas image = camera.render(w, 20);

    image.SaveAsPNG("christmasball.png");

    return 0;
}