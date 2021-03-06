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
#include <renderstat.h>

#define MIN_ALLOC (2)

/* TODO: Memory allocation, even if using standard calloc/realloc have a huge impact on performances. need to find a way
 * to reuse the intersect object without reallocating from scratch all the time. We use a lot of Intersect objects as
 * there is at least 2 per ray (one for Ray intersect object, one object per light)
 */

Intersect::Intersect()
{
    this->allocated = MIN_ALLOC;
    this->list = (Intersection **)calloc(sizeof(Intersection *), MIN_ALLOC);
    if (this->list != nullptr)
    {
        stats.addMalloc();
        stats.addIntersect();
        this->num = 0;
    }
    else
    {
        printf("ABORT: Allocation error [%s]!\n", __FUNCTION__);
        exit(-1);
    }
}

Intersect::~Intersect()
{
    int i;
    for(i = 0; i < this->num; i++)
    {
        if (this->list[i] != nullptr)
        {
            delete this->list[i];
            this->list[i] = nullptr;
        }
    }
    /* Free stuff */
    if (this->list != nullptr)
    {
        free(this->list);
        this->list = nullptr;
    }
}

void Intersect::reset()
{
    this->num = 0;
}

void Intersect::add(Intersection i)
{
    Intersection *x;
    int j, k;

    if ((this->num + 1) > this->allocated)
    {
        this->allocated *= 2;
        stats.addRealloc();
        this->list = (Intersection **)realloc(this->list, sizeof(Intersection *) * this->allocated);
    }

    this->list[this->num++] = new Intersection(i.t, i.object, i.u, i.v);

    stats.setMaxIntersect(this->num);

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