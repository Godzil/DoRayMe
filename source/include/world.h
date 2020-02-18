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

class World
{
public:
    uint32_t objectCount;
    uint32_t lightCount;

private:
    uint32_t allocatedObjectCount;
    uint32_t allocatedLightCount;

    Light *lightList;
    Shape *shapeList;

public:
    World() : objectCount(0), lightCount(0) { };
};

#endif //DORAYME_WORLD_H
