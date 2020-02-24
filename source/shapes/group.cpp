/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Group implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <tuple.h>
#include <ray.h>
#include <group.h>
#include <cone.h>
#include <math_helper.h>

#define MIN_ALLOC (2)

Group::Group() : Shape(SHAPE_GROUP)
{
    this->allocatedObjectCount = MIN_ALLOC;
    this->objectList = (Shape **)calloc(sizeof(Shape *), MIN_ALLOC);
    this->objectCount = 0;
}

Intersect Group::intersect(Ray r)
{
    Intersect ret;
    int i, j;
    if (this->objectCount > 0)
    {
        for(i = 0; i < this->objectCount; i++)
        {
            Intersect xs = this->objectList[i]->intersect(r);
            if (xs.count() > 0)
            {
                for(j = 0; j < xs.count(); j++)
                {
                    ret.add(xs[j]);
                }
            }
        }
    }

    return ret;
}

Intersect Group::localIntersect(Ray r)
{
    return Intersect();
}

Tuple Group::localNormalAt(Tuple point)
{
    return Vector(1, 0, 0);
}

void Group::addObject(Shape *s)
{
    if ((this->objectCount + 1) > this->allocatedObjectCount)
    {
        this->allocatedObjectCount *= 2;
        this->objectList = (Shape **)realloc(this->objectList, sizeof(Shape **) * this->allocatedObjectCount);
    }

    s->parent = this;
    s->updateTransform();

    this->objectList[this->objectCount++] = s;
}

bool Group::isEmpty()
{
    return (this->objectCount == 0);
}