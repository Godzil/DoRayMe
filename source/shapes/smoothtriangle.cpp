/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Smooth Triangle implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <ray.h>
#include <shape.h>
#include <triangle.h>
#include <smoothtriangle.h>
#include <math_helper.h>
#include <renderstat.h>

SmoothTriangle::SmoothTriangle(Point p1, Point p2, Point p3, Vector n1, Vector n2, Vector n3) : Triangle(p1, p2, p3),
                                                                                                n1(n1), n2(n2), n3(n3)
{
    this->type = Shape::SMOOTHTRIANGLE;
    stats.addSmoothTriangle();
}

Tuple SmoothTriangle::localNormalAt(Tuple point, Intersection *hit)
{
    return (this->n2 * hit->u +
            this->n3 * hit->v +
            this->n1 * (1 - hit->u - hit->v)).normalise();
}

void SmoothTriangle::dumpMe(FILE *fp)
{
    Tuple t = this->n1;
    fprintf(fp, "\"n1\": { \"x\": %f, \"y\": %f, \"z\": %f}, \n",
            t.x, t.y, t.z);
    t = this->n2;
    fprintf(fp, "\"n2\": { \"x\": %f, \"y\": %f, \"z\": %f}, \n",
            t.x, t.y, t.z);
    t = this->n3;
    fprintf(fp, "\"n3\": { \"x\": %f, \"y\": %f, \"z\": %f}, \n",
            t.x, t.y, t.z);
    Triangle::dumpMe(fp);
}