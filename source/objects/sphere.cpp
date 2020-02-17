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

    Ray transRay = this->invTransform(r);

    Tuple sphere_to_ray = transRay.origin - Point(0, 0, 0);

    a = transRay.direction.dot(transRay.direction);
    b = 2 * transRay.direction.dot(sphere_to_ray);
    c = sphere_to_ray.dot(sphere_to_ray) - 1;

    discriminant = b * b - 4 * a * c;

    if (discriminant >= 0)
    {
        ret.add(Intersection((-b - sqrt(discriminant)) / (2 * a), this));
        ret.add(Intersection((-b + sqrt(discriminant)) / (2 * a), this));
    }

    return ret;
}

Tuple Sphere::normalAt(Tuple point)
{
    Tuple object_point = this->inverseTransform * point;
    Tuple object_normal = (object_point - Point(0, 0, 0)).normalise();
    Tuple world_normal = this->inverseTransform.transpose() * object_normal;

    /* W may get wrong, so hack it. This is perfectly normal as we are using a 4x4 matrix instead of a 3x3 */
    world_normal.w = 0;

    return world_normal.normalise();
}