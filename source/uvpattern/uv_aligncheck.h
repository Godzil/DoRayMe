/*
 *  DoRayMe - a quick and dirty Raytracer
 *  UV Align Check test pattern header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_UV_ALIGNCHECK_H
#define DORAYME_UV_ALIGNCHECK_H

class UVAlignCheck : public UVPattern
{
public:
    Colour ul, ur, bl, br;

    UVAlignCheck(Colour main, Colour ul, Colour ur, Colour bl, Colour br) : UVPattern(1, 1, main, main),
                                                                            ul(ul), ur(ur), bl(bl), br(br) {};

    Colour uvPatternAt(double u, double v) {
        /* Remember that v=0 is  at the bottom, v=1 at the top */
        if (v > 0.8)
        {
            if (u < 0.2) { return this->ul; }
            if (u > 0.8) { return this->ur; }
        }
        else if (v < 0.2)
        {
            if (u < 0.2) { return this->bl; }
            if (u > 0.8) { return this->br; }
        }

        /* main is stored in A or B */
        return this->a;
    };
};


#endif /* DORAYME_UV_ALIGNCHECK_H */
