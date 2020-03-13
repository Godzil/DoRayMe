/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Tuples implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <tuple.h>

#include <math.h>


double Tuple::magnitude()
{
    return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2) + pow(this->w, 2));
}

Tuple Tuple::normalise()
{
    double mag = this->magnitude();
    if (mag == 0)
    {
        return Tuple(0, 0, 0, 0);
    }

    return Tuple(this->x / mag, this->y / mag, this->z / mag, this->w / mag);
}
/*
double Tuple::dot(const Tuple &b)
{
    return this->x * b.x + this->y * b.y + this->z * b.z + this->w * b.w;
}

Tuple Tuple::cross(const Tuple &b) const
{
    return Tuple(this->y * b.z - this->z * b.y,
                 this->z * b.x - this->x * b.z,
                 this->x * b.y - this->y * b.x,
                 0);
}
*/
Tuple Tuple::reflect(const Tuple &normal)
{
    return *this - normal * 2 * this->dot(normal);
}

bool Tuple::isRepresentable()
{
    return !(isnan(this->x) || isnan(this->y) || isnan(this->z) ||
             isinf(this->x) || isinf(this->y) || isinf(this->z));
}