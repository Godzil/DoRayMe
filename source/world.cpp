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

Tuple World::shadeHit(Computation comps, uint32_t depthCount)
{
    /* TODO: Add support for more than one light */

    bool isThereAnObstacle = this->isShadowed(comps.overHitPoint);

    Tuple surface = comps.object->material.lighting(*this->lightList[0], comps.overHitPoint, comps.eyeVector,
            comps.normalVector, comps.object, isThereAnObstacle);

    Tuple reflected = this->reflectColour(comps, depthCount);
    Tuple refracted = this->refractedColour(comps, depthCount);

    if ((comps.object->material.reflective > 0) && (comps.object->material.transparency > 0))
    {
        double reflectance = comps.schlick();

        return surface + reflected * reflectance + refracted * (1 - reflectance);

    }

    return surface + reflected + refracted;
}

Tuple World::colourAt(Ray r, uint32_t depthCount)
{
    Intersect allHits = this->intersect(r);
    Intersection hit = allHits.hit();

    if (hit.nothing())
    {
        return Colour(0, 0, 0);
    }
    else
    {
        return this->shadeHit(hit.prepareComputation(r, &allHits), depthCount);
    }
}

bool World::isShadowed(Tuple point)
{
    /* TODO: Add support for more than one light */

    Tuple v = this->lightList[0]->position - point;
    double distance = v.magnitude();
    Tuple direction = v.normalise();

    Ray r = Ray(point, direction);
    Intersection h = this->intersect(r).hit();

    if (!h.nothing() && (h.t < distance))
    {
        return true;
    }

    return false;
}

Colour World::reflectColour(Computation comps, uint32_t depthCount)
{
    if ((depthCount == 0) || (comps.object->material.reflective == 0))
    {
        return Colour(0, 0, 0);
    }

    /* So it is reflective, even just a bit. Let'sr reflect the ray! */
    Ray reflectedRay = Ray(comps.overHitPoint, comps.reflectVector);

    Tuple hitColour = this->colourAt(reflectedRay, depthCount - 1);
    hitColour = hitColour * comps.object->material.reflective;

    return Colour(hitColour.x, hitColour.y, hitColour.z);
}

Colour World::refractedColour(Computation comps, uint32_t depthCount)
{
    double nRatio = comps.n1 / comps.n2;
    double cos_i = comps.eyeVector.dot(comps.normalVector);
    double sin2_t = (nRatio*nRatio) * (1 - cos_i * cos_i);

    if ((sin2_t > 1 ) || (depthCount == 0) || (comps.object->material.transparency == 0))
    {
        return Colour(0, 0, 0);
    }

    double cos_t = sqrt(1.0 - sin2_t);
    Tuple direction = comps.normalVector * (nRatio * cos_i - cos_t) - comps.eyeVector * nRatio;

    Ray refractedRay = Ray(comps.underHitPoint, direction);

    Tuple hitColour = this->colourAt(refractedRay, depthCount - 1) * comps.object->material.transparency;

    return Colour(hitColour.x, hitColour.y, hitColour.z);
}