/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Triangle header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_TRIANGLE_H
#define DORAYME_TRIANGLE_H

#include <shape.h>
#include <stdio.h>

class Triangle : public Shape
{
    Intersect localIntersect(Ray r);
    Tuple localNormalAt(Tuple point);

public:
    Tuple p1, p2, p3;
    Tuple e1, e2;
    Tuple normal;

public:
    Triangle(Point p1, Point p2, Point p3);
    BoundingBox getBounds();

    void dumpMe(FILE *fp);

};

#endif /* DORAYME_TRIANGLE_H */
