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
#include <stdio.h>

#ifdef ENABLE_LUA_SUPPORT
extern "C" {
#include <lua.h>
}
#endif

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

#ifdef ENABLE_LUA_SUPPORT
    lua_State *L;
#endif

public:
    World();
    ~World();

    void addObject(Shape *s);
    void addLight(Light *l);

    /* Some debug things */
    bool lightIsIn(Light &l);
    bool objectIsIn(Shape &s);

    Shape *getObject(int i) { return this->objectList[i]; };
    Light *getLight(int i) { return this->lightList[i]; };

    Tuple shadeHit(Computation comps, uint32_t depthCount = 4);
    Tuple colourAt(Ray r, uint32_t depthCount = 4);
    bool isShadowed(Tuple point, Tuple lightPosition);

    Colour reflectColour(Computation comps, uint32_t depthCount = 4);
    Colour refractedColour(Computation comps, uint32_t depthCount = 4);

    Intersect intersect(Ray r);

    void dumpMe(FILE *fp);
};

#endif /* DORAYME_WORLD_H */
