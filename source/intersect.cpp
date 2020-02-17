/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Intersect implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <stdlib.h>

#include <intersect.h>

#define MIN_ALLOC (2)

Intersect::Intersect()
{
    this->allocated = MIN_ALLOC;
    this->list = (Intersection **)calloc(sizeof(Object *), MIN_ALLOC);
    this->num = 0;
}

void Intersect::add(Intersection *i)
{
    if ((this->num + 1) < this->allocated)
    {
        this->allocated *= 2;
        this->list = (Intersection **)realloc(this->list, sizeof(Object *) * this->allocated);
    }
    this->list[this->num++] = i;
}