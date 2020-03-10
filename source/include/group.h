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

    char name[32 + 1];

protected:
    Intersect localIntersect(Ray r);
    Tuple localNormalAt(Tuple point, Intersection *hit = nullptr);

    BoundingBox bounds;

public:
    bool isEmpty();

    void addObject(Shape *s);
    void removeObject(Shape *s);

    Shape *operator[](const int p) { return this->objectList[p]; };
    Shape *getUnboxable(const int p) { return this->unboxableObjectList[p]; };

    Intersect intersect(Ray r);
    BoundingBox getLocalBounds();
    BoundingBox getBounds();

    void updateBoundingBox();
    void updateTransform();

    bool includes(Shape *b);

    uint32_t getObjectCount() { return this->objectCount; };
    uint32_t getUnboxableCount() { return this->unboxableObjectCount; };

    Group(const char *name = nullptr);

    void lock();

    const char *getName() { return this->name; };

    void dumpMe(FILE * fp);
};

#endif /* DORAYME_GROUP_H */
