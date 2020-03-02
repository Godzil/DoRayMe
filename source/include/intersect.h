/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Intersect header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_INTERSECT_H
#define DORAYME_INTERSECT_H

#include <stdint.h>
#include <intersection.h>

class Intersect
{
private:
    Intersection **list;
    uint32_t num;
    uint32_t allocated;
public:
    Intersect();
    ~Intersect();
    void reset();
    void add(Intersection i);
    int count() { return this->num; };
    Intersection operator[](const int p) { return *this->list[p]; }
    Intersection hit();
};

#endif /* DORAYME_INTERSECT_H */
