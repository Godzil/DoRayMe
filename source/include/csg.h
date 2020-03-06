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
    Intersect localIntersect(Ray r);
    Tuple localNormalAt(Tuple point, Intersection *hit = nullptr);
    BoundingBox getLocalBounds();

    bool intersectionAllowed(bool leftHit, bool inLeft, bool inRight);

    Intersect filterIntersections(Intersect &xs);

    void updateBoundingBox();
    BoundingBox getBounds();

public:
    CSG(OperationType operation, Shape *left, Shape *right);

    Intersect intersect(Ray r);

    bool includes(Shape *b);

    void updateTransform();

    void dumpMe(FILE *fp);
};

#endif /* DORAYME_CSG_H */
