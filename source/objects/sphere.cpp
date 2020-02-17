/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Sphere implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <math.h>

#include <sphere.h>
#include <ray.h>
#include <tuple.h>
#include <intersect.h>

Intersect Sphere::intersect(Ray r)
{
    Intersect ret;
    double a, b, c, discriminant;
    Tuple sphere_to_ray = r.origin - Point(0, 0, 0);

    a = r.direction.dot(r.direction);
    b = 2 * r.direction.dot(sphere_to_ray);
    c = sphere_to_ray.dot(sphere_to_ray) - 1;

    discriminant = b * b - 4 * a * c;

    if (discriminant >= 0)
    {
        ret.add(newIntersection((-b - sqrt(discriminant)) / (2 * a), this));
        ret.add(newIntersection((-b + sqrt(discriminant)) / (2 * a), this));
    }

    return ret;
}