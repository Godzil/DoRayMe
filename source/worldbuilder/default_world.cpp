/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Default World builder implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <worldbuilder.h>
#include <world.h>

#include <sphere.h>
#include <light.h>
#include <material.h>
#include <transformation.h>

DefaultWorld::DefaultWorld()
{
    Light *l = new Light(POINT_LIGHT, Point(-10, 10, -10), Colour(1, 1, 1));
    Sphere *s1 = new Sphere();
    Sphere *s2 = new Sphere();
    Material s1Mat = Material();
    s1Mat.colour = Colour(0.8, 1.0, 0.6);
    s1Mat.diffuse = 0.7;
    s1Mat.specular = 0.2;
    s1->setMaterial(s1Mat);

    s2->setTransform(scaling(0.5, 0.5,0.5));

    this->addLight(l);

    this->addObject(s1);
    this->addObject(s2);
}
