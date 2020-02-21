/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Ring Pattern header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_RINGSUPPORT_H
#define DORAYME_RINGSUPPORT_H

#include <pattern.h>

class RingPattern : public Pattern
{
public:
    RingPattern(Colour a, Colour b) : Pattern(a, b) { };

    Colour patternAt(Tuple point)
    {
        Tuple distance = this->b - this->a;
        double fraction = point.x - floor(point.x);

        Tuple ret = this->a + distance * fraction;

        return Colour(ret.x, ret.y, ret.z);
    }
};


#endif //DORAYME_RINGSUPPORT_H
