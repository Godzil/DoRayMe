/*
 *  DoRayMe - a quick and dirty Raytracer
 *  UV Pattern header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_UV_PATTERN_H
#define DORAYME_UV_PATTERN_H

#include <colour.h>

class UVPattern
{
public:
    Colour a;
    Colour b;
    double width;
    double height;

    UVPattern(double width, double height, Colour a, Colour b) : a(a), b(b),
                                                                 width(width), height(height) {};

    virtual Colour uvPatternAt(double u, double v) = 0;
};

#endif /* DORAYME_UV_PATTERN_H */
