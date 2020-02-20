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
    bool inside = false;

    if (normalV.dot(eyeV) < 0)
    {
        inside = true;
        normalV = -normalV;
    }

    Tuple overHitP = hitP + normalV * getEpsilon();

    return Computation(this->object,
                       this->t,
                       hitP,
                       eyeV,
                       normalV,
                       overHitP,
                       inside);
}