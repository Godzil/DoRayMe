/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Plane implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <tuple.h>
#include <ray.h>
#include <shape.h>
#include <plane.h>
#include <math_helper.h>

void Plane::localIntersect(Ray r, Intersect &xs)
{
    double t;

    if (fabs(r.direction.y) < getEpsilon())
    {
        /* With a direction == 0, the ray can't intersect the plane */
    }
    else
    {
        t = -r.origin.y / r.direction.y;

        xs.add(Intersection(t, this));
    }
}

Tuple Plane::localNormalAt(Tuple point, Intersection *hit)
{
    return Vector(0, 1, 0);
}

BoundingBox Plane::getLocalBounds()
{
    BoundingBox ret;

    ret | Point(-INFINITY, 0-getEpsilon(), -INFINITY);
    ret | Point(INFINITY, 0+getEpsilon(), INFINITY);

    return ret;
}