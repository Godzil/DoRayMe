/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Cylinder header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_CYLINDER_H
#define DORAYME_CYLINDER_H

#include <shape.h>
#include <ray.h>
#include <intersect.h>

class Cylinder : public Shape {
private:
    Intersect localIntersect(Ray r);

    Tuple localNormalAt(Tuple point);

    bool checkCap(Ray r, double t);
    void intersectCaps(Ray r, Intersect &xs);

public:
    bool isClosed;
    double minCap;
    double maxCap;

    Cylinder() : minCap(-INFINITY), maxCap(INFINITY), isClosed(false), Shape(SHAPE_CYLINDER) {};
};

#endif //DORAYME_CYLINDER_H
