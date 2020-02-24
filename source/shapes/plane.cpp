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

Intersect Plane::localIntersect(Ray r)
{
    double t;
    Intersect ret = Intersect();

    if (fabs(r.direction.y) < getEpsilon())
    {
        /* With a direction == 0, the ray can't intersect the plane */
        return ret;
    }

    t = -r.origin.y / r.direction.y;

    ret.add(Intersection(t, this));

    return ret;
}

Tuple Plane::localNormalAt(Tuple point)
{
    return Vector(0, 1, 0);
}

BoundingBox Plane::getBounds()
{
    BoundingBox ret;

    ret.min = this->objectToWorld(Point(-INFINITY, 0-getEpsilon(), -INFINITY));
    ret.max = this->objectToWorld(Point(INFINITY, 0+getEpsilon(), INFINITY));

    return ret;
}