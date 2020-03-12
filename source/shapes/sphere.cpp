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

void Sphere::localIntersect(Ray r, Intersect &xs)
{
    double a, b, c, discriminant;

    Tuple sphere_to_ray = r.origin - Point(0, 0, 0);

    a = r.direction.dot(r.direction);
    b = 2 * r.direction.dot(sphere_to_ray);
    c = sphere_to_ray.dot(sphere_to_ray) - 1;

    discriminant = b * b - 4 * a * c;

    if (discriminant >= 0)
    {
        xs.add(Intersection((-b - sqrt(discriminant)) / (2 * a), this));
        xs.add(Intersection((-b + sqrt(discriminant)) / (2 * a), this));
    }
}

Tuple Sphere::localNormalAt(Tuple point, Intersection *hit)
{
    return (point - Point(0, 0, 0)).normalise();
}

void Sphere::dumpMe(FILE *fp)
{
    fprintf(fp, "\"Type\": \"Sphere\",\n");
    Tuple t = this->transformMatrix * Point(0, 0, 0);
    fprintf(fp, "\"center\": { \"x\": %f, \"y\": %f, \"z\": %f}, \n",
            t.x, t.y, t.z);
    t = this->transformMatrix * Point(1, 1, 1);
    fprintf(fp, "\"radius\": { \"x\": %f, \"y\": %f, \"z\": %f}, \n",
            t.x, t.y, t.z);
    Shape::dumpMe(fp);
}