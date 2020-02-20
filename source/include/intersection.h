/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Intersection header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_INTERSECTION_H
#define DORAYME_INTERSECTION_H

#include <stdlib.h>
#include <ray.h>

class Shape;

struct Computation
{
    Computation(Shape *object, double t, Tuple point, Tuple eyev, Tuple normalv, bool inside) :
          object(object), t(t), hitPoint(point), eyeVector(eyev), normalVector(normalv), inside(inside) { };
    Shape *object;
    double t;
    Tuple hitPoint;
    Tuple eyeVector;
    Tuple normalVector;

    bool inside;
};

class Intersection
{
public:
    double t;
    Shape *object;

public:
    Intersection(double t, Shape *object) : t(t), object(object) { };
    bool nothing() { return (this->object == nullptr); };

    Computation prepareComputation(Ray r);

    bool operator==(const Intersection &b) const { return ((this->t == b.t) && (this->object == b.object)); };
};

#endif //DORAYME_INTERSECTION_H
