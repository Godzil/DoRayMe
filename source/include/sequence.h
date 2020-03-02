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

#include <stdlib.h>
#include <stdint.h>
#include <time.h>

class Sequence
{
private:
    double *list;
    uint32_t listPos;
    uint32_t listSize;
public:
    Sequence() : list(nullptr), listPos(0), listSize(0) {
        /* Need to bootstrap rand here */
        srand(time(NULL));
    }
    Sequence(double *list, uint32_t listSize) : list(list), listPos(0), listSize(listSize) { };

    static double frand(void)
    {
        return rand() / ((double) RAND_MAX);
    }


    double next() {
        if (this->listSize == 0)
        {
           return frand();
        }
        else
        {
            uint32_t pos = this->listPos;
            this->listPos = (this->listPos + 1) % this->listSize;
            return this->list[pos];
        }
    }
};


#endif /* DORAYME_SEQUENCE_H */
