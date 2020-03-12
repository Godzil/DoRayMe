/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Cylinder implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <tuple.h>
#include <ray.h>
#include <shape.h>
#include <cylinder.h>
#include <math_helper.h>

bool Cylinder::checkCap(Ray r, double t)
{
    /* Helping function to reduce duplication.
     * Checks to see if the intersection ot t is within a radius
     * of 1 (the radius of our cylinder from the y axis
     */
    double x = r.origin.x + t * r.direction.x;
    double z = r.origin.z + t * r.direction.z;
    return (x * x + z * z) <= 1;
}

void Cylinder::intersectCaps(Ray r, Intersect &xs)
{
    /* Caps only matter if the cylinder is closed, and might possibly be
     * intersected by the ray
     */
    if ((this->isClosed) && (fabs(r.direction.y) > getEpsilon()))
    {
        double t;
        /* Check for an intersection with the lower end cap by intersecting
         * the ray with the plan at y = this->minCap
         */
        t = (this->minCap - r.origin.y) / r.direction.y;
        if (this->checkCap(r, t))
        {
            xs.add(Intersection(t, this));
        }

        /* Check for an intersection with the upper end cap by intersecting
         * the ray with the plan at y = this->maxCap
         */
        t = (this->maxCap - r.origin.y) / r.direction.y;
        if (this->checkCap(r, t))
        {
            xs.add(Intersection(t, this));
        }
    }
}

void Cylinder::localIntersect(Ray r, Intersect &xs)
{
    double A = r.direction.x * r.direction.x + r.direction.z * r.direction.z;

    /* Ray is parallel to the Y axis */
    if (A >= getEpsilon())
    {
        double B = 2 * r.origin.x * r.direction.x +
                   2 * r.origin.z * r.direction.z;
        double C = r.origin.x * r.origin.x + r.origin.z * r.origin.z - 1;

        double disc = B * B - 4 * A * C;

        if (disc >= 0)
        {
            double t0 = (-B - sqrt(disc)) / (2 * A);
            double t1 = (-B + sqrt(disc)) / (2 * A);

            double y0 = r.origin.y + t0 * r.direction.y;
            if ((this->minCap < y0) && (y0 < this->maxCap))
            {
                xs.add(Intersection(t0, this));
            }

            double y1 = r.origin.y + t1 * r.direction.y;
            if ((this->minCap < y1) && (y1 < this->maxCap))
            {
                xs.add(Intersection(t1, this));
            }
        }
    }

    this->intersectCaps(r, xs);
}

Tuple Cylinder::localNormalAt(Tuple point, Intersection *hit)
{
    /* Compute the square of the distance from the Y axis */
    double dist = point.x * point.x + point.z * point.z;

    if ((dist < 1) && (point.y >= (this->maxCap - getEpsilon())))
    {
        return Vector(0, 1, 0);
    }

    if ((dist < 1) && (point.y <= this->minCap + getEpsilon()))
    {
        return Vector(0, -1, 0);
    }

    return Vector(point.x, 0, point.z);
}

BoundingBox Cylinder::getLocalBounds()
{
    BoundingBox ret;

    ret | Point(-1, this->minCap, -1);
    ret | Point(1, this->maxCap, 1);

    return ret;
}

void Cylinder::dumpMe(FILE *fp)
{
    fprintf(fp, "\"Type\": \"Cylinder\",\n");
    Tuple t = this->transformMatrix * Point(0, 0, 0);
    fprintf(fp, "\"pseudocenter\": { \"x\": %f, \"y\": %f, \"z\": %f}, \n",
            t.x, t.y, t.z);
    t = this->transformMatrix * Point(0, this->minCap, 0);
    fprintf(fp, "\"min\": %f, \n", t.y);
    t = this->transformMatrix * Point(1, this->maxCap, 1);
    fprintf(fp, "\"max\": %f, \n", t.y);
    Shape::dumpMe(fp);
}