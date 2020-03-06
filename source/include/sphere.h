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
#include <renderstat.h>
#include <stdio.h>

class Sphere : public Shape
{
protected:
    Intersect localIntersect(Ray r);
    Tuple localNormalAt(Tuple point, Intersection *hit = nullptr);

public:
    Sphere() : Shape(SHAPE_SPHERE) { stats.addSphere(); };
    /* All sphere are at (0, 0, 0) and radius 1 in the object space */


    void dumpMe(FILE *fp);
};

/* Mostly for test purposes */
class GlassSphere : public Sphere
{
public:
    GlassSphere() : Sphere() { this->material.transparency = 1.0; this->material.refractiveIndex = 1.5; };
};

#endif /* DORAYME_SPHERE_H */
