/*
 *  DoRayMe - a quick and dirty Raytracer
 *  Cone implementation
 *
 *  Created by Manoël Trapier
 *  Copyright (c) 2020 986-Studio.
 *
 */
#include <ray.h>
#include <shape.h>
#include <triangle.h>
#include <math_helper.h>
#include <renderstat.h>

Triangle::Triangle(Point p1, Point p2, Point p3) : Shape(SHAPE_TRIANGLE), p1(p1), p2(p2), p3(p3)
{
    stats.addTriangle();

    this->e1 = p2 - p1;
    this->e2 = p3 - p1;
    this->normal = e2.cross(e1).normalise();
}

Intersect Triangle::localIntersect(Ray r)
{
    Intersect ret;

    Tuple dirCrossE2 = r.direction.cross(this->e2);
    double determinant = this->e1.dot(dirCrossE2);
    if (fabs(determinant) < getEpsilon())
    {
        return ret;
    }

    double f = 1.0 / determinant;
    Tuple p1ToOrigin = r.origin - this->p1;
    Tuple originCrossE1 = p1ToOrigin.cross(this->e1);
    double u = f * p1ToOrigin.dot(dirCrossE2);
    double v = f * r.direction.dot(originCrossE1);

    if ((u < 0) || (u > 1))
    {
        return ret;
    }

    if ((v < 0) || ((u + v) > 1))
    {
        return ret;
    }

    double t = f * this->e2.dot(originCrossE1);
    ret.add(Intersection(t, this));

    return ret;
}

Tuple Triangle::localNormalAt(Tuple point)
{
    return this->normal;
}

BoundingBox Triangle::getLocalBounds()
{
    BoundingBox ret;

    ret | this->objectToWorld(p1);
    ret | this->objectToWorld(p2);
    ret | this->objectToWorld(p3);

    return ret;
}

void Triangle::dumpMe(FILE *fp)
{
    fprintf(fp, "\"Type\": \"Triangle\",\n");
    Tuple t = this->transformMatrix * this->p1;
    fprintf(fp, "\"p1\": { \"x\": %f, \"y\": %f, \"z\": %f}, \n",
            t.x, t.y, t.z);
    t = this->transformMatrix * this->p2;
    fprintf(fp, "\"p2\": { \"x\": %f, \"y\": %f, \"z\": %f}, \n",
            t.x, t.y, t.z);
    t = this->transformMatrix * this->p3;
    fprintf(fp, "\"p3\": { \"x\": %f, \"y\": %f, \"z\": %f}, \n",
            t.x, t.y, t.z);
    Shape::dumpMe(fp);
}