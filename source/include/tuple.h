/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Tuples header
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#ifndef DORAYME_TUPLE_H
#define DORAYME_TUPLE_H

#include <math_helper.h>

class Tuple
{
public:
    double x, y, z, w;

public:
    Tuple(double x, double y, double z) : x(x), y(y), z(z), w(0.0) {};
    Tuple(double x, double y, double z, double w)  : x(x), y(y), z(z), w(w) {};
    bool isPoint()  { return (this->w == 1.0); };
    bool isVector() { return (this->w == 0.0); };

    bool operator==(const Tuple &b) const { return double_equal(this->x, b.x) &&
                                                   double_equal(this->y, b.y) &&
                                                   double_equal(this->z, b.z) &&
                                                   double_equal(this->w, b.w); };

    Tuple operator+(const Tuple &b) const { return Tuple(this->x + b.x, this->y + b.y,
                                                         this->z + b.z, this->w + b.w); };

    Tuple operator-(const Tuple &b) const { return Tuple(this->x - b.x, this->y - b.y,
                                                         this->z - b.z, this->w - b.w); };
    Tuple operator-() const { return Tuple(-this->x, -this->y, -this->z, -this->w); };
    Tuple operator*(const double &b) const { return Tuple(this->x * b, this->y * b,
                                                          this->z * b, this->w * b); };
    Tuple operator/(const double &b) const { return Tuple(this->x / b, this->y / b,
                                                          this->z / b, this->w / b); };

    double magnitude();
    Tuple normalise();
    double dot(const Tuple &b);
};

class Point: public Tuple
{
public:
    Point(double x, double y, double z) : Tuple(x, y, z, 1.0) {};
};

class Vector: public Tuple
{
public:
    Vector(double x, double y, double z) : Tuple(x, y, z, 0.0) {};
    Vector cross(const Vector &b) const;
};

#endif /*DORAYME_TUPLE_H*/
