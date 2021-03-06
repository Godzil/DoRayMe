/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Cube implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <tuple.h>
#include <ray.h>
#include <shape.h>
#include <cube.h>
#include <math_helper.h>

void Cube::checkAxis(double axeOrigin, double axeDirection, double *axeMin, double *axeMax)
{
    double tMinNumerator = (-1 - axeOrigin);
    double tMaxNumerator = (1 - axeOrigin);

    if (fabs(axeDirection) >= getEpsilon())
    {
        *axeMin = tMinNumerator / axeDirection;
        *axeMax = tMaxNumerator / axeDirection;
    }
    else
    {
        *axeMin = tMinNumerator * INFINITY;
        *axeMax = tMaxNumerator * INFINITY;
    }

    if (*axeMin > *axeMax)
    {
        double swap = *axeMax;
        *axeMax = *axeMin;
        *axeMin = swap;
    }
}

void Cube::localIntersect(Ray r, Intersect &xs)
{
    double xtMin, xtMax, ytMin, ytMax, ztMin, ztMax;
    double tMin, tMax;

    this->checkAxis(r.origin.x, r.direction.x, &xtMin, &xtMax);
    this->checkAxis(r.origin.y, r.direction.y, &ytMin, &ytMax);
    this->checkAxis(r.origin.z, r.direction.z, &ztMin, &ztMax);

    tMin = max3(xtMin, ytMin, ztMin);
    tMax = min3(xtMax, ytMax, ztMax);

    if (tMin <= tMax)
    {
        xs.add(Intersection(tMin, this));
        xs.add(Intersection(tMax, this));
    }
}

Tuple Cube::localNormalAt(Tuple point, Intersection *hit)
{
    double maxC = max3(fabs(point.x), fabs(point.y), fabs(point.z));

    if (maxC == fabs(point.x))
    {
        return Vector(point.x, 0, 0);
    }
    else if (maxC == fabs(point.y))
    {
        return Vector(0, point.y, 0);
    }

    return Vector(0, 0, point.z);
}

void Cube::dumpMe(FILE *fp)
{
    fprintf(fp, "\"Type\": \"Cube\",\n");
    Tuple t = this->transformMatrix * Point(0, 0, 0);
    fprintf(fp, "\"center\": { \"x\": %f, \"y\": %f, \"z\": %f}, \n",
            t.x, t.y, t.z);
    t = this->transformMatrix * Point(1, 1, 1);
    fprintf(fp, "\"corner\": { \"x\": %f, \"y\": %f, \"z\": %f}, \n",
            t.x, t.y, t.z);
    Shape::dumpMe(fp);
}