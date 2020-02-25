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

    Cone() : minCap(-INFINITY), maxCap(INFINITY), isClosed(false), Shape(SHAPE_CONE) {};
    BoundingBox getBounds();
    bool haveFiniteBounds() { return !(isinf(this->minCap) || isinf(this->maxCap)); };
};

#endif /* DORAYME_CONE_H */
