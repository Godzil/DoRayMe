/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Render test for Group and Bounding box in chapter 14.
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

Shape *leg()
{
    Group *ret = new Group();
    Sphere *s = new Sphere();
    s->setTransform(translation(0, 0, -1) * scaling(0.25, 0.25, 0.25));
    ret->addObject(s);
    Cylinder *cyl = new Cylinder();
    cyl->minCap = 0;
    cyl->maxCap = 1;
    cyl->isClosed = false;
    cyl->setTransform(translation(0, 0, -1) * rotationY(-0.5236) * rotationZ(-1.5708) * scaling(0.25, 1, 0.25));

    ret->addObject(cyl);

    return ret;
}

Shape *cap()
{
    Group *ret = new Group();

    Cone *c = new Cone();
    c->minCap = -1;
    c->maxCap = 0;
    c->isClosed = false;
    c->setTransform(rotationX(-0.7854) * scaling(0.24606, 1.37002, 0.24606));
    ret->addObject(c);

    c = new Cone();
    c->minCap = -1;
    c->maxCap = 0;
    c->isClosed = false;
    c->setTransform(rotationY(1.0472) * rotationX(-0.7854) * scaling(0.24606, 1.37002, 0.24606));
    ret->addObject(c);

    c = new Cone();
    c->minCap = -1;
    c->maxCap = 0;
    c->isClosed = false;
    c->setTransform(rotationY(2.0944) * rotationX(-0.7854) * scaling(0.24606, 1.37002, 0.24606));
    ret->addObject(c);

    c = new Cone();
    c->minCap = -1;
    c->maxCap = 0;
    c->isClosed = false;
    c->setTransform(rotationY(3.1416) * rotationX(-0.7854) * scaling(0.24606, 1.37002, 0.24606));
    ret->addObject(c);

    c = new Cone();
    c->minCap = -1;
    c->maxCap = 0;
    c->isClosed = false;
    c->setTransform(rotationY(4.1888) * rotationX(-0.7854) * scaling(0.24606, 1.37002, 0.24606));
    ret->addObject(c);

    c = new Cone();
    c->minCap = -1;
    c->maxCap = 0;
    c->isClosed = false;
    c->setTransform(rotationY(5.236) * rotationX(-0.7854) * scaling(0.24606, 1.37002, 0.24606));
    ret->addObject(c);

    return ret;
}

Shape *wacky()
{
    Group *ret = new Group();

    Shape *s;

    s = leg();
    ret->addObject(s);

    s = leg();
    s->setTransform(rotationY(1.0472));
    ret->addObject(s);

    s = leg();
    s->setTransform(rotationY(2.0944));
    ret->addObject(s);

    s = leg();
    s->setTransform(rotationY(3.1416));
    ret->addObject(s);

    s = leg();
    s->setTransform(rotationY(4.1888));
    ret->addObject(s);

    s = leg();
    s->setTransform(rotationY(5.236));
    ret->addObject(s);

    s = cap();
    s->setTransform(translation(0, 1, 0));
    ret->addObject(s);

    s = cap();
    s->setTransform(rotationX(3.1416) * translation(0, 1, 0));
    ret->addObject(s);
    
    return ret;
}
int main()
{
    World w = World();

    /* Add lights */
    Light light1 = Light(POINT_LIGHT, Point(10000, 10000, -10000), Colour(0.25, 0.25, 0.25));
    w.addLight(&light1);
    Light light2 = Light(POINT_LIGHT, Point(-10000, 10000, -10000), Colour(0.25, 0.25, 0.25));
    w.addLight(&light2);
    Light light3 = Light(POINT_LIGHT, Point(10000, -10000, -10000), Colour(0.25, 0.25, 0.25));
    w.addLight(&light3);
    Light light4 = Light(POINT_LIGHT, Point(-10000, -10000, -10000), Colour(0.25, 0.25, 0.25));
    w.addLight(&light4);

    /* ----------------------------- */

    /* White background */
    Plane p = Plane();
    p.setTransform(translation(0, 0, 100) *  rotationX(1.5708));
    p.material.colour = Colour(1, 1, 1);
    p.material.ambient = 1;
    p.material.diffuse = 0;
    p.material.specular = 0;
    w.addObject(&p);
    
    Shape *wa;
    
    wa = wacky();
    wa->setTransform(translation(-2.8, 0, 0) * rotationX(0.4363) * rotationY(0.1745));
    wa->material.colour = Colour(0.9, 0.2, 0.4);
    wa->material.ambient = 0.2;
    wa->material.diffuse = 0.8;
    wa->material.specular = 0.7;
    wa->material.shininess = 20;
    w.addObject(wa);

    wa = wacky();
    wa->setTransform(rotationY(0.1745));
    wa->material.colour = Colour(0.2, 0.9, 0.6);
    wa->material.ambient = 0.2;
    wa->material.diffuse = 0.8;
    wa->material.specular = 0.7;
    wa->material.shininess = 20;
    w.addObject(wa);

    wa = wacky();
    wa->setTransform(translation(2.8, 0, 0) * rotationX(-0.4363) * rotationY(-0.1745));
    wa->material.colour = Colour(0.2, 0.3, 1.0);
    wa->material.ambient = 0.2;
    wa->material.diffuse = 0.8;
    wa->material.specular = 0.7;
    wa->material.shininess = 20;
    w.addObject(wa);

    /* ----------------------------- */

    /* Set the camera */
    Camera camera = Camera(1000, 334, 0.9);
    camera.setTransform(viewTransform(Point(0, 0, -9),
                                      Point(0, 0, 0),
                                      Vector(0, 1, 0)));

    /* Now render it */
    Canvas image = camera.render(w, 5);

    image.SaveAsPNG("ch14_test.png");

    return 0;
}