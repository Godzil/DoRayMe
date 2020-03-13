/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Render test for OBJ File using teapots in chapter 15.
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <world.h>
#include <light.h>
#include <plane.h>
#include <cube.h>
#include <sphere.h>
#include <material.h>
#include <colour.h>
#include <canvas.h>
#include <camera.h>
#include <objfile.h>

#include <pattern.h>
#include <strippattern.h>
#include <gradientpattern.h>
#include <checkerspattern.h>
#include <ringpattern.h>

#include <transformation.h>
#include <cylinder.h>

int main()
{
    World w = World();

    /* Add lights */
   /* Light light1 = Light(POINT_LIGHT, Point(10, 100, 10), Colour(.1, .1, .1));
    w.addLight(&light1);
    Light light2 = Light(POINT_LIGHT, Point(10, 100, -10), Colour(.1, .1, .2));
    w.addLight(&light2);
    Light light3 = Light(POINT_LIGHT, Point(-10, 100, 10), Colour(.1, .1, .1));
    w.addLight(&light3);
    Light light4 = Light(POINT_LIGHT, Point(-10, 100, -10), Colour(.1, .1, .1));
    w.addLight(&light4);*/

    Light light1 = Light(POINT_LIGHT, Point(0, 100, 0), Colour(.3, .3, .3));
    w.addLight(&light1);


    Point lightPos = Point(3.8, 6.8, 4.5);
    Light mouthLight = Light(POINT_LIGHT, lightPos, Colour(0.5, 0.5, 0.5));
    w.addLight(&mouthLight);

    Light mainLight = Light(POINT_LIGHT,  Point(8, 10, 16), Colour(1, 1, 1));
    w.addLight(&mainLight);

    /* ----------------------------- */
#if 0
    /* Spot light */
    Sphere spot = Sphere();
    spot.dropShadow = false;
    spot.setTransform(translation(lightPos.x, lightPos.y, lightPos.z) * scaling(0.2, 0.2, 0.2));
    w.addObject(&spot);

    Cylinder X = Cylinder();
    X.minCap = 0;
    X.maxCap = 4;
    Cylinder Y = Cylinder();
    Y.minCap = 0;
    Y.maxCap = 4;
    Cylinder Z = Cylinder();
    Z.minCap = 0;
    Z.maxCap = 4;
    Z.materialSet = Y.materialSet = X.materialSet = true;
    X.material.ambient = 1;
    X.material.specular = 0;
    X.material.diffuse = 0;
    Z.material = Y.material = X.material;
    Z.dropShadow = Y.dropShadow = X.dropShadow = false;
    X.material.colour = Colour(1, 0, 0);
    Y.material.colour = Colour(0, 1, 0);
    Z.material.colour = Colour(0, 0, 1);

    Y.setTransform(translation(lightPos.x, lightPos.y, lightPos.z) * scaling(0.1, 1, 0.1));
    X.setTransform(translation(lightPos.x, lightPos.y, lightPos.z) * rotationZ(M_PI/2) *  scaling(0.1, 1, 0.1));
    Z.setTransform(translation(lightPos.x, lightPos.y, lightPos.z) * rotationX(M_PI/2) *  scaling(0.1, 1, 0.1));
    w.addObject(&X);
    w.addObject(&Y);
    w.addObject(&Z);
#endif

    /* Floor */
    Material floorMaterial;
    floorMaterial.colour = Colour(0.2, 0.3, 0.3);
    floorMaterial.reflective = 0.3;
    floorMaterial.specular = 0.4;
    floorMaterial.shininess = 5;
    floorMaterial.ambient = 0;
    floorMaterial.diffuse = 0.8;

    /* Let's use a cube for the floor */
    Cube floor = Cube();
    floor.setMaterial(floorMaterial);
    floor.setTransform(translation(0, -0.1, 0) * scaling(10, 0.1, 10));
    w.addObject(&floor);

    Material dragonMat;
    dragonMat.colour = Colour(0.23, 0.75, 0.39);
    dragonMat.reflective = 0.9;
    dragonMat.transparency = 0.99;
    dragonMat.specular = 0.9;
    dragonMat.shininess = 50;
    dragonMat.refractiveIndex = 1.6;
    dragonMat.ambient = 0;
    dragonMat.diffuse = 0.7;

    Shape *dragon = OBJFile("dragon.obj").getBaseGroup();
    dragon->setTransform(rotationY(M_PI * 0.75) * scaling(2, 2, 2));
    dragon->setMaterial(dragonMat);
    w.addObject(dragon);

    /* ----------------------------- */

    OctreeOptimisation opt;
    w.finalise(opt);

    /* Set the camera */
    Camera camera = Camera(40, 30, M_PI/2);
    camera.setTransform(viewTransform(Point(-5, 10, 13),
                                      Point(0, 1, 0),
                                      Vector(0, 1, 0)));

    /* Now render it */
    Canvas image = camera.render(w, 5);

    image.SaveAsPNG("ch15_teapot_objfile.png");

    return 0;
}
