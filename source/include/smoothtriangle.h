/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Smooth Triangle header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_SMOOTHTRIANGLE_H
#define DORAYME_SMOOTHTRIANGLE_H

#include <triangle.h>

class SmoothTriangle : public Triangle
{
public:
    Vector n1;
    Vector n2;
    Vector n3;

protected:
    Tuple localNormalAt(Tuple point, Intersection *hit);

public:
    SmoothTriangle(Point p1, Point p2, Point p3, Vector n1, Vector n2, Vector n3);

    void dumpMe(FILE *fp);
};

#endif /* DORAYME_SMOOTHTRIANGLE_H */
