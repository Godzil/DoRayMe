/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Pattern header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_PATTERN_H
#define DORAYME_PATTERN_H

#include <colour.h>
#include <tuple.h>
#include <matrix.h>
#include <stdio.h>

class Shape;

class Pattern
{
public:
    Colour a;
    Colour b;

    Matrix transformMatrix;
    Matrix inverseTransform;

public:
    Pattern(Colour a, Colour b);

    virtual Colour patternAt(Tuple point) = 0;
    virtual void dumpMe(FILE *fp);

    void setTransform(Matrix transform);
    Colour patternAtObject(Shape *object, Tuple point);
};

#endif /* DORAYME_PATTERN_H */
