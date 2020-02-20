/*
 *  DoRayMe - a quick and dirty Raytracer
 *  World header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_WORLD_H
#define DORAYME_WORLD_H

#include <stdint.h>
#include <light.h>
#include <shape.h>
#include <intersect.h>
#include <ray.h>

class World
{
public:
    uint32_t objectCount;
    uint32_t lightCount;

private:
    uint32_t allocatedObjectCount;
    uint32_t allocatedLightCount;

    Light* *lightList;
    Shape* *objectList;

public:
    World();
    ~World();

    void addObject(Shape *s);
    void addLight(Light *l);

    /* Some debug things */
    bool lightIsIn(Light &l);
    bool objectIsIn(Shape &s);

    Shape *getObject(int i) { return this->objectList[i]; };

    Tuple shadeHit(Computation comps);;
    Tuple colourAt(Ray r);
    bool isShadowed(Tuple point);

    Intersect intersect(Ray r);

};

#endif /* DORAYME_WORLD_H */
