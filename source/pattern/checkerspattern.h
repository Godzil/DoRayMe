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

class CheckersPattern : public Pattern
{
public:
    CheckersPattern(Colour a, Colour b) : Pattern(a, b) { };

    Colour patternAt(Tuple point)
    {
        double value = floor(point.x) + floor(point.y) + floor(point.z);

        return (fmod(value, 2) == 0)?this->a:this->b;
    }
};

#endif /* DORAYME_CHECKERSPATTERN_H */
