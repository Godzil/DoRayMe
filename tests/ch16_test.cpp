/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Render test for CSG in chapter 16.
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
#include <csg.h>

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
    Light light1 = Light(POINT_LIGHT, Point(6, 10, 10), Colour(0.5, 0.4, 0.5));
    w.addLight(&light1);

    /* Add lights */
    Light light2 = Light(POINT_LIGHT, Point(6, 10, -2.5), Colour(0.5, 0.6, 0.5));
    w.addLight(&light2);

    /* ----------------------------- */

    /* Floor */
    Plane p = Plane();
    CheckersPattern checkered = CheckersPattern(Colour(0.35, 0.35, 0.35), Colour(0.4, 0.4, 0.4));
    p.material.pattern = &checkered;
    p.material.ambient = 0.2;
    p.material.diffuse = 1;
    p.material.specular = 0;
    p.material.reflective = 0.1;
    p.setTransform(translation(0, 0, 0));
    w.addObject(&p);

    Plane p2 = Plane();
    p2.setTransform(translation(0, 0, -3) * rotationX(M_PI/2));
    p2.material.pattern = &checkered;
    p2.material.ambient = 0.2;
    p2.material.diffuse = 1;
    p2.material.specular = 0;
    w.addObject(&p2);

    /* ----------------------------- */

    /* Funky cube */
    Cylinder c1 = Cylinder();
    c1.minCap = -2;
    c1.maxCap = 2;
    c1.isClosed = true;
    c1.material.colour = Colour(1, 0, 0);
    c1.setTransform(scaling(0.4, 1, 0.4));
    c1.materialSet = true;

    Cylinder c2 = Cylinder();
    c2.minCap = -2;
    c2.maxCap = 2;
    c2.isClosed = true;
    c2.material.colour = Colour(0, 1, 0);
    c2.setTransform(rotationX(M_PI/2) * scaling(0.4, 1, 0.4));
    c2.materialSet = true;

    CSG leaf1 = CSG(CSG::UNION, &c1, &c2);

    Cylinder c3 = Cylinder();
    c3.minCap = -2;
    c3.maxCap = 2;
    c3.isClosed = true;
    c3.material.colour = Colour(0, 0, 1);
    c3.setTransform(rotationZ(M_PI/2) * scaling(0.4, 1, 0.4));
    c3.materialSet = true;

    CSG leaf2 = CSG(CSG::UNION, &leaf1, &c3);

    Cube cb = Cube();
    cb.materialSet = true;
    cb.material.reflective = 0.5;
    cb.material.colour = Colour(0.3, 0.3, 0.3);
    cb.material.ambient = 0;
    cb.material.diffuse = 0.3;
    cb.material.specular = 0.3;
    cb.material.shininess = 20;

    Sphere sp = Sphere();
    sp.setTransform(scaling(1.35, 1.35, 1.35));
    sp.materialSet = true;
    sp.material.colour = Colour(0, 0, 0);
    sp.material.ambient = 0;
    sp.material.specular = 0.3;
    sp.material.shininess = 20;
    sp.material.reflective = 0.05;
    sp.material.diffuse = 0.3;
    CSG leaf3 = CSG(CSG::INTERSECTION, &sp, &cb);

    CSG leaf4 = CSG(CSG::DIFFERENCE, &leaf3, &leaf2);
    leaf4.setTransform(translation(0, 1, 0.8) * rotationY(-0.45));
    w.addObject(&leaf4);

    /* ----------------------------- */

    /* Tricylinder weirdy */
    Cylinder sp1 = Cylinder();
    sp1.minCap = -2;
    sp1.maxCap = 2;
    sp1.isClosed = true;
    sp1.materialSet = true;
    sp1.material.colour = Colour(1, 0, 0);
    Cylinder sp2 = Cylinder();
    sp2.minCap = -2;
    sp2.maxCap = 2;
    sp2.isClosed = true;
    sp2.materialSet = true;
    sp2.setTransform(rotationX(M_PI/2));
    sp2.material.colour = Colour(0, 1, 0);
    Cylinder sp3 = Cylinder();
    sp3.minCap = -2;
    sp3.maxCap = 2;
    sp3.isClosed = true;
    sp3.materialSet = true;
    sp3.setTransform(rotationZ(M_PI/2));
    sp3.material.colour = Colour(0, 0, 1);

    CSG spleaf1 = CSG(CSG::INTERSECTION, &sp1, &sp2);
    CSG spleaf2 = CSG(CSG::INTERSECTION, &spleaf1, &sp3);

    spleaf2.setTransform(translation(4, 1, -0.1) *  rotationY(0.35));
    w.addObject(&spleaf2);

    /* ----------------------------- */

    Group grp = Group();
    int i;
#define SLICE_NUM (12)
    for(i = 0; i < SLICE_NUM; i++)
    {
        Cube *c = new Cube();

        c->setTransform(rotationY((2*M_PI / SLICE_NUM) * i) * scaling(0.1, 1.1, 0.7) * translation(0, 0, 0.9));
        c->dropShadow = false;
        grp.addObject(c);
    }

    grp.materialSet = true;
    grp.dropShadow = false;
    grp.material.ambient = 0;
    grp.material.diffuse = 0.1;
    grp.material.specular = 0;
    grp.material.transparency = 1;
    grp.material.reflective = 1;
    grp.material.refractiveIndex = 1;

    Sphere ballSp = Sphere();
    ballSp.materialSet = true;
    ballSp.material.colour = Colour(0.7, 0.2, 0.1);
    CSG ballLeaf = CSG(CSG::INTERSECTION, &grp, &ballSp);

    ballLeaf.setTransform(translation(-4, 1, -0.1) *  rotationY(-0.35) * rotationZ(0.1));
    w.addObject(&ballLeaf);

    /* ----------------------------- */

    /* Set the camera */
    Camera camera = Camera(80, 40, M_PI / 2);
    camera.setTransform(viewTransform(Point(0, 3, 5),
                                      Point(0, 1, 0),
                                      Vector(0, 1, 0)));

    /* Now render it */
    Canvas image = camera.render(w, 5);

    image.SaveAsPNG("ch16_test.png");

    return 0;
}