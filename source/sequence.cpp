/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Sequence implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <sequence.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <math_helper.h>

Sequence::Sequence() : list(nullptr), listPos(0), listSize(0) {
    /* Need to bootstrap rand here */
    srand(time(NULL));
}

Sequence::Sequence(double *list, uint32_t listSize) : list(list), listPos(0), listSize(listSize) { };

double Sequence::next() {
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