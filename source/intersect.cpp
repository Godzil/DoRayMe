/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Intersect implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <stdlib.h>
#include <math_helper.h>
#include <intersect.h>

#include <float.h>

#define MIN_ALLOC (2)

Intersect::Intersect()
{
    this->allocated = MIN_ALLOC;
    this->list = (Intersection *)calloc(sizeof(Intersection *), MIN_ALLOC);
    this->num = 0;
}

void Intersect::add(Intersection i)
{
    if ((this->num + 1) > this->allocated)
    {
        this->allocated *= 2;
        this->list = (Intersection *)realloc(this->list, sizeof(Intersection *) * this->allocated);
    }
    this->list[this->num++] = i;
}

Intersection Intersect::hit()
{
    int i;
    double minHit = DBL_MAX;
    uint32_t curHit = -1;
    for(i = 0; i < this->num; i++)
    {
        if ((this->list[i].t >= 0) && (this->list[i].t < minHit))
        {
            curHit = i;
            minHit = this->list[i].t;
        }
    }

    if (curHit == -1)
    {
        return Intersection(0, nullptr);
    }

    return this->list[curHit];
}