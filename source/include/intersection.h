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
#include <material.h>
#include <renderstat.h>

class Shape;
class Intersect;

struct Computation
{
    Computation(Shape *object, double t, Tuple point, Tuple eyev, Tuple normalv, Tuple overHitP,
                bool inside, Tuple reflectV = Vector(0, 0, 0), double n1 = 1.0, double n2 = 1.0,
                Tuple underHitP = Point(0, 0, 0), Material *objMat = nullptr) :
          object(object), t(t), hitPoint(point), eyeVector(eyev), normalVector(normalv), inside(inside),
          overHitPoint(overHitP), underHitPoint(underHitP), reflectVector(reflectV), n1(n1), n2(n2), material(objMat) { };

    double schlick();

    Shape *object;
    double t;
    Tuple hitPoint;
    Tuple overHitPoint;
    Tuple underHitPoint;
    Tuple eyeVector;
    Tuple normalVector;
    Tuple reflectVector;

    Material *material;

    double n1;
    double n2;

    bool inside;
};

class Intersection
{
public:
    double t;
    Shape *object;
    double u, v;

public:
    Intersection(double t, Shape *object, double u = NAN, double v = NAN) : t(t), object(object), u(u), v(v) { stats.addIntersection(); };
    bool nothing() { return (this->object == nullptr); };

    Computation prepareComputation(Ray r, Intersect *xs = nullptr);

    bool operator==(const Intersection &b) const { return ((this->t == b.t) && (this->object == b.object)); };
};

#endif /* DORAYME_INTERSECTION_H */
