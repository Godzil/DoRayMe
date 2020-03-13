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
    Tuple() : x(0), y(0), z(0), w(0.0) {};
    Tuple(double x, double y, double z) : x(x), y(y), z(z), w(0.0) {};
    Tuple(double x, double y, double z, double w)  : x(x), y(y), z(z), w(w) {};
    bool isPoint()  { return (this->w == 1.0); };
    bool isVector() { return (this->w == 0.0); };

    bool operator==(const Tuple &b) const { return double_equal(this->x, b.x) &&
                                                   double_equal(this->y, b.y) &&
                                                   double_equal(this->z, b.z) &&
                                                   double_equal(this->w, b.w); };
    bool operator!=(const Tuple &b) const { return !(*this == b); };

    Tuple operator+(const Tuple &b) const { return Tuple(this->x + b.x, this->y + b.y,
                                                         this->z + b.z, this->w + b.w); };

    Tuple operator-(const Tuple &b) const { return Tuple(this->x - b.x, this->y - b.y,
                                                         this->z - b.z, this->w - b.w); };
    Tuple operator-() const { return Tuple(-this->x, -this->y, -this->z, -this->w); };
    Tuple operator*(const double &b) const { return Tuple(this->x * b, this->y * b,
                                                          this->z * b, this->w * b); };
    Tuple operator/(const double &b) const { return Tuple(this->x / b, this->y / b,
                                                          this->z / b, this->w / b); };
    bool isRepresentable();

    void set(double nX, double nY, double nZ) { this->x = nX; this->y = nY; this->z = nZ; };
    double magnitude();
    Tuple normalise();

    double dot(const Tuple &b) {
        return this->x * b.x + this->y * b.y + this->z * b.z + this->w * b.w;
    }

    Tuple cross(const Tuple &b) const {
        return Tuple(this->y * b.z - this->z * b.y,
                     this->z * b.x - this->x * b.z,
                     this->x * b.y - this->y * b.x,
                     0);
    }

    Tuple reflect(const Tuple &normal);
};

class Point: public Tuple
{
public:
    Point() : Tuple(0, 0, 0, 1.0) {};
    Point(double x, double y, double z) : Tuple(x, y, z, 1.0) {};
};

class Vector: public Tuple
{
public:
    Vector() : Tuple(0, 0, 0, 0.0) {};
    Vector(double x, double y, double z) : Tuple(x, y, z, 0.0) {};
};

#endif /* DORAYME_TUPLE_H */
