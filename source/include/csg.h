/*
 *  DoRayMe - a quick and dirty Raytracer
 *  CSG header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_CSG_H
#define DORAYME_CSG_H

#include <shape.h>

class CSG : public Shape
{
public:
    enum OperationType
    {
        UNION,
        DIFFERENCE,
        INTERSECTION
    };

protected:
    Shape *left;
    Shape *right;
    OperationType operation;
    BoundingBox bounds;

protected:
    void localIntersect(Ray r, Intersect &xs);
    Tuple localNormalAt(Tuple point, Intersection *hit = nullptr);
    BoundingBox getLocalBounds();

    bool intersectionAllowed(bool leftHit, bool inLeft, bool inRight);

    void filterIntersections(Intersect &xs, Intersect &ret);

    void updateBoundingBox();
    BoundingBox getBounds();

public:
    CSG(OperationType operation, Shape *left, Shape *right);

    void intersect(Ray &r, Intersect &xs);

    bool includes(Shape *b);

    void updateTransform();

    void lock();

    void dumpMe(FILE *fp);
};

#endif /* DORAYME_CSG_H */
