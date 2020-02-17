/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Object header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_OBJECT_H
#define DORAYME_OBJECT_H

class Object;

#include <ray.h>
#include <intersect.h>

/* Base class for all object that can be presented in the world */
class Object
{
public:
    virtual Intersect intersect(Ray r);
};

#endif //DORAYME_OBJECT_H
