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
private:
    Intersect localIntersect(Ray r);
    Tuple localNormalAt(Tuple point);

public:
    Sphere() : Shape(SHAPE_SPHERE) { };
    /* All sphere are at (0, 0, 0) and radius 1 in the object space */
};

#endif /* DORAYME_SPHERE_H */
