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

    double schlick()
    {
        /* Find the cos of the angle betzeen the eye and normal vector */
        double cos = this->eyeVector.dot(this->normalVector);
        double r0;
        /* Total internal reflection can only occur when n1 > n2 */
        if (this->n1 > this->n2)
        {
            double n, sin2_t;
            n = this->n1 / this->n2;
            sin2_t = (n * n) * (1.0 - (cos * cos));
            if (sin2_t > 1.0)
            {
                return 1.0;
            }
            /* Compute the cos of theta */
            cos = sqrt(1.0 - sin2_t);
        }


        r0 = ((this->n1 - this->n2) / (this->n1 + this->n2));
        r0 = r0 * r0;

        return r0 + (1 - r0) *  ((1 - cos)*(1 - cos)*(1 - cos)*(1 - cos)*(1 - cos));
    };

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

public:
    Intersection(double t, Shape *object) : t(t), object(object) { stats.addIntersection(); };
    bool nothing() { return (this->object == nullptr); };

    Computation prepareComputation(Ray r, Intersect *xs = nullptr);

    bool operator==(const Intersection &b) const { return ((this->t == b.t) && (this->object == b.object)); };
};

#endif /* DORAYME_INTERSECTION_H */
