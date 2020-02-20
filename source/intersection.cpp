/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Intersection implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <intersection.h>
#include <shape.h>

Computation Intersection::prepareComputation(Ray r)
{
    Tuple hitP = r.position(this->t);
    Tuple normalV = this->object->normalAt(hitP);
    Tuple eyeV = -r.direction;
    bool inside;

    if (normalV.dot(eyeV) < 0)
    {
        inside = true;
        normalV = -normalV;
    }


    return Computation(this->object,
                       this->t,
                       hitP,
                       eyeV,
                       normalV,
                       inside);
}