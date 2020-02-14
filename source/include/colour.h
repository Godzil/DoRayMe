/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Colour header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_COLOUR_H
#define DORAYME_COLOUR_H

#include <tuples.h>

class Colour : public Tuple
{
public:
    Colour(double red, double green, double blue) : Tuple(red, green, blue, 0) {};
    double red()           { return this->x; };
    double green()         { return this->y; };
    double blue()          { return this->z; };
    double red(double v)   { this->x = v; return v; };
    double green(double v) { this->y = v; return v; };
    double blue(double v)  { this->z = v; return v; };

    using Tuple::operator*;
    Colour operator*(const Colour &b) const { return Colour(this->x * b.x,
                                                            this->y * b.y,
                                                            this->z * b.z); };
};


#endif /* DORAYME_COLOUR_H */
