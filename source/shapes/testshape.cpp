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

void TestShape::localIntersect(Ray r, Intersect &xs)
{
    this->localRay = r;
}

Tuple TestShape::localNormalAt(Tuple point, Intersection *hit)
{
     return Vector(point.x, point.y, point.z);
}