/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Test shape implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <shape.h>
#include <testshape.h>

TestShape::TestShape() : localRay(Point(0, 0, 0), Vector(0, 0, 0))
{
}

Intersect TestShape::localIntersect(Ray r)
{
    this->localRay = r;
    return Intersect();
}

Tuple TestShape::localNormalAt(Tuple point)
{
     return Vector(point.x, point.y, point.z);
}