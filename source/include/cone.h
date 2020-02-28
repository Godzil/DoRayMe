/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Cone header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_CONE_H
#define DORAYME_CONE_H

#include <shape.h>
#include <ray.h>
#include <intersect.h>
#include <renderstat.h>
#include <stdio.h>

class Cone : public Shape {
protected:
    Intersect localIntersect(Ray r);

    Tuple localNormalAt(Tuple point);

    bool checkCap(Ray r, double t, double y);
    void intersectCaps(Ray r, Intersect &xs);

public:
    bool isClosed;
    double minCap;
    double maxCap;

    Cone() : minCap(-INFINITY), maxCap(INFINITY), isClosed(false), Shape(SHAPE_CONE) { stats.addCone(); };
    BoundingBox getLocalBounds();
    bool haveFiniteBounds() { return !(isinf(this->minCap) || isinf(this->maxCap)); };

    void dumpMe(FILE *fp);
};

#endif /* DORAYME_CONE_H */
