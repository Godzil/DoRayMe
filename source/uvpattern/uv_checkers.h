/*
 *  DoRayMe - a quick and dirty Raytracer
 *  UV Checkers header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_UV_CHECKERS_H
#define DORAYME_UV_CHECKERS_H

#include <uv_pattern.h>
#include <math.h>

class UVCheckers : public UVPattern
{
public:
    UVCheckers(double width, double height, Colour a, Colour b) : UVPattern(width, height, a, b) {};

    Colour uvPatternAt(double u, double v) {
        double u2 = floor(u * this->width);
        double v2 = floor(v * this->width);

        if (fmod((u2 + v2), 2) == 0)
        {
            return this->a;
        }
        return this->b;
    };
};

#endif /* DORAYME_UV_CHECKERS_H */
