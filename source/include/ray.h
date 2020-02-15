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

class Ray
{
public:
    Vector direction;
    Point origin;

    Ray(Point origin, Vector direction) : origin(origin), direction(direction) { };

    Tuple position(double t) { return this->origin + this->direction * t; };
};

#endif //DORAYME_RAY_H
