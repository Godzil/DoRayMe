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
#include <renderstat.h>
#include <stdio.h>

class Cylinder : public Shape {

protected:
    void localIntersect(Ray r, Intersect &xs);

    Tuple localNormalAt(Tuple point, Intersection *hit = nullptr);

    bool checkCap(Ray r, double t);
    void intersectCaps(Ray r, Intersect &xs);

public:
    bool isClosed;
    double minCap;
    double maxCap;

    Cylinder() : minCap(-INFINITY), maxCap(INFINITY), isClosed(false), Shape(Shape::CYLINDER) { stats.addCylinder(); };

    BoundingBox getLocalBounds();
    bool haveFiniteBounds() { return !(isinf(this->minCap) || isinf(this->maxCap)); };

    void dumpMe(FILE *fp);
};

#endif //DORAYME_CYLINDER_H
