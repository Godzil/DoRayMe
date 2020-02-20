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

#include <shape.h>
#include <ray.h>
#include <intersect.h>

class Sphere : public Shape
{
public:
    Sphere() : Shape(SHAPE_SPHERE) { };
    /* All sphere are at (0, 0, 0) and radius 1 in the object space */
    virtual Intersect intersect(Ray r);
    virtual Tuple normalAt(Tuple point);
};

#endif /* DORAYME_SPHERE_H */
