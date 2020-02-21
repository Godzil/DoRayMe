/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Strip Pattern header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_TESTPATTERN_H
#define DORAYME_TESTPATTERN_H

#include <pattern.h>

#include <stdio.h>

class TestPattern : public Pattern
{
public:
    TestPattern() : Pattern(Colour(0, 0, 0), Colour(1, 1, 1)) { };

    Colour patternAt(Tuple point)
    {
        return Colour(point.x, point.y, point.z);
    }
};

#endif /* DORAYME_TESTPATTERN_H */
