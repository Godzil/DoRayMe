/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Strip Pattern header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */

#ifndef DORAYME_STRIPPATTERN_H
#define DORAYME_STRIPPATTERN_H

#include <pattern.h>

#include <stdio.h>

class StripPattern : public Pattern
{
public:
    StripPattern(Colour a, Colour b) : Pattern(a, b) { };

    Colour patternAt(Tuple point)
    {
        if (fmod(floor(point.x), 2) == 0)
        {
            return this->a;
        }
        return this->b;
    }

    void dumpMe(FILE *fp) {
        fprintf(fp, "\"Type\": \"Strip\",\n");
        Pattern::dumpMe(fp);
    }
};

#endif /* DORAYME_STRIPPATTERN_H */
