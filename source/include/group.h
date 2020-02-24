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

class Group : public Shape
{
private:
    uint32_t allocatedObjectCount;
    Shape* *objectList;
    uint32_t objectCount;

protected:
    Intersect localIntersect(Ray r);
    Tuple localNormalAt(Tuple point);



public:
    bool isEmpty();

    void addObject(Shape *s);
    Shape *operator[](const int p) { return this->objectList[p]; }

    Intersect intersect(Ray r);

    BoundingBox getBounds();

    Group();
};

#endif /* DORAYME_GROUP_H */
