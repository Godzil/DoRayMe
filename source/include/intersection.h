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

class Object;

class Intersection
{
public:
    double t;
    Object *object;

public:
    Intersection(double t, Object *object) : t(t), object(object) { };
};

#endif //DORAYME_INTERSECTION_H
