/*
 *  DoRayMe - a quick and dirty Raytracer
 *  World optimiser header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_WORLDOPTIMISER_H
#define DORAYME_WORLDOPTIMISER_H

#include <group.h>

/* World Optimiser subclasses will created move objcet around to try to optimise the parsing of the world.
 * This class is abstract to we can implement different type and change at runtime or build time
 */
class WorldOptimiser
{
public:
    virtual void run(Group *root) = 0;
};

class NoWorldOptimisation : public WorldOptimiser
{
public:
    void run(Group *root) {};
};

class OctreeOptimisation : public WorldOptimiser
{
public:
    void run(Group *root) {};
};

#endif /* DORAYME_WORLDOPTIMISER_H */
