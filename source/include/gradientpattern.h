/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Gradient Pattern header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_GRADIENTPATTERN_H
#define DORAYME_GRADIENTPATTERN_H

#include <pattern.h>

class GradientPattern : public Pattern
{
public:
    GradientPattern(Colour a, Colour b) : Pattern(a, b) { };

    Colour patternAt(Tuple point)
    {
        Tuple distance = this->b - this->a;
        double fraction = point.x - floor(point.x);

        Tuple ret = this->a + distance * fraction;

        return Colour(ret.x, ret.y, ret.z);
    }
};

#endif //DORAYME_GRADIENTPATTERN_H
