/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Sequence header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_SEQUENCE_H
#define DORAYME_SEQUENCE_H

#include <stdint.h>

class Sequence
{
private:
    double *list;
    uint32_t listPos;
    uint32_t listSize;
public:
    Sequence();
    Sequence(double *list, uint32_t listSize);
    double next();
};


#endif /* DORAYME_SEQUENCE_H */
