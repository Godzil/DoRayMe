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
        double squared = (point.x * point.x) + (point.z * point.z);

        double value = floor(sqrt(squared));

        return (modulo(value, 2) == 0)?this->a:this->b;
    }

    void dumpMe(FILE *fp) {
        fprintf(fp, "\"Type\": \"Ring\"\n");
        Pattern::dumpMe(fp);
    }
};


#endif /* DORAYME_RINGSUPPORT_H */
