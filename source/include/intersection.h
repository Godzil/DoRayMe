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

struct Intersection
{
    double t;
    Object *object;
};

static Intersection *newIntersection(double t, Object *object)
{
    Intersection *ret = (Intersection *)calloc(sizeof(Intersection), 1);

    if (ret != nullptr)
    {
        ret->t = t;
        ret->object = object;
    }

    return ret;
}

static void freeIntersection(Intersection *i)
{
    if ( i != nullptr )
    {
        free(i);
    }
}

#endif //DORAYME_INTERSECTION_H
