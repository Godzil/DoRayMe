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
    this->list = (Intersection **)calloc(sizeof(Intersection *), MIN_ALLOC);
    this->num = 0;
}

Intersect::~Intersect()
{
    /* Free stuff */
}

void Intersect::add(Intersection i)
{
    Intersection *x;
    int j, k;

    if ((this->num + 1) > this->allocated)
    {
        this->allocated *= 2;
        this->list = (Intersection **)realloc(this->list, sizeof(Intersection *) * this->allocated);
    }
    this->list[this->num++] = new Intersection(i.t, i.object);

    /* Now sort.. */
    for(j = 1; j < (this->num); j++)
    {
        x = this->list[j];
        k = j;
        while( (k > 0) && (this->list[k - 1]->t) > x->t )
        {
            this->list[k] = this->list[k - 1];
            k--;
        }
        this->list[k] = x;
    }
}

Intersection Intersect::hit()
{
    int i;

    for(i = 0; i < this->num; i++)
    {
        if (this->list[i]->t >= 0)
            return *this->list[i];
    }

    return Intersection(0, nullptr);
}