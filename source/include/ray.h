/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Ray header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_RAY_H
#define DORAYME_RAY_H

#include <tuple.h>
#include <renderstat.h>

class Ray
{
public:
    Tuple direction;
    Tuple origin;

    Ray(Tuple origin, Tuple direction) : origin(origin), direction(direction) { stats.addRay(); };

    Tuple position(double t) { return this->origin + this->direction * t; };
};

#endif /* DORAYME_RAY_H */
