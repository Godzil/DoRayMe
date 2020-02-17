/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Sphere header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_SPHERE_H
#define DORAYME_SPHERE_H

#include <object.h>
#include <ray.h>
#include <intersect.h>

class Sphere : public Object
{
public:
    /* All sphere are at (0, 0, 0) and radius 1*/
    virtual Intersect intersect(Ray r);
};

#endif //DORAYME_SPHERE_H
