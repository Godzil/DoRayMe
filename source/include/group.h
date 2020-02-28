/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Group header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_GROUP_H
#define DORAYME_GROUP_H

#include <shape.h>
#include <stdio.h>

/* TODO: Add a way to force(?) material from group to be applied on childs */

class Group : public Shape
{
private:
    uint32_t allocatedObjectCount;
    Shape* *objectList;
    uint32_t objectCount;

    uint32_t allocatedUnboxableObjectCount;
    Shape* *unboxableObjectList;
    uint32_t unboxableObjectCount;

protected:
    Intersect localIntersect(Ray r);
    Tuple localNormalAt(Tuple point);

    BoundingBox bounds;

public:
    bool isEmpty();

    void addObject(Shape *s);
    Shape *operator[](const int p) { return this->objectList[p]; }

    Intersect intersect(Ray r);
    BoundingBox getBounds();

    void updateBoundingBox();
    void updateTransform();

    Group();

    void dumpMe(FILE * fp);
};

#endif /* DORAYME_GROUP_H */
