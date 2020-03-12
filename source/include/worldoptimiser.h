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

/* World Optimiser subclasses will created move objects around to try to optimise the raytrace of the world, to
 * have as least as possible object to intersect per ray.
 * This class is abstract to we can implement different type and change at runtime or build time
 */
class WorldOptimiser
{
protected:
    Group *root;
    void moveInfiniteObjects(Shape *s = nullptr);
    void moveAllObjects(Shape *s = nullptr);
public:
    void setRoot(Group *root) { this->root = root; };
    virtual void run() = 0;
};

class NoWorldOptimisation : public WorldOptimiser
{
public:
    void run() {};
};

class BVHOptimisation : public WorldOptimiser
{
private:
    void makeTree(Group *leaf, int depth = 0);
public:
    void run();
};

class OctreeOptimisation : public WorldOptimiser
{
private:
    void makeTree(Group *leaf, int depth = 0);
public:
    void run();
};

#endif /* DORAYME_WORLDOPTIMISER_H */
