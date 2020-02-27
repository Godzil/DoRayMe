/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Checkers Pattern header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_CHECKERSPATTERN_H
#define DORAYME_CHECKERSPATTERN_H

#include <stdio.h>

class CheckersPattern : public Pattern
{
public:
    CheckersPattern(Colour a, Colour b) : Pattern(a, b) { };

    Colour patternAt(Tuple point)
    {
        double value = floor(point.x) + floor(point.y) + floor(point.z);

        return (fmod(value, 2) == 0)?this->a:this->b;
    }

    void dumpMe(FILE *fp) {
        fprintf(fp, "\"Type\": \"Checkers\",\n");
        Pattern::dumpMe(fp);
    }

};

#endif /* DORAYME_CHECKERSPATTERN_H */
