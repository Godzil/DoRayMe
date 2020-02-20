/*
 *  DoRayMe - a quick and dirty Raytracer
 *  World implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <world.h>
#include <light.h>
#include <shape.h>

#define MIN_ALLOC (2)

World::World() : objectCount(0), lightCount(0)
{
    this->allocatedLightCount = MIN_ALLOC;
    this->lightList = (Light **)calloc(sizeof(Light *), MIN_ALLOC);
    this->lightCount = 0;

    this->allocatedObjectCount = MIN_ALLOC;
    this->objectList = (Shape **)calloc(sizeof(Shape *), MIN_ALLOC);
    this->objectCount = 0;
};

World::~World()
{
    /* We need to do some cleanup... */
}

void World::addObject(Shape *s)
{
    if ((this->objectCount + 1) > this->allocatedObjectCount)
    {
        this->allocatedObjectCount *= 2;
        this->objectList = (Shape **)realloc(this->objectList, sizeof(Shape **) * this->allocatedObjectCount);
    }
    this->objectList[this->objectCount++] = s;
}

void World::addLight(Light *l)
{
    if ((this->lightCount + 1) > this->allocatedLightCount)
    {
        this->allocatedLightCount *= 2;
        this->lightList = (Light **)realloc(this->lightList, sizeof(Light **) * this->allocatedLightCount);
    }
    this->lightList[this->lightCount++] = l;
}

bool World::lightIsIn(Light &l)
{
    int i;
    for(i = 0; i < this->lightCount; i++)
    {
        if (*this->lightList[i] == l)
        {
            return true;
        }
    }
    return false;
}

bool World::objectIsIn(Shape &s)
{
    int i;
    for(i = 0; i < this->objectCount; i++)
    {
        if (*this->objectList[i] == s)
        {
            return true;
        }
    }
    return false;
}

Intersect World::intersect(Ray r)
{
    Intersect ret;
    int i, j;

    for(i = 0; i < this->objectCount; i++)
    {
        Intersect xs = this->objectList[i]->intersect(r);

        for(j = 0; j < xs.count(); j++)
        {
            ret.add(xs[j]);
        }
    }

    return ret;
}

Tuple World::shadeHit(Computation comps)
{
    return comps.object->material.lighting(*this->lightList[0], comps.hitPoint, comps.eyeVector, comps.normalVector);
}

Tuple World::colourAt(Ray r)
{
    Intersection hit = this->intersect(r).hit();

    if (hit.nothing())
    {
        return Colour(0, 0, 0);
    }
    else
    {
        return this->shadeHit(hit.prepareComputation(r));
    }
}